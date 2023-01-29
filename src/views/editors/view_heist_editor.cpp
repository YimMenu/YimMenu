#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/local_player.hpp"
#include "util/misc.hpp"

namespace big
{
	static int dch_radio_button_index = 0;
	static int cas_heist_flow = 0; 
	static int h3opt_target = 0;
	static int h3opt_bitset1 = 0;
	static int h3opt_approach = 0;
	static int h3_last_approach = 0;
	static int h3_hard_approach = 0;
	static int h3opt_crewweap = 0;
	static int h3opt_crewdriver = 0;
	static int h3opt_crewhacker = 0;
	static int h3opt_vehs = 0;
	static int h3opt_weaps = 0;
	static int h3opt_bitset0 = 0;
	static int h3opt_keylevels = 0;
	static void tab_item_diamond_casino_heist()
	{
		if (ImGui::BeginTabItem("Diamond Casino Heist"))
		{
			enum Mode
			{
				PREP_EDITOR,
			};

			ImGui::RadioButton("Prep Editor", &dch_radio_button_index, PREP_EDITOR);

			switch (dch_radio_button_index)
			{
			case PREP_EDITOR:
			{
				ImGui::Text("Make sure you have arcade set up and pay 25K to open the heist before editing");
				ImGui::Text("If the panel doesn't change, please re-enter the arcade interior");

				static bool unlocked_patrick_mcreary = false;
				unlocked_patrick_mcreary = misc::has_bit_set(&cas_heist_flow, 9);
				components::checkbox("Unlocked Patrick McReary", &unlocked_patrick_mcreary, [] { unlocked_patrick_mcreary ? local_player::stat_set_bits("$MPX_CAS_HEIST_FLOW", 9) : local_player::stat_clear_bits("$MPX_CAS_HEIST_FLOW", 9); });
				
				static bool unlocked_avi_schwartzman = false;
				unlocked_avi_schwartzman = misc::has_bit_set(&cas_heist_flow, 15);
				components::checkbox("Unlocked Avi Schwartzman", &unlocked_avi_schwartzman, [] { unlocked_avi_schwartzman ? local_player::stat_set_bits("$MPX_CAS_HEIST_FLOW", 15) : local_player::stat_clear_bits("$MPX_CAS_HEIST_FLOW", 15); });

				ImGui::BeginGroup();
				components::button("Unlock All Access Points", [] { local_player::stat_set_bits("$MPX_H3OPT_ACCESSPOINTS", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10); });
				components::button("Unlock All POI", [] { local_player::stat_set_bits("$MPX_H3OPT_POI", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9); });
				ImGui::EndGroup(); ImGui::SameLine();
				ImGui::BeginGroup();
				components::button("Reset All Access Points", [] { local_player::stat_clear_bits("$MPX_H3OPT_ACCESSPOINTS", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10); });
				components::button("Reset All POI", [] { local_player::stat_clear_bits("$MPX_H3OPT_POI", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9); });
				ImGui::EndGroup();

				static const char* targets[] = {"Cash", "Gold", "Artwork", "Diamonds"};
				components::combo("Selected Target", &h3opt_target, targets, IM_ARRAYSIZE(targets), [] { local_player::stat_set_int("$MPX_H3OPT_TARGET", h3opt_target); });

				static bool scope_out_vault_contents = false;
				scope_out_vault_contents = misc::has_bit_set(&h3opt_bitset1, 0);
				components::checkbox("Scope Out Vault Contents", &scope_out_vault_contents, [] { scope_out_vault_contents ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 0) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 0); });

				static const char* approaches[] = { "None", "Silent & Sneaky", "The Big Con", "Aggressive" };
				components::combo("Selected Approach", &h3opt_approach, approaches, IM_ARRAYSIZE(approaches), [] { local_player::stat_set_int("$MPX_H3OPT_APPROACH", h3opt_approach); });
				components::combo("Selected Last Approach", &h3_last_approach, approaches, IM_ARRAYSIZE(approaches), [] { local_player::stat_set_int("$MPX_H3_LAST_APPROACH", h3_last_approach); });
				components::combo("Selected Hard Approach", &h3_hard_approach, approaches, IM_ARRAYSIZE(approaches), [] { local_player::stat_set_int("$MPX_H3_HARD_APPROACH", h3_hard_approach); });

				static const char* gunmen[] = { "None", "Karl Abolaji 5%", "Gustavo Mota 9%", "Charlie Reed 7%", "Chester McCoy 10%", "Patrick McReary 8%", "Unknown 0%" };
				components::combo("Selected Gunman", &h3opt_crewweap, gunmen, IM_ARRAYSIZE(gunmen), [] { local_player::stat_set_int("$MPX_H3OPT_CREWWEAP", h3opt_crewweap); });
				
				static const char* drivers[] = { "None", "Karim Denz 5%", "Taliana Martinez 7%", "Eddie Toh 9%", "Zach Nelson 6%", "Chester McCoy 10%", "Unknown 0%" };
				components::combo("Selected Driver", &h3opt_crewdriver, drivers, IM_ARRAYSIZE(drivers), [] { local_player::stat_set_int("$MPX_H3OPT_CREWDRIVER", h3opt_crewdriver); });

				static const char* hackers[] = { "None", "Rickie Lukens 3%", "Christian Feltz 7%", "Yohan Blair 5%", "Avi Schwartzman 10%", "Paige Harris 9%", "Unknown 0%" };
				components::combo("Selected Hacker", &h3opt_crewhacker, hackers, IM_ARRAYSIZE(hackers), [] { local_player::stat_set_int("$MPX_H3OPT_CREWHACKER", h3opt_crewhacker); });

				static const char* karl_abolaji_weapons[] = { "Micro SMG", "Machine Pistol" };
				static const char* gustavo_mota_weapons[] = { "Rifle", "Shotgun" };
				static const char* charlie_reed_weapons[] = { "SMG", "Shotgun" };
				static const char* chester_mccoy_weapons[] = { "Mk II Shotgun", "Mk II Rifle" };
				static const char* patrick_mcreary_weapons[] = { "Combat PDW", "Rifle" };
				switch (h3opt_crewweap)
				{
				case 1: { components::combo("Selected Unmarked Weapon", &h3opt_weaps, karl_abolaji_weapons, IM_ARRAYSIZE(karl_abolaji_weapons), [] { local_player::stat_set_int("$MPX_H3OPT_WEAPS", h3opt_weaps); }); } break;
				case 2: { components::combo("Selected Unmarked Weapon", &h3opt_weaps, gustavo_mota_weapons, IM_ARRAYSIZE(gustavo_mota_weapons), [] { local_player::stat_set_int("$MPX_H3OPT_WEAPS", h3opt_weaps); }); } break;
				case 3: { components::combo("Selected Unmarked Weapon", &h3opt_weaps, charlie_reed_weapons, IM_ARRAYSIZE(charlie_reed_weapons), [] { local_player::stat_set_int("$MPX_H3OPT_WEAPS", h3opt_weaps); }); } break;
				case 4: { components::combo("Selected Unmarked Weapon", &h3opt_weaps, chester_mccoy_weapons, IM_ARRAYSIZE(chester_mccoy_weapons), [] { local_player::stat_set_int("$MPX_H3OPT_WEAPS", h3opt_weaps); }); } break;
				case 5: { components::combo("Selected Unmarked Weapon", &h3opt_weaps, patrick_mcreary_weapons, IM_ARRAYSIZE(patrick_mcreary_weapons), [] { local_player::stat_set_int("$MPX_H3OPT_WEAPS", h3opt_weaps); }); } break;
				}

				static const char* karim_denz_vehicles[] = { "Issi Classic", "Asbo", "Kanjo", "Sentinel Classic" };
				static const char* taliana_martinez_vehicles[] = { "Retinue Mk II", "Drift Yosemite", "Sugoi", "Jugular" };
				static const char* eddie_toh_vehicles[] = { "Sultan Classic", "Gauntlet Classic", "Ellie", "Komoda" };
				static const char* zach_nelson_vehicles[] = { "Manchez", "Stryder", "Defiler", "Lectro" };
				static const char* chester_mccoy_vehicles[] = { "Zhaba", "Vagrant", "Outlaw", "Everon" };
				switch (h3opt_crewdriver)
				{
				case 1: { components::combo("Selected Getaway Vehicle", &h3opt_vehs, karim_denz_vehicles, IM_ARRAYSIZE(karim_denz_vehicles), [] { local_player::stat_set_int("$MPX_H3OPT_VEHS", h3opt_vehs); }); } break;
				case 2: { components::combo("Selected Getaway Vehicle", &h3opt_vehs, taliana_martinez_vehicles, IM_ARRAYSIZE(taliana_martinez_vehicles), [] { local_player::stat_set_int("$MPX_H3OPT_VEHS", h3opt_vehs); }); } break;
				case 3: { components::combo("Selected Getaway Vehicle", &h3opt_vehs, eddie_toh_vehicles, IM_ARRAYSIZE(eddie_toh_vehicles), [] { local_player::stat_set_int("$MPX_H3OPT_VEHS", h3opt_vehs); }); } break;
				case 4: { components::combo("Selected Getaway Vehicle", &h3opt_vehs, zach_nelson_vehicles, IM_ARRAYSIZE(zach_nelson_vehicles), [] { local_player::stat_set_int("$MPX_H3OPT_VEHS", h3opt_vehs); }); } break;
				case 5: { components::combo("Selected Getaway Vehicle", &h3opt_vehs, chester_mccoy_vehicles, IM_ARRAYSIZE(chester_mccoy_vehicles), [] { local_player::stat_set_int("$MPX_H3OPT_VEHS", h3opt_vehs); }); } break;
				}

				static const char* key_levels[] = { "None", "Level 1", "Level 2" };
				components::combo("Selected Key Level", &h3opt_keylevels, key_levels, IM_ARRAYSIZE(key_levels), [] { local_player::stat_set_int("$MPX_H3OPT_KEYLEVELS", h3opt_keylevels); });
				
				ImGui::BeginGroup();

				static bool vault_keycards = false;
				vault_keycards = misc::has_bit_set(&h3opt_bitset1, 1);
				components::checkbox("Vault Keycards", &vault_keycards, [] { vault_keycards ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 1) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 1); });
				
				static bool unmarked_weapons = false;
				unmarked_weapons = misc::has_bit_set(&h3opt_bitset1, 2);
				components::checkbox("Unmarked Weapons", &unmarked_weapons, [] { unmarked_weapons ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 2) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 2); });
				
				static bool getaway_vehicles = false;
				getaway_vehicles = misc::has_bit_set(&h3opt_bitset1, 3);
				components::checkbox("Getaway Vehicles", &getaway_vehicles, [] { getaway_vehicles ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 3) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 3); });
				
				static bool hacking_device = false;
				hacking_device = misc::has_bit_set(&h3opt_bitset1, 4);
				components::checkbox("Hacking Device", &hacking_device, [] { hacking_device ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 4) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 4); });
				
				static bool nano_drone = false;
				nano_drone = misc::has_bit_set(&h3opt_bitset1, 5);
				components::checkbox("Nano Drone - Silent & Sneaky", &nano_drone, [] { nano_drone ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 5) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 5); });
				
				static bool vault_laser = false;
				vault_laser = misc::has_bit_set(&h3opt_bitset1, 6);
				components::checkbox("Vault Laser - Silent & Sneaky", &vault_laser, [] { vault_laser ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 6) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 6); });
				
				static bool vault_drills = false;
				vault_drills = misc::has_bit_set(&h3opt_bitset1, 7);
				components::checkbox("Vault Drills - The Big Con", &vault_drills, [] { vault_drills ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 7) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 7); });
				
				static bool vault_explosives = false;
				vault_explosives = misc::has_bit_set(&h3opt_bitset1, 8);
				components::checkbox("Vault Explosives - Aggressive", &vault_explosives, [] { vault_explosives ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 8) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 8); });
				
				static bool thermal_charges = false;
				thermal_charges = misc::has_bit_set(&h3opt_bitset1, 9);
				components::checkbox("Thermal Charges - Aggressive", &thermal_charges, [] { thermal_charges ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 9) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 9); });
				
				ImGui::EndGroup(); ImGui::SameLine();
				ImGui::BeginGroup();

				static bool patrol_routes = false;
				patrol_routes = misc::has_bit_set(&h3opt_bitset0, 1);
				components::checkbox("Patrol Routes", &patrol_routes, [] { patrol_routes ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 1) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 1); });
				
				static bool duggan_shipments = false;
				duggan_shipments = misc::has_bit_set(&h3opt_bitset0, 2);
				components::checkbox("Duggan Shipments", &duggan_shipments, [] { duggan_shipments ? (local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 2), local_player::stat_set_int("$MPX_H3OPT_DISRUPTSHIP", 3)) : (local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 2), local_player::stat_set_int("$MPX_H3OPT_DISRUPTSHIP", 0)); });
				
				static bool infiltration_suits = false;
				infiltration_suits = misc::has_bit_set(&h3opt_bitset0, 3);
				components::checkbox("Infiltration Suits - Silent & Sneaky", &infiltration_suits, [] { infiltration_suits ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 3) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 3); });
				
				static bool power_drills = false;
				power_drills = misc::has_bit_set(&h3opt_bitset0, 4);
				components::checkbox("Power Drills", &power_drills, [] { power_drills ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 4) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 4); });
				
				static bool emp_device = false;
				emp_device = misc::has_bit_set(&h3opt_bitset0, 5);
				components::checkbox("Emp Device - Silent & Sneaky", &emp_device, [] { emp_device ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 5) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 5); });
				
				static bool decoy_gunman = false;
				decoy_gunman = misc::has_bit_set(&h3opt_bitset0, 6);
				components::checkbox("Decoy Gunman", &decoy_gunman, [] { decoy_gunman ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 6) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 6); });
				
				static bool clean_vehicle = false;
				clean_vehicle = misc::has_bit_set(&h3opt_bitset0, 7);
				components::checkbox("Clean Vehicle", &clean_vehicle, [] { clean_vehicle ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 7) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 7); });
				
				static bool bugstars_gear = false;
				bugstars_gear = misc::has_bits_set(&h3opt_bitset0, 8, 9);
				components::checkbox("Entry Disguise - Bugstars Gear - The Big Con", &bugstars_gear, [] { bugstars_gear ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 8, 9) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 8, 9); });
				
				static bool maintenance_gear = false;
				maintenance_gear = misc::has_bits_set(&h3opt_bitset0, 10, 11);
				components::checkbox("Entry Disguise - Maintenance Gear - The Big Con", &maintenance_gear, [] { maintenance_gear ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 10, 11) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 10, 11); });
				
				static bool gruppe_sechs_gear = false;
				gruppe_sechs_gear = misc::has_bits_set(&h3opt_bitset0, 12, 13);
				components::checkbox("Entry Disguise - Gruppe Sechs Gear - The Big Con", &gruppe_sechs_gear, [] { gruppe_sechs_gear ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 12, 13) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 12, 13); });
				
				static bool after_party = false;
				after_party = misc::has_bits_set(&h3opt_bitset0, 14, 15);
				components::checkbox("Entry Disguise - After Party - The Big Con", &after_party, [] { after_party ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 14, 15) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 14, 15); });
				
				static bool noose_gear = false;
				noose_gear = misc::has_bit_set(&h3opt_bitset0, 16);
				components::checkbox("Exit Disguise - Noose Gear - The Big Con", &noose_gear, [] { noose_gear ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 16) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 16); });
				
				static bool firefighter_gear = false;
				firefighter_gear = misc::has_bit_set(&h3opt_bitset0, 17);
				components::checkbox("Exit Disguise - Firefighter Gear - The Big Con", &firefighter_gear, [] { firefighter_gear ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 17) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 17); });
				
				static bool tunnel_boring_machine = false;
				tunnel_boring_machine = misc::has_bit_set(&h3opt_bitset0, 19);
				components::checkbox("Tunnel Boring Machine - Aggressive", &tunnel_boring_machine, [] { tunnel_boring_machine ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 19) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 19); });
				
				static bool reinforced_armor = false;
				reinforced_armor = misc::has_bit_set(&h3opt_bitset0, 20);
				components::checkbox("Reinforced Armor - Aggressive", &reinforced_armor, [] { reinforced_armor ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 20) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 20); });
				
				ImGui::EndGroup();
			}
				break;
			}

			ImGui::EndTabItem();
		}
	}

	static int cph_radio_button_index = 0;
	static bool cph_ip_airstrip = false;
	static bool cph_ip_halo_jump = false;
	static bool cph_ip_west_beach = false;
	static bool cph_ip_main_dock = false;
	static bool cph_ip_north_dock = false;
	static bool cph_ip_north_drop_zone = false;
	static bool cph_ip_south_drop_zone = false;
	static bool cph_ip_drainage_tunnel = false;
	static bool cph_cep_main_gate = false;
	static bool cph_cep_north_wall = false;
	static bool cph_cep_north_gate = false;
	static bool cph_cep_south_wall = false;
	static bool cph_cep_south_gate = false;
	static bool cph_cep_drainage_tunnel = false;
	static bool cph_hard_mode = false;
	static int cph_st_cash_value = 0;
	static int cph_st_weed_value = 0;
	static int cph_st_coke_value = 0;
	static int cph_st_gold_value = 0;
	static int cph_st_paint_value = 0;
	static int cph_st_island_index[24] = {};
	static int cph_st_compound_index[8] = {};
	static int cph_h4loot_paint = 0;
	static int cph_st_island_scoped_index[24] = {};
	static int cph_st_compound_scoped_index[8] = {};
	static int cph_h4loot_paint_scoped = 0;
	static bool cph_poi_grappling_equipment1 = false;
	static bool cph_poi_grappling_equipment2 = false;
	static bool cph_poi_grappling_equipment3 = false;
	static bool cph_poi_grappling_equipment4 = false;
	static bool cph_poi_guard_clothing1 = false;
	static bool cph_poi_guard_clothing2 = false;
	static bool cph_poi_guard_clothing3 = false;
	static bool cph_poi_guard_clothing4 = false;
	static bool cph_poi_bolt_cutters1 = false;
	static bool cph_poi_bolt_cutters2 = false;
	static bool cph_poi_bolt_cutters3 = false;
	static bool cph_poi_bolt_cutters4 = false;
	static bool cph_poi_cutting_power = false;
	static bool cph_poi_power_station = false;
	static bool cph_poi_supply_truck = false;
	static bool cph_poi_control_tower = false;
	static int cph_h4cnf_grappel = 0;
	static int cph_h4cnf_uniform = 0;
	static int cph_h4cnf_boltcut = 0;
	static int cph_supply_truck_index = 0;
	static int cph_target_index = 0;
	static int cph_weapon_index = 0;
	static bool cph_scoped_target = false;
	static bool cph_approach_vehicles_submarine_kosatka = false;
	static bool cph_approach_vehicles_plane_alkonost = false;
	static bool cph_approach_vehicles_plane_velum = false;
	static bool cph_approach_vehicles_helicopter_stealth_annihilator = false;
	static bool cph_approach_vehicles_boat_patrol_boat = false;
	static bool cph_approach_vehicles_boat_longfin = false;
	static void tab_item_cayo_perico_heist()
	{
		if (ImGui::BeginTabItem("Cayo Perico Heist"))
		{
			ImGui::Text("Make sure to pay 25K to open the heist before editing");
			ImGui::Text("If the panel doesn't change, please re-enter the kosatka interior");

			enum Mode
			{
				PREP_EDITOR,
			};

			ImGui::RadioButton("Prep Editor", &cph_radio_button_index, PREP_EDITOR);

			switch (cph_radio_button_index)
			{
			case PREP_EDITOR:
			{
				if (ImGui::TreeNode("Infiltration Points & Escape Points"))
				{
					components::checkbox("Airstrip##infiltration_points", &cph_ip_airstrip, [] { cph_ip_airstrip ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 0) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 0); });
					components::checkbox("Halo Jump##infiltration_points", &cph_ip_halo_jump, [] { cph_ip_halo_jump ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 1) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 1); });
					components::checkbox("West Beach##infiltration_points", &cph_ip_west_beach, [] { cph_ip_west_beach ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 2) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 2); });
					components::checkbox("Main Dock##infiltration_points", &cph_ip_main_dock, [] { cph_ip_main_dock ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 3) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 3); });
					components::checkbox("North Dock##infiltration_points", &cph_ip_north_dock, [] { cph_ip_north_dock ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 4) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 4); });
					components::checkbox("North Drop Zone##infiltration_points", &cph_ip_north_drop_zone, [] { cph_ip_north_drop_zone ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 5) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 5); });
					components::checkbox("South Drop Zone##infiltration_points", &cph_ip_south_drop_zone, [] { cph_ip_south_drop_zone ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 6) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 6); });
					components::checkbox("Drainage Tunnel##infiltration_points", &cph_ip_drainage_tunnel, [] { cph_ip_drainage_tunnel ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 7) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 7); });
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("Compound Entry Points"))
				{
					components::checkbox("Main Gate##compound_entry_points", &cph_cep_main_gate, [] { cph_cep_main_gate ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 0) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 0); });
					components::checkbox("North Wall##compound_entry_points", &cph_cep_north_wall, [] { cph_cep_north_wall ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 1) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 1); });
					components::checkbox("North Gate##compound_entry_points", &cph_cep_north_gate, [] { cph_cep_north_gate ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 2) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 2); });
					components::checkbox("South Wall##compound_entry_points", &cph_cep_south_wall, [] { cph_cep_south_wall ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 3) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 3); });
					components::checkbox("South Gate##compound_entry_points", &cph_cep_south_gate, [] { cph_cep_south_gate ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 4) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 4); });
					components::checkbox("Drainage Tunnel##compound_entry_points", &cph_cep_drainage_tunnel, [] { cph_cep_drainage_tunnel ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 5) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 5); });
					ImGui::TreePop();
				}
				components::checkbox("Hard Mode", &cph_hard_mode, [] { cph_hard_mode ? local_player::stat_set_bits("$MPX_H4_PROGRESS", 12) : local_player::stat_clear_bits("$MPX_H4_PROGRESS", 12); });
				if (ImGui::TreeNode("Secondary Targets"))
				{
					if (ImGui::InputInt("Cash Value Per Share##secondary_targets", &cph_st_cash_value))
						g_fiber_pool->queue_job([] { local_player::stat_set_int("$MPX_H4LOOT_CASH_V", cph_st_cash_value); });
					if (ImGui::InputInt("Weed Value Per Share##secondary_targets", &cph_st_weed_value))
						g_fiber_pool->queue_job([] { local_player::stat_set_int("$MPX_H4LOOT_WEED_V", cph_st_weed_value); });
					if (ImGui::InputInt("Coke Value Per Share##secondary_targets", &cph_st_coke_value))
						g_fiber_pool->queue_job([] { local_player::stat_set_int("$MPX_H4LOOT_COKE_V", cph_st_coke_value); });
					if (ImGui::InputInt("Gold Value Per Share##secondary_targets", &cph_st_gold_value))
						g_fiber_pool->queue_job([] { local_player::stat_set_int("$MPX_H4LOOT_GOLD_V", cph_st_gold_value); });
					if (ImGui::InputInt("Paint Value Per Share##secondary_targets", &cph_st_paint_value))
						g_fiber_pool->queue_job([] { local_player::stat_set_int("$MPX_H4LOOT_PAINT_V", cph_st_paint_value); });

					static const char* secondary_targets_normal[] = { "None", "Cash", "Weed", "Coke", "Gold" };
					static const char* secondary_targets_painting[] = { "None", "Paint" };
					ImGui::Text("Island Secondary Targets");
					for (int i = 0; i < 24; i++)
					{
						components::button(std::format("{}##{} island_secondary_targets", secondary_targets_normal[cph_st_island_index[i]], i), [i]
						{
							switch ((cph_st_island_index[i] + 1) % 5)
							{
							case 0:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I", i);
							}
							break;
							case 1:
							{
								local_player::stat_set_bits("$MPX_H4LOOT_CASH_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I", i);
							}
							break;
							case 2:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I", i);
								local_player::stat_set_bits("$MPX_H4LOOT_WEED_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I", i);
							}
							break;
							case 3:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I", i);
								local_player::stat_set_bits("$MPX_H4LOOT_COKE_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I", i);
							}
							break;
							case 4:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I", i);
								local_player::stat_set_bits("$MPX_H4LOOT_GOLD_I", i);
							}
							break;
							}
						});
						if ((i + 1) % 8)
							ImGui::SameLine();
					}
					ImGui::Text("Compound Secondary Targets");
					for (int i = 0; i < 8; i++)
					{
						components::button(std::format("{}##{} compound_secondary_targets", secondary_targets_normal[cph_st_compound_index[i]], i), [i]
						{
							switch ((cph_st_compound_index[i] + 1) % 5)
							{
							case 0:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C", i);
							}
							break;
							case 1:
							{
								local_player::stat_set_bits("$MPX_H4LOOT_CASH_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C", i);
							}
							break;
							case 2:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C", i);
								local_player::stat_set_bits("$MPX_H4LOOT_WEED_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C", i);
							}
							break;
							case 3:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C", i);
								local_player::stat_set_bits("$MPX_H4LOOT_COKE_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C", i);
							}
							break;
							case 4:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C", i);
								local_player::stat_set_bits("$MPX_H4LOOT_GOLD_C", i);
							}
							break;
							}
						});
						ImGui::SameLine();
					} ImGui::Spacing();
					ImGui::Text("Painting Positions: "); ImGui::SameLine();
					for (int i = 0; i < 7; i++)
					{
						components::button(std::format("{:d}##{} painting_positions", misc::has_bit_set(&cph_h4loot_paint, i), i), [i] { !misc::has_bit_set(&cph_h4loot_paint, i) ? local_player::stat_set_bits("$MPX_H4LOOT_PAINT", i) : local_player::stat_clear_bits("$MPX_H4LOOT_PAINT", i); });
						ImGui::SameLine();
					} ImGui::Spacing();

					ImGui::Text("Island Secondary Targets Scoped Positions");
					for (int i = 0; i < 24; i++)
					{
						components::button(std::format("{:d}##{} island_secondary_targets_scoped_positions", cph_st_island_index[i] == cph_st_island_scoped_index[i] && cph_st_island_index[i] != 0, i), [i]
						{
							if (!(cph_st_island_index[i] == cph_st_island_scoped_index[i]))
							{
								switch (cph_st_island_index[i])
								{
								case 0:
								{
									local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I_SCOPED", i);
								}
									break;
								case 1:
								{
									local_player::stat_set_bits("$MPX_H4LOOT_CASH_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I_SCOPED", i);
								}
									break;
								case 2:
								{
									local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I_SCOPED", i);
									local_player::stat_set_bits("$MPX_H4LOOT_WEED_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I_SCOPED", i);
								}
									break;
								case 3:
								{
									local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I_SCOPED", i);
									local_player::stat_set_bits("$MPX_H4LOOT_COKE_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I_SCOPED", i);
								}
									break;
								case 4:
								{
									local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I_SCOPED", i);
									local_player::stat_set_bits("$MPX_H4LOOT_GOLD_I_SCOPED", i);
								}
									break;
								}
							}
							else
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I_SCOPED", i);
							}
						});
						if ((i + 1) % 8)
							ImGui::SameLine();
					}
					ImGui::Text("Compound Secondary Targets Scoped Positions");
					for (int i = 0; i < 8; i++)
					{
						components::button(std::format("{:d}##{} compound_secondary_targets_scoped_positions", cph_st_compound_index[i] == cph_st_compound_scoped_index[i] && cph_st_compound_index[i] != 0, i), [i]
						{
							if (!(cph_st_compound_index[i] == cph_st_compound_scoped_index[i]))
							{
								switch (cph_st_compound_index[i])
								{
								case 0:
								{
									local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C_SCOPED", i);
								}
									break;
								case 1:
								{
									local_player::stat_set_bits("$MPX_H4LOOT_CASH_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C_SCOPED", i);
								}
									break;
								case 2:
								{
									local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C_SCOPED", i);
									local_player::stat_set_bits("$MPX_H4LOOT_WEED_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C_SCOPED", i);
								}
									break;
								case 3:
								{
									local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C_SCOPED", i);
									local_player::stat_set_bits("$MPX_H4LOOT_COKE_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C_SCOPED", i);
								}
									break;
								case 4:
								{
									local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C_SCOPED", i);
									local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C_SCOPED", i);
									local_player::stat_set_bits("$MPX_H4LOOT_GOLD_C_SCOPED", i);
								}
									break;
								}
							}
							else
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C_SCOPED", i);
							}
						});
						ImGui::SameLine();
					} ImGui::Spacing();
					ImGui::Text("Painting Scoped Positions: "); ImGui::SameLine();
					for (int i = 0; i < 7; i++)
					{
						components::button(std::format("{:d}##{} painting_scoped_positions", misc::has_bit_set(&cph_h4loot_paint_scoped, i) && misc::has_bit_set(&cph_h4loot_paint, i), i), [i] { !misc::has_bit_set(&cph_h4loot_paint_scoped, i) ? local_player::stat_set_bits("$MPX_H4LOOT_PAINT_SCOPED", i) : local_player::stat_clear_bits("$MPX_H4LOOT_PAINT_SCOPED", i); });
						ImGui::SameLine();
					} ImGui::Spacing();

					components::button("Scoped All Island Secondary Targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_I_SCOPED", local_player::stat_get_int("$MPX_H4LOOT_CASH_I"));
						local_player::stat_set_int("$MPX_H4LOOT_WEED_I_SCOPED", local_player::stat_get_int("$MPX_H4LOOT_WEED_I"));
						local_player::stat_set_int("$MPX_H4LOOT_COKE_I_SCOPED", local_player::stat_get_int("$MPX_H4LOOT_COKE_I"));
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_I_SCOPED", local_player::stat_get_int("$MPX_H4LOOT_GOLD_I"));
					}); ImGui::SameLine();
					components::button("Scoped All Compound Secondary Targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_C_SCOPED", local_player::stat_get_int("$MPX_H4LOOT_CASH_C"));
						local_player::stat_set_int("$MPX_H4LOOT_WEED_C_SCOPED", local_player::stat_get_int("$MPX_H4LOOT_WEED_C"));
						local_player::stat_set_int("$MPX_H4LOOT_COKE_C_SCOPED", local_player::stat_get_int("$MPX_H4LOOT_COKE_C"));
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_C_SCOPED", local_player::stat_get_int("$MPX_H4LOOT_GOLD_C"));
					}); ImGui::SameLine();
					components::button("Scoped All Painting Secondary Targets", [] { local_player::stat_set_int("$MPX_H4LOOT_PAINT_SCOPED", local_player::stat_get_int("$MPX_H4LOOT_PAINT")); });
					ImGui::TreePop();
				}
				if (ImGui::TreeNode("Points Of Interest"))
				{
					ImGui::Text("Grappling Equipment Positions: "); ImGui::SameLine();
					for (int i = 0; i < 16; i++)
					{
						components::button(std::format("{:d}##{} grappling_equipment_positions", misc::has_bit_set(&cph_h4cnf_grappel, i), i), [i] { !misc::has_bit_set(&cph_h4cnf_grappel, i) ? local_player::stat_set_bits("$MPX_H4CNF_GRAPPEL", i) : local_player::stat_clear_bits("$MPX_H4CNF_GRAPPEL", i); });
						ImGui::SameLine();
					} ImGui::Spacing();
					ImGui::Text("Guard Clothing Positions: "); ImGui::SameLine();
					for (int i = 0; i < 16; i++)
					{
						components::button(std::format("{:d}##{} guard_clothing_positions", misc::has_bit_set(&cph_h4cnf_uniform, i), i), [i] { !misc::has_bit_set(&cph_h4cnf_uniform, i) ? local_player::stat_set_bits("$MPX_H4CNF_UNIFORM", i) : local_player::stat_clear_bits("$MPX_H4CNF_UNIFORM", i); });
						ImGui::SameLine();
					} ImGui::Spacing();
					ImGui::Text("Bolt Cutters Positions: "); ImGui::SameLine();
					for (int i = 0; i < 16; i++)
					{
						components::button(std::format("{:d}##{} bolt_cutters_positions", misc::has_bit_set(&cph_h4cnf_boltcut, i), i), [i] { !misc::has_bit_set(&cph_h4cnf_boltcut, i) ? local_player::stat_set_bits("$MPX_H4CNF_BOLTCUT", i) : local_player::stat_clear_bits("$MPX_H4CNF_BOLTCUT", i); });
						ImGui::SameLine();
					} ImGui::Spacing();
					static const char* supply_truck_positions[] = { "None", "Airstrip", "North Dock", "Main Dock - East", "Main Dock - West", "Compound Main Gate" };
					components::combo("Supply Truck Position", &cph_supply_truck_index, supply_truck_positions, IM_ARRAYSIZE(supply_truck_positions), [] { local_player::stat_set_int("$MPX_H4CNF_TROJAN", cph_supply_truck_index); });

					ImGui::BeginGroup();
					components::checkbox("Grappling Equipment 1", &cph_poi_grappling_equipment1, [] { cph_poi_grappling_equipment1 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 0) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 0); });
					components::checkbox("Grappling Equipment 2", &cph_poi_grappling_equipment2, [] { cph_poi_grappling_equipment2 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 1) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 1); });
					components::checkbox("Grappling Equipment 3", &cph_poi_grappling_equipment3, [] { cph_poi_grappling_equipment3 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 2) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 2); });
					components::checkbox("Grappling Equipment 4", &cph_poi_grappling_equipment4, [] { cph_poi_grappling_equipment4 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 3) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 3); });
					ImGui::EndGroup(); ImGui::SameLine();
					ImGui::BeginGroup();
					components::checkbox("Guard Clothing 1", &cph_poi_guard_clothing1, [] { cph_poi_guard_clothing1 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 4) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 4); });
					components::checkbox("Guard Clothing 2", &cph_poi_guard_clothing2, [] { cph_poi_guard_clothing2 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 5) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 5); });
					components::checkbox("Guard Clothing 3", &cph_poi_guard_clothing3, [] { cph_poi_guard_clothing3 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 6) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 6); });
					components::checkbox("Guard Clothing 4", &cph_poi_guard_clothing4, [] { cph_poi_guard_clothing4 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 7) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 7); });
					ImGui::EndGroup(); ImGui::SameLine();
					ImGui::BeginGroup();
					components::checkbox("Bolt Cutters 1", &cph_poi_bolt_cutters1, [] { cph_poi_bolt_cutters1 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 8) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 8); });
					components::checkbox("Bolt Cutters 2", &cph_poi_bolt_cutters2, [] { cph_poi_bolt_cutters2 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 9) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 9); });
					components::checkbox("Bolt Cutters 3", &cph_poi_bolt_cutters3, [] { cph_poi_bolt_cutters3 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 10) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 10); });
					components::checkbox("Bolt Cutters 4", &cph_poi_bolt_cutters4, [] { cph_poi_bolt_cutters4 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 11) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 11); });
					ImGui::EndGroup(); ImGui::SameLine();
					ImGui::BeginGroup();
					components::checkbox("Cutting Power", &cph_poi_cutting_power, [] { cph_poi_cutting_power ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 13) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 13); });
					components::checkbox("Power Station", &cph_poi_power_station, [] { cph_poi_power_station ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 14) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 14); });
					components::checkbox("Supply Truck", &cph_poi_supply_truck, [] { cph_poi_supply_truck ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 15) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 15); });
					components::checkbox("Control Tower", &cph_poi_control_tower, [] { cph_poi_control_tower ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 16) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 16); });
					ImGui::EndGroup();

					ImGui::TreePop();
				}
				static const char* targets[] = { "Sinsimito Tequila", "Ruby Necklace", "Bearer Bonds", "Pink Diamond", "Maorazo Files", "Panther Statue" };
				components::combo("Selected Target", &cph_target_index, targets, IM_ARRAYSIZE(targets), [] { local_player::stat_set_int("$MPX_H4CNF_TARGET", cph_target_index); });
				static const char* weapons[] = { "None", "Aggressoh", "Conspirator", "Crack Shot", "Saboteur", "Marksman" };
				components::combo("Selected Weapon", &cph_weapon_index, weapons, IM_ARRAYSIZE(weapons), [] { local_player::stat_set_int("$MPX_H4CNF_WEAPONS", cph_weapon_index); });
				components::checkbox("Scoped Target", &cph_scoped_target, [] { cph_scoped_target ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 0) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 0); });
				components::checkbox("Approach Vehicles - Submarine: Kosatka", &cph_approach_vehicles_submarine_kosatka, [] { cph_approach_vehicles_submarine_kosatka ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 1) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 1); });
				components::checkbox("Approach Vehicles - Plane: Alkonost", &cph_approach_vehicles_plane_alkonost, [] { cph_approach_vehicles_plane_alkonost ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 2) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 2); });
				components::checkbox("Approach Vehicles - Plane: Velum", &cph_approach_vehicles_plane_velum, [] { cph_approach_vehicles_plane_velum ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 3) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 3); });
				components::checkbox("Approach Vehicles - Helicopter: Stealth Annihilator", &cph_approach_vehicles_helicopter_stealth_annihilator, [] { cph_approach_vehicles_helicopter_stealth_annihilator ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 4) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 4); });
				components::checkbox("Approach Vehicles - Boat: Patrol Boat", &cph_approach_vehicles_boat_patrol_boat, [] { cph_approach_vehicles_boat_patrol_boat ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 5) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 5); });
				components::checkbox("Approach Vehicles - Boat: Longfin", &cph_approach_vehicles_boat_longfin, [] { cph_approach_vehicles_boat_longfin ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 6) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 6); });
			}
				break;
			}

			ImGui::EndTabItem();
		}
	}
	void view::heist_editor()
	{
		g_fiber_pool->queue_job([] 
		{
			cas_heist_flow = local_player::stat_get_int("$MPX_CAS_HEIST_FLOW");
			h3opt_target = local_player::stat_get_int("$MPX_H3OPT_TARGET");
			h3opt_bitset1 = local_player::stat_get_int("$MPX_H3OPT_BITSET1");
			h3opt_approach = local_player::stat_get_int("$MPX_H3OPT_APPROACH");
			h3_last_approach = local_player::stat_get_int("$MPX_H3_LAST_APPROACH");
			h3_hard_approach = local_player::stat_get_int("$MPX_H3_HARD_APPROACH");
			h3opt_crewweap = local_player::stat_get_int("$MPX_H3OPT_CREWWEAP");
			h3opt_crewdriver = local_player::stat_get_int("$MPX_H3OPT_CREWDRIVER");
			h3opt_crewhacker = local_player::stat_get_int("$MPX_H3OPT_CREWHACKER");
			h3opt_vehs = local_player::stat_get_int("$MPX_H3OPT_VEHS");
			h3opt_weaps = local_player::stat_get_int("$MPX_H3OPT_WEAPS");
			h3opt_keylevels = local_player::stat_get_int("$MPX_H3OPT_KEYLEVELS");

			//dch_key_level_index = local_player::stat_get_int("$MPX_H3OPT_KEYLEVELS");
			//dch_vault_keycards = local_player::stat_bits_test("$MPX_H3OPT_BITSET1", 1);
			//dch_unmarked_weapons = local_player::stat_bits_test("$MPX_H3OPT_BITSET1", 2);
			//dch_getaway_vehicles = local_player::stat_bits_test("$MPX_H3OPT_BITSET1", 3);
			//dch_hacking_device = local_player::stat_bits_test("$MPX_H3OPT_BITSET1", 4);
			//dch_nano_drone = local_player::stat_bits_test("$MPX_H3OPT_BITSET1", 5);
			//dch_vault_laser = local_player::stat_bits_test("$MPX_H3OPT_BITSET1", 6);
			//dch_vault_drills = local_player::stat_bits_test("$MPX_H3OPT_BITSET1", 7);
			//dch_vault_explosives = local_player::stat_bits_test("$MPX_H3OPT_BITSET1", 8);
			//dch_thermal_charges = local_player::stat_bits_test("$MPX_H3OPT_BITSET1", 9);
			//dch_patrol_routes = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 1);
			//dch_duggan_shipments = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 2);
			//dch_infiltration_suits = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 3);
			//dch_power_drills = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 4);
			//dch_emp_device = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 5);
			//dch_decoy_gunman = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 6);
			//dch_clean_vehicle = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 7);
			//dch_bugstars_gear = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 8, 9);
			//dch_maintenance_gear = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 10, 11);
			//dch_gruppe_sechs_gear = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 12, 13);
			//dch_after_party = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 14, 15);
			//dch_noose_gear = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 16);
			//dch_firefighter_gear = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 17);
			//dch_tunnel_boring_machine = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 19);
			//dch_reinforced_armor = local_player::stat_bits_test("$MPX_H3OPT_BITSET0", 20);

			cph_ip_airstrip = local_player::stat_bits_test("$MPX_H4CNF_APPROACH", 0);
			cph_ip_halo_jump = local_player::stat_bits_test("$MPX_H4CNF_APPROACH", 1);
			cph_ip_west_beach = local_player::stat_bits_test("$MPX_H4CNF_APPROACH", 2);
			cph_ip_main_dock = local_player::stat_bits_test("$MPX_H4CNF_APPROACH", 3);
			cph_ip_north_dock = local_player::stat_bits_test("$MPX_H4CNF_APPROACH", 4);
			cph_ip_north_drop_zone = local_player::stat_bits_test("$MPX_H4CNF_APPROACH", 5);
			cph_ip_south_drop_zone = local_player::stat_bits_test("$MPX_H4CNF_APPROACH", 6);
			cph_ip_drainage_tunnel = local_player::stat_bits_test("$MPX_H4CNF_APPROACH", 7);
			cph_cep_main_gate = local_player::stat_bits_test("$MPX_H4CNF_BS_ENTR", 0);
			cph_cep_north_wall = local_player::stat_bits_test("$MPX_H4CNF_BS_ENTR", 1);
			cph_cep_north_gate = local_player::stat_bits_test("$MPX_H4CNF_BS_ENTR", 2);
			cph_cep_south_wall = local_player::stat_bits_test("$MPX_H4CNF_BS_ENTR", 3);
			cph_cep_south_gate = local_player::stat_bits_test("$MPX_H4CNF_BS_ENTR", 4);
			cph_cep_drainage_tunnel = local_player::stat_bits_test("$MPX_H4CNF_BS_ENTR", 5);
			cph_hard_mode = local_player::stat_bits_test("$MPX_H4_PROGRESS", 12);
			cph_st_cash_value = local_player::stat_get_int("$MPX_H4LOOT_CASH_V");
			cph_st_weed_value = local_player::stat_get_int("$MPX_H4LOOT_WEED_V");
			cph_st_coke_value = local_player::stat_get_int("$MPX_H4LOOT_COKE_V");
			cph_st_gold_value = local_player::stat_get_int("$MPX_H4LOOT_GOLD_V");
			cph_st_paint_value = local_player::stat_get_int("$MPX_H4LOOT_PAINT_V");
			for (int i = 0; i < 24; i++)
			{
				if (local_player::stat_bits_test("$MPX_H4LOOT_CASH_I", i))
					cph_st_island_index[i] = 1;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_WEED_I", i))
					cph_st_island_index[i] = 2;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_COKE_I", i))
					cph_st_island_index[i] = 3;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_GOLD_I", i))
					cph_st_island_index[i] = 4;
				else
					cph_st_island_index[i] = 0;
			}
			for (int i = 0; i < 8; i++)
			{
				if (local_player::stat_bits_test("$MPX_H4LOOT_CASH_C", i))
					cph_st_compound_index[i] = 1;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_WEED_C", i))
					cph_st_compound_index[i] = 2;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_COKE_C", i))
					cph_st_compound_index[i] = 3;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_GOLD_C", i))
					cph_st_compound_index[i] = 4;
				else
					cph_st_compound_index[i] = 0;
			}
			cph_h4loot_paint = local_player::stat_get_int("$MPX_H4LOOT_PAINT");
			for (int i = 0; i < 24; i++)
			{
				if (local_player::stat_bits_test("$MPX_H4LOOT_CASH_I_SCOPED", i))
					cph_st_island_scoped_index[i] = 1;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_WEED_I_SCOPED", i))
					cph_st_island_scoped_index[i] = 2;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_COKE_I_SCOPED", i))
					cph_st_island_scoped_index[i] = 3;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_GOLD_I_SCOPED", i))
					cph_st_island_scoped_index[i] = 4;
				else
					cph_st_island_scoped_index[i] = 0;
			}
			for (int i = 0; i < 8; i++)
			{
				if (local_player::stat_bits_test("$MPX_H4LOOT_CASH_C_SCOPED", i))
					cph_st_compound_scoped_index[i] = 1;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_WEED_C_SCOPED", i))
					cph_st_compound_scoped_index[i] = 2;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_COKE_C_SCOPED", i))
					cph_st_compound_scoped_index[i] = 3;
				else if (local_player::stat_bits_test("$MPX_H4LOOT_GOLD_C_SCOPED", i))
					cph_st_compound_scoped_index[i] = 4;
				else
					cph_st_compound_scoped_index[i] = 0;
			}
			cph_h4loot_paint_scoped = local_player::stat_get_int("$MPX_H4LOOT_PAINT_SCOPED");
			cph_poi_grappling_equipment1 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 0);
			cph_poi_grappling_equipment2 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 1);
			cph_poi_grappling_equipment3 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 2);
			cph_poi_grappling_equipment4 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 3);
			cph_poi_guard_clothing1 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 4);
			cph_poi_guard_clothing2 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 5);
			cph_poi_guard_clothing3 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 6);
			cph_poi_guard_clothing4 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 7);
			cph_poi_bolt_cutters1 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 8);
			cph_poi_bolt_cutters2 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 9);
			cph_poi_bolt_cutters3 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 10);
			cph_poi_bolt_cutters4 = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 11);
			cph_poi_cutting_power = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 13);
			cph_poi_power_station = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 14);
			cph_poi_supply_truck = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 15);
			cph_poi_control_tower = local_player::stat_bits_test("$MPX_H4CNF_BS_GEN", 16);
			cph_h4cnf_grappel = local_player::stat_get_int("$MPX_H4CNF_GRAPPEL");
			cph_h4cnf_uniform = local_player::stat_get_int("$MPX_H4CNF_UNIFORM");
			cph_h4cnf_boltcut = local_player::stat_get_int("$MPX_H4CNF_BOLTCUT");
			cph_supply_truck_index = local_player::stat_get_int("$MPX_H4CNF_TROJAN");
			cph_target_index = local_player::stat_get_int("$MPX_H4CNF_TARGET");
			cph_weapon_index = local_player::stat_get_int("$MPX_H4CNF_WEAPONS");
			cph_scoped_target = local_player::stat_bits_test("$MPX_H4_MISSIONS", 0);
			cph_approach_vehicles_submarine_kosatka = local_player::stat_bits_test("$MPX_H4_MISSIONS", 1);
			cph_approach_vehicles_plane_alkonost = local_player::stat_bits_test("$MPX_H4_MISSIONS", 2);
			cph_approach_vehicles_plane_velum = local_player::stat_bits_test("$MPX_H4_MISSIONS", 3);
			cph_approach_vehicles_helicopter_stealth_annihilator = local_player::stat_bits_test("$MPX_H4_MISSIONS", 4);
			cph_approach_vehicles_boat_patrol_boat = local_player::stat_bits_test("$MPX_H4_MISSIONS", 5);
			cph_approach_vehicles_boat_longfin = local_player::stat_bits_test("$MPX_H4_MISSIONS", 6);
		});

		if (ImGui::BeginTabBar("##heist_editor_tab_bar"))
		{
			tab_item_diamond_casino_heist();
			tab_item_cayo_perico_heist();
			ImGui::EndTabBar();
		}
	}
}