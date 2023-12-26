#include "xml_vehicles_service.hpp"

#include "file_manager.hpp"
#include "pointers.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "util/world_model.hpp"

namespace big
{

	xml_vehicles_service::xml_vehicles_service()
	{
		g_xml_vehicles_service = this;
	}

	xml_vehicles_service::~xml_vehicles_service()
	{
		g_xml_vehicles_service = nullptr;
	}

	void xml_vehicles_service::fetch_xml_files()
	{
		auto folder_path = g_file_manager.get_project_folder("xml_vehicles").get_path();

		try
		{
			for (const auto& entry : std::filesystem::directory_iterator(folder_path))
			{
				if (entry.path().extension() == ".xml")
				{
					pugi::xml_document doc;
					pugi::xml_parse_result result = doc.load_file(entry.path().c_str());

					if (result)
						m_all_xml_vehicles.emplace(std::pair<std::string, pugi::xml_document>(entry.path().filename().generic_string(), std::move(doc)));
					else
						LOG(WARNING) << "Failed to load XML file: " << entry.path().filename().string() << std::endl;
				}
			}
		}
		catch (const std::exception& e)
		{
			LOG(WARNING) << "Failed fetching XML vehicles: " << e.what() << std::endl;
		}
	}

	void apply_vehicle_properties(Vehicle vehicle_handle, pugi::xml_node vehicle_node)
	{
		auto vehicle_properties_node = vehicle_node.child("VehicleProperties");
		auto vehicle_colors_node     = vehicle_properties_node.child("Colours");
		auto vehicle_mods_node       = vehicle_properties_node.child("Mods");
		auto vehicle_doors_node      = vehicle_properties_node.child("DoorsOpen");

		VEHICLE::SET_VEHICLE_LIVERY(vehicle_handle, vehicle_properties_node.child("Livery").text().as_int());
		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle_handle,
		    vehicle_colors_node.child("Mod1_a").text().as_int(),
		    vehicle_colors_node.child("Mod1_b").text().as_int(),
		    vehicle_colors_node.child("Mod1_c").text().as_int());
		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle_handle,
		    vehicle_colors_node.child("Mod2_a").text().as_int(),
		    vehicle_colors_node.child("Mod2_b").text().as_int());

		VEHICLE::SET_VEHICLE_COLOURS(vehicle_handle,
		    vehicle_colors_node.child("Primary").text().as_int(),
		    vehicle_colors_node.child("Secondary").text().as_int());
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle_handle,
		    vehicle_colors_node.child("Pearl").text().as_int(),
		    vehicle_colors_node.child("Rim").text().as_int());

		if (vehicle_colors_node.child("IsPrimaryColourCustom").text().as_bool())
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle_handle,
			    vehicle_colors_node.child("Cust1_R").text().as_int(),
			    vehicle_colors_node.child("Cust1_G").text().as_int(),
			    vehicle_colors_node.child("Cust1_B").text().as_int());
		if (vehicle_colors_node.child("IsSecondaryColourCustom").text().as_bool())
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle_handle,
			    vehicle_colors_node.child("Cust2_R").text().as_int(),
			    vehicle_colors_node.child("Cust2_G").text().as_int(),
			    vehicle_colors_node.child("Cust2_B").text().as_int());
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle_handle,
		    vehicle_colors_node.child("tyreSmoke_R").text().as_int(),
		    vehicle_colors_node.child("tyreSmoke_G").text().as_int(),
		    vehicle_colors_node.child("tyreSmoke_B").text().as_int());

		ENTITY::SET_ENTITY_VISIBLE(vehicle_handle, vehicle_node.child("IsVisible").text().as_bool(), true);

		for (int i = 0; i < 48; i++)
		{
			std::string_view mod_item = "_";
			VEHICLE::SET_VEHICLE_MOD_KIT(vehicle_handle, 0);
			if (i >= 17 && i <= 22)
				VEHICLE::TOGGLE_VEHICLE_MOD(vehicle_handle,
				    i,
				    vehicle_mods_node.child(std::string(mod_item).append(std::to_string(i)).data()).text().as_int());
			else
				VEHICLE::SET_VEHICLE_MOD(vehicle_handle,
				    i,
				    vehicle_mods_node.child(std::string(mod_item).append(std::to_string(i)).data()).text().as_int(),
				    true);
		}

		if (vehicle_doors_node.child("BackLeftDoor").text().as_bool())
			vehicle::operate_vehicle_door(vehicle_handle, eDoorId::VEH_EXT_DOOR_DSIDE_R, true);
		if (vehicle_doors_node.child("BackRightDoor").text().as_bool())
			vehicle::operate_vehicle_door(vehicle_handle, eDoorId::VEH_EXT_DOOR_PSIDE_R, true);
		if (vehicle_doors_node.child("FrontLeftDoor").text().as_bool())
			vehicle::operate_vehicle_door(vehicle_handle, eDoorId::VEH_EXT_DOOR_DSIDE_F, true);
		if (vehicle_doors_node.child("FrontRightDoor").text().as_bool())
			vehicle::operate_vehicle_door(vehicle_handle, eDoorId::VEH_EXT_DOOR_PSIDE_F, true);
		if (vehicle_doors_node.child("Hood").text().as_bool())
			vehicle::operate_vehicle_door(vehicle_handle, eDoorId::VEH_EXT_BONNET, true);
		if (vehicle_doors_node.child("Trunk").text().as_bool())
			vehicle::operate_vehicle_door(vehicle_handle, eDoorId::VEH_EXT_BOOT, true);
	}

	Entity ped_attachment(pugi::xml_node ped_node, Hash ped_model, Vector3 pos, Vector3 rot, Vector3 offset, Vehicle handle, int bone)
	{
		auto ped_properties_node = ped_node.child("PedProperties");

		Ped ped_handle = ped::spawn(ePedType::PED_TYPE_CIVMALE, ped_model, 0, pos, 0, *g_pointers->m_gta.m_is_session_started);

		if (entity::take_control_of(ped_handle))
		{
			PED::SET_PED_CAN_RAGDOLL(ped_handle, ped_node.child("CanRagdoll").text().as_bool(true));
			PED::SET_PED_RAGDOLL_ON_COLLISION(ped_handle, ped_node.child("CanRagdoll").text().as_bool(false));

			if (ped_node.child("HasShortHeight").text().as_bool())
				PED::SET_PED_CONFIG_FLAG(ped_handle, 223, 1);

			ENTITY::SET_ENTITY_VISIBLE(ped_handle, ped_node.child("IsVisible").text().as_bool(), true);
			ENTITY::SET_ENTITY_INVINCIBLE(ped_handle, ped_node.child("IsInvincible").text().as_bool());
			ENTITY::SET_ENTITY_DYNAMIC(ped_handle, ped_node.child("Dynamic").text().as_bool());
			ENTITY::SET_ENTITY_ALPHA(ped_handle, ped_node.child("OpacityLevel").text().as_int(), false);

			PED::SET_PED_MAX_HEALTH(ped_handle, ped_node.child("MaxHealth").text().as_float());
			ENTITY::SET_ENTITY_HEALTH(ped_handle, ped_node.child("Health").text().as_float(), false, 0);
			PED::SET_PED_ARMOUR(ped_handle, ped_properties_node.child("Armour").text().as_float());
			ENTITY::SET_ENTITY_PROOFS(ped_handle,
			    ped_node.child("IsBulletProof").text().as_bool(),
			    ped_node.child("IsFireProof").text().as_bool(),
			    ped_node.child("IsExplosionProof").text().as_bool(),
			    ped_node.child("IsCollisionProof").text().as_bool(),
			    ped_node.child("IsMeleeProof").text().as_bool(),
			    false,
			    false,
			    false);

			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped_handle, ped_node.child("IsStill").text().as_bool());
			PED::SET_PED_ARMOUR(ped_handle, ped_node.child("Armour").text().as_int());
			if (!WEAPON::HAS_PED_GOT_WEAPON(ped_handle, ped_node.child("CurrentWeapon").text().as_uint(), false))
				WEAPON::GIVE_WEAPON_TO_PED(ped_handle, ped_node.child("CurrentWeapon").text().as_uint(), 9999, true, false);
			WEAPON::SET_CURRENT_PED_WEAPON(ped_handle, ped_node.child("CurrentWeapon").text().as_uint(), true);
			PED::SET_PED_CAN_SWITCH_WEAPON(ped_handle, false);
			PED::SET_PED_COMBAT_ABILITY(ped_handle, 2);
			PED::SET_PED_COMBAT_MOVEMENT(ped_handle, 2);

			PED::SET_PED_CAN_PLAY_AMBIENT_ANIMS(ped_handle, true);
			PED::SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(ped_handle, true);
			PED::SET_PED_CAN_PLAY_GESTURE_ANIMS(ped_handle, true);
			PED::SET_PED_CAN_PLAY_VISEME_ANIMS(ped_handle, true, TRUE);

			if (ped_properties_node.child("ScenarioActive").text().as_bool())
				TASK::TASK_START_SCENARIO_IN_PLACE(ped_handle, const_cast<PCHAR>(ped_node.child("ScenarioName").text().as_string()), 0, true);

			if (ped_properties_node.child("AnimActive").text().as_bool())
				ped::ped_play_animation(ped_handle,
				    ped_properties_node.child("AnimDict").text().as_string(),
				    ped_properties_node.child("AnimName").text().as_string(),
				    4,
				    -4,
				    -1,
				    1);

			ENTITY::ATTACH_ENTITY_TO_ENTITY(ped_handle, handle, bone, offset.x, offset.y, offset.z, rot.x, rot.y, rot.z, false, false, true, false, 2, true, false);
		}

		return ped_handle;
	}

	Entity vehicle_attachment(pugi::xml_node node, Hash vehicle_model, Vector3 pos, Vector3 rot, Vector3 offset, Vehicle handle, int bone)
	{
		Vehicle vehicle_handle = vehicle::spawn(vehicle_model, pos, 0, *g_pointers->m_gta.m_is_session_started, false);

		apply_vehicle_properties(vehicle_handle, node);

		ENTITY::ATTACH_ENTITY_TO_ENTITY(vehicle_handle, handle, bone, offset.x, offset.y, offset.z, rot.x, rot.y, rot.z, false, false, true, false, 2, true, false);

		return vehicle_handle;
	}


	Entity object_attachment(pugi::xml_node attachment_node, Hash object_model, Vector3 pos, Vector3 rot, Vector3 offset, Vehicle handle, int bone)
	{
		Object object_handle = world_model::spawn(object_model, pos, *g_pointers->m_gta.m_is_session_started);
		ENTITY::SET_ENTITY_VISIBLE(object_handle, attachment_node.child("IsVisible").text().as_bool(), true);
		ENTITY::SET_ENTITY_INVINCIBLE(object_handle, attachment_node.child("IsInvincible").text().as_bool());
		ENTITY::ATTACH_ENTITY_TO_ENTITY(object_handle, handle, bone, offset.x, offset.y, offset.z, rot.x, rot.y, rot.z, false, false, true, false, 2, true, false);

		return object_handle;
	}

	Vehicle xml_vehicles_service::spawn_from_xml(pugi::xml_document& doc, Vector3 pos)
	{
		auto vehicle_node             = doc.child("Vehicle");
		auto vehicle_attachments_node = vehicle_node.child("SpoonerAttachments");

		auto vehicle_handle = vehicle::spawn(vehicle_node.child("ModelHash").text().as_uint(),
		    pos,
		    ENTITY::GET_ENTITY_HEADING(self::ped),
		    *g_pointers->m_gta.m_is_session_started,
		    false);

		ENTITY::SET_ENTITY_VISIBLE(vehicle_handle, vehicle_node.child("IsVisible").text().as_bool(), false);
		ENTITY::SET_ENTITY_INVINCIBLE(vehicle_handle, vehicle_node.child("IsInvincible").text().as_bool());
		ENTITY::SET_ENTITY_ALPHA(vehicle_handle, vehicle_node.child("OpacityLevel").text().as_int(), false);
		ENTITY::SET_ENTITY_PROOFS(vehicle_handle,
		    vehicle_node.child("IsBulletProof").text().as_bool(),
		    vehicle_node.child("IsFireProof").text().as_bool(),
		    vehicle_node.child("IsExplosionProof").text().as_bool(),
		    vehicle_node.child("IsCollisionProof").text().as_bool(),
		    vehicle_node.child("IsMeleeProof").text().as_bool(),
		    false,
		    false,
		    false);

		//Appearance
		apply_vehicle_properties(vehicle_handle, vehicle_node);

		//Attachments
		for (auto attachment_item = vehicle_attachments_node.first_child(); attachment_item;
		     attachment_item      = attachment_item.next_sibling())
		{
			//Yes the node Attachment has a node called Attachment, go figure
			auto entity_attachment_node = attachment_item.child("Attachment");
			auto entity_model           = attachment_item.child("ModelHash").text().as_uint();
			auto entity_vector_node     = attachment_item.child("PositionRotation");

			Vector3 position = {entity_vector_node.child("X").text().as_float(),
			    entity_vector_node.child("Y").text().as_float(),
			    entity_vector_node.child("Z").text().as_float()};
			Vector3 rotation = {entity_attachment_node.child("Pitch").text().as_float(),
			    entity_attachment_node.child("Roll").text().as_float(),
			    entity_attachment_node.child("Yaw").text().as_float()};
			Vector3 offset   = {entity_attachment_node.child("X").text().as_float(),
			      entity_attachment_node.child("Y").text().as_float(),
			      entity_attachment_node.child("Z").text().as_float()};
			int bone         = entity_attachment_node.child("BoneIndex").text().as_int();
			int type         = attachment_item.child("Type").text().as_int();

			Entity attachment_handle{};

			if (type == 1)
				attachment_handle = ped_attachment(attachment_item, entity_model, position, rotation, offset, vehicle_handle, bone);
			else if (type == 2)
				attachment_handle = vehicle_attachment(attachment_item, entity_model, position, rotation, offset, vehicle_handle, bone);
			else if (type == 3)
				attachment_handle = object_attachment(attachment_item, entity_model, position, rotation, offset, vehicle_handle, bone);

			if (!attachment_item.child("PtfxLopAsset").text().empty())
			{
				const char* asset = const_cast<PCHAR>(attachment_item.child("PtfxLopAsset").text().as_string());
				STREAMING::REQUEST_NAMED_PTFX_ASSET(asset);

				for (int i = 0; i < 35 && !STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(asset); i++)
					STREAMING::REQUEST_NAMED_PTFX_ASSET(asset), script::get_current()->yield();

				if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(asset))
				{
					GRAPHICS::USE_PARTICLE_FX_ASSET(asset);
					GRAPHICS::START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY(
					    const_cast<PCHAR>(attachment_item.child("PtfxLopEffect").text().as_string()),
					    attachment_handle,
					    0,
					    0,
					    0,
					    0,
					    0,
					    0,
					    1,
					    0,
					    0,
					    0,
					    1,
					    1,
					    1,
					    1);
					STREAMING::REMOVE_NAMED_PTFX_ASSET(asset);
				}
			}
		}

		return vehicle_handle;
	}
}
