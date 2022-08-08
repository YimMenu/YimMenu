const axios = require('axios');
const fs = require('fs-extra');
const path = require('path');

function joaat(key) {
    key = key.toLowerCase();

    let hash = 0;
    for (let i = 0, length = key.length; i < length; i++) {
        hash += key.charCodeAt(i);
        hash += (hash << 10);
        hash ^= (hash >>> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >>> 11);
    hash += (hash << 15);

    return hash>>>0;
}

async function read_etag(path) {
    let etag = "";

    try {
        etag = await fs.readFile(path);
    } catch (err) {
        etag = "";
    }

    return etag;
}

function remove_last_n(str, n) {
    return str.substring(0, str.length - n);
}

function title_case(str) {
    var splitStr = str.toLowerCase().split(/[\s_]+/);
    for (var i = 0; i < splitStr.length; i++) {
        splitStr[i] = splitStr[i].charAt(0).toUpperCase() + splitStr[i].substring(1);     
    }

    return splitStr.join(' '); 
}


async function check_update(url, etag_path, output_path, gen_callback) {
    try {
        let etag = await read_etag(etag_path);

        let response = await axios({
            url: url,
            method: 'HEAD'
        });

        if (response.headers['etag'] == etag) {
            console.log('"' + output_path + '" is up to date.');
            return;
        }

        response = await axios({
            url: url,
            method: 'GET',
            responseType: 'arraybuffer'
        });

        try {
            let file_str = gen_callback(response.data.toString());

            await fs.outputFile(
                output_path, 
                file_str
            );

        } catch (e) {
            console.log('Failed to generate "' + output_path + '".');
            console.log(e);
            return;
        }

        try {
            await fs.writeFile(etag_path, response.headers['etag']);
        } catch (e) {
            console.log('Failed to generate "' + etag_path + '".');
            console.log(e);
            return;
        }

        console.log('"' + output_path + '" updated.');
    } catch (e) {
        console.log('Failed to connect to "' + url + '".');
        console.log(e);
    }
}

async function gen_objects() {
    await check_update(
        'https://raw.githubusercontent.com/DurtyFree/gta-v-data-dumps/master/ObjectList.ini',
        path.resolve(__dirname, './etag_objects.txt'),
        path.resolve(__dirname, './dist/BigBaseV2/src/services/gta_data/object_data.hpp'),
        (text_data) => {

            let object_hash_map_str = 'gta_data_service::m_object_hash_map = {\n';
            object_hash_map_str += `\t{ 0, "" } \n`;

            let lines = text_data.split('\n');
            for (let line of lines) {
                if (!line) {
                    continue;
                }
                
                object_hash_map_str += `\t{ ${joaat(line)}, "${line}" } \n`;
            }

            object_hash_map_str = remove_last_n(object_hash_map_str, 3);
            object_hash_map_str += `\n};\n\n`;
    
            return '#include "gta_data_service.hpp"\n\n' + object_hash_map_str;
        }
    );
}

async function gen_peds() {
    await check_update(
        'https://raw.githubusercontent.com/DurtyFree/gta-v-data-dumps/master/peds.json',
        path.resolve(__dirname, './etag_peds.txt'),
        path.resolve(__dirname, './dist/BigBaseV2/src/services/gta_data/ped_data.hpp'),
        (text_data) => {
            let json_data = JSON.parse(text_data);

            let ped_hash_map_str = 'gta_data_service::m_ped_hash_idx_map = {\n';
            let ped_arr_str = 'gta_data_service::m_ped_item_arr = {\n';
            let ped_type_str = 'gta_data_service::m_ped_type_arr = {\n';

            let num_of_items = 0;
            let ped_type_set = new Set();

            let filtered_items = [{
                hash: 0,
                type_idx: -1,
                type: "",
                name: ""
            }];
    
            for (let item of json_data) {
                if (
                    !item["Hash"] ||
                    !item["Name"] ||
                    !item["Pedtype"]
                ) {
                    console.log("Filtered ped: " + item["Name"]);
                    continue;
                }
    
                let ped = {
                    hash: item["Hash"],
                    type_idx: -1,
                    type: title_case(item["Pedtype"]),
                    name: item["Name"]
                }
 
                ped_type_set.add(ped.type);
    
                filtered_items.push(ped);
            }
    
            filtered_items.sort((a, b) => {
                if (a.name < b.name) return -1;
                if (a.name > b.name) return 1;
                return 0;
            });
    
            let ped_type_arr = [...ped_type_set];
            ped_type_arr.sort();
    
            let ped_type_map = {};
            for (let type_idx in ped_type_arr)
            {
                ped_type_map[ped_type_arr[type_idx]] = type_idx;
            }
    
            for (let ped of filtered_items)
            {
                if (ped.type) {
                    ped.type_idx = ped_type_map[ped.type];
                }
    
                ped_hash_map_str += `\t{ ${ped.hash}, ${num_of_items} }, \n`;
                ped_arr_str += `\t{ ${ped.hash}, ${ped.type_idx}, "${ped.name}" }, \n`;
                num_of_items++;
            }
    
            for (let ped_type of ped_type_arr)
            {
                ped_type_str += `\t"${ped_type}", \n`
            }
    
            ped_hash_map_str = remove_last_n(ped_hash_map_str, 3);
            ped_hash_map_str += `\n};\n\n`;
    
            ped_arr_str = remove_last_n(ped_arr_str, 3);
            ped_arr_str += `\n};\n\n`;
    
            ped_type_str = remove_last_n(ped_type_str, 3);
            ped_type_str += `\n};\n\n`;
    
            return '#include "gta_data_service.hpp"\n\n' + ped_arr_str + ped_hash_map_str + ped_type_str;
        }
    );
}

async function gen_vehicles() {
    await check_update(
        'https://raw.githubusercontent.com/DurtyFree/gta-v-data-dumps/master/vehicles.json',
        path.resolve(__dirname, './etag_vehicles.txt'),
        path.resolve(__dirname, './dist/BigBaseV2/src/services/gta_data/vehicle_data.hpp'),
        (text_data) => {
            let json_data = JSON.parse(text_data);

            let veh_hash_map_str = 'gta_data_service::m_vehicle_hash_idx_map = {\n';
            let veh_arr_str = 'gta_data_service::m_vehicle_item_arr = {\n';
            let veh_class_str = 'gta_data_service::m_vehicle_class_arr = {\n';
            let veh_maker_arr_str = 'gta_data_service::m_vehicle_manufacturer_arr = {\n';
    
            let num_of_items = 0;
            let veh_class_set = new Set();
            let veh_maker_set = new Set();
            let veh_display_name_count = {};
            let filtered_items = [{
                hash: 0,
                class_idx: -1,
                clazz: "",
                name: "",
                display_name: "",
                manufacturer_idx: -1,
                display_manufacturer: ""
            }];
    
            for (let item of json_data) {
                item["Name"] = item["Name"].toUpperCase();
    
                if (
                    !item["Hash"] ||
                    !item["Name"] || 
                    !item["Class"] || 
                    !item["Bones"] ||
                    item["Bones"][0] == "stub"
                ) {
                    console.log("Filtered vehicle: " + item["Name"]);
                    continue;
                }
    
                let veh = {
                    hash: item["Hash"],
                    class_idx: -1,
                    clazz: title_case(item["Class"]),
                    name: item["Name"],
                    display_name: item["Name"],
                    manufacturer_idx: -1,
                    display_manufacturer: ""
                }
    
                if (veh.clazz == "Compacts") {
                    veh.clazz = "Compact";
                }
    
                if (item["DisplayName"]) {
                    veh.display_name = item["DisplayName"];
                }
        
                if (item["ManufacturerDisplayName"]) {
                    veh.display_manufacturer = item["ManufacturerDisplayName"];
                }  else if (item["Manufacturer"]) {
                    veh.display_manufacturer = item["Manufacturer"];
                }
    
                if (!veh_display_name_count[veh.display_name])
                {
                    veh_display_name_count[veh.display_name] = 0;
                }
                veh_display_name_count[veh.display_name]++;
    
                if (veh.clazz) {
                    veh_class_set.add(veh.clazz);
                }

                if (veh.display_manufacturer) {
                    veh_maker_set.add(veh.display_manufacturer);
                }
    
                filtered_items.push(veh);
            }
    
            filtered_items.sort((a, b) => {
                if (a.display_name < b.display_name) return -1;
                if (a.display_name > b.display_name) return 1;
                return 0;
            });
    
            let veh_class_arr = [...veh_class_set];
            veh_class_arr.sort();
    
            let veh_class_map = {};
            for (let class_idx in veh_class_arr) {
                veh_class_map[veh_class_arr[class_idx]] = class_idx;
            }

            let veh_maker_arr = [...veh_maker_set];
            veh_maker_arr.sort();
    
            let veh_maker_map = {};
            for (let maker_idx in veh_maker_arr) {
                veh_maker_map[veh_maker_arr[maker_idx]] = maker_idx;
            }
    
            for (let veh of filtered_items) {
                if (veh_display_name_count[veh.display_name] > 1) {
                    veh.display_name = veh.display_name + ' (' + veh.name + ')';
                }
    
                if (veh.clazz) {
                    veh.class_idx = veh_class_map[veh.clazz];
                }

                if (veh.display_manufacturer) {
                    veh.manufacturer_idx = veh_maker_map[veh.display_manufacturer];
                }
    
                veh_hash_map_str += `\t{ ${veh.hash}, ${num_of_items} }, \n`;
                veh_arr_str += `\t{ ${veh.hash}, ${veh.class_idx}, "${veh.display_name}", ${veh.manufacturer_idx} }, \n`;
                num_of_items++;
            }
    
            for (let clazz of veh_class_arr)
            {
                veh_class_str += `\t"${clazz}", \n`
            }

            for (let maker of veh_maker_arr)
            {
                veh_maker_arr_str += `\t"${maker}", \n`
            }
    
            veh_hash_map_str = remove_last_n(veh_hash_map_str, 3);
            veh_hash_map_str += `\n};\n\n`;
    
            veh_arr_str = remove_last_n(veh_arr_str, 3);
            veh_arr_str += `\n};\n\n`;
    
            veh_class_str = remove_last_n(veh_class_str, 3);
            veh_class_str += `\n};\n\n`;

            veh_maker_arr_str = remove_last_n(veh_maker_arr_str, 3);
            veh_maker_arr_str += `\n};\n\n`;
    
            return '#include "gta_data_service.hpp"\n\n' + veh_arr_str + veh_hash_map_str + veh_class_str + veh_maker_arr_str;
        }
    );
}

async function gen_weapon() {
    await check_update(
        'https://raw.githubusercontent.com/DurtyFree/gta-v-data-dumps/master/weapons.json',
        path.resolve(__dirname, './etag_weapons.txt'),
        path.resolve(__dirname, './dist/BigBaseV2/src/services/gta_data/weapon_data.hpp'),
        (text_data) => {
            let json_data = JSON.parse(text_data);

            const hash_blacklist_set = new Set([
                joaat("WEAPON_BIRD_CRAP"),
                joaat("WEAPON_DIGISCANNER"),
                joaat("WEAPON_GARBAGEBAG"),
                joaat("WEAPON_GRENADELAUNCHER_SMOKE"),
                joaat("WEAPON_HANDCUFFS"),
                joaat("WEAPON_METALDETECTOR"),
                joaat("GADGET_NIGHTVISION"),
                joaat("GADGET_PARACHUTE"),
                joaat("WEAPON_TRANQUILIZER"),
                joaat("WEAPON_STINGER")
            ]);

            let weapon_hash_map_str = 'gta_data_service::m_weapon_hash_idx_map = {\n';
            let weapon_arr_str = 'gta_data_service::m_weapon_item_arr = {\n';
            let weapon_type_str = 'gta_data_service::m_weapon_type_arr = {\n';

            let num_of_items = 0;
            let weapon_type_set = new Set();

            let filtered_items = [{
                hash: 0,
                type_idx: -1,
                type: "",
                name: "",
                throwable: false,
                reward_hash: 0,
                reward_ammo_hash: 0
            }];

            for (let item of json_data) {
                if (
                    !item["Hash"] ||
                    !item["Name"] ||
                    item["IsVehicleWeapon"]
                ) {
                    continue;
                }

                if (hash_blacklist_set.has(item["Hash"])) {
                    continue;
                }

                let weapon = {
                    hash: item["Hash"],
                    type_idx: -1,
                    type: "",
                    name: item["Name"],
                    throwable: false,
                    reward_hash: 0,
                    reward_ammo_hash: 0
                };

                if (
                    item["TranslatedLabel"] &&
                    item["TranslatedLabel"]["English"]
                ) {
                    weapon.name = item["TranslatedLabel"]["English"];
                }

                if (weapon.name == "Invalid" || weapon.name == "Unarmed" || !item["Category"]) {
                    continue;
                }
        
                weapon.type = item["Category"].substring(6);

                let is_gun = false;
                let is_recharge = false;

                let flags = item["Flags"];

                if (flags) {
                    for (let flag of flags) {
                        if (flag == "Gun")  {
                            is_gun = true;
                        } else if (flag == "DisplayRechargeTimeHUD") {
                            is_recharge = true;
                        } else if (flag == "Thrown") {
                            weapon.throwable = true;
                        }
                    }
                }

                if (weapon.type == "MELEE" || weapon.type == "UNARMED" || is_gun)
                {
                    weapon.reward_hash = joaat("REWARD_" + item["Name"]);
        
                    if (is_gun && !is_recharge)
                    {
                        let weapon_id = item["Name"].substring(7);
                        weapon.reward_ammo_hash = joaat("REWARD_AMMO_" + weapon_id);
                    }
                }

                weapon_type_set.add(weapon.type);
    
                filtered_items.push(weapon);
            }

            filtered_items.sort((a, b) => {
                if (a.name < b.name) return -1;
                if (a.name > b.name) return 1;
                return 0;
            });
    
            let weapon_type_arr = [...weapon_type_set];
            weapon_type_arr.sort();
    
            let weapon_type_map = {};
            for (let type_idx in weapon_type_arr)
            {
                weapon_type_map[weapon_type_arr[type_idx]] = type_idx;
            }

            for (let weapon of filtered_items)
            {
                if (weapon.type) {
                    weapon.type_idx = weapon_type_map[weapon.type];
                }
    
                weapon_hash_map_str += `\t{ ${weapon.hash}, ${num_of_items} }, \n`;
                weapon_arr_str += `\t{ ${weapon.hash}, ${weapon.type_idx}, "${weapon.name}", ${weapon.throwable}, ${weapon.reward_hash}, ${weapon.reward_ammo_hash} }, \n`;
                num_of_items++;
            }
    
            for (let weapon_type of weapon_type_arr)
            {
                weapon_type_str += `\t"${weapon_type}", \n`
            }
    
            weapon_hash_map_str = remove_last_n(weapon_hash_map_str, 3);
            weapon_hash_map_str += `\n};\n\n`;
    
            weapon_arr_str = remove_last_n(weapon_arr_str, 3);
            weapon_arr_str += `\n};\n\n`;
    
            weapon_type_str = remove_last_n(weapon_type_str, 3);
            weapon_type_str += `\n};\n\n`;

            return '#include "gta_data_service.hpp"\n\n' + weapon_arr_str + weapon_hash_map_str + weapon_type_str;
        }
    );
}

async function gen_files() {
    await gen_objects();
    await gen_peds();
    await gen_vehicles();
    await gen_weapon();
}

gen_files();