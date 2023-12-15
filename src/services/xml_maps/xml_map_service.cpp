#include "xml_map_service.hpp"

#include "natives.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "util/world_model.hpp"

namespace big
{
	xml_map_service::xml_map_service()
	{
		g_xml_map_service = this;
	}

	xml_map_service::~xml_map_service()
	{
		g_xml_map_service = nullptr;
	}

	void xml_map_service::fetch_xml_files()
	{
		auto folder_path = g_file_manager.get_project_folder("xml_maps").get_path();

		try
		{
			for (const auto& entry : std::filesystem::directory_iterator(folder_path))
			{
				if (entry.path().extension() == ".xml")
				{
					pugi::xml_document doc;
					pugi::xml_parse_result result = doc.load_file(entry.path().c_str());

					if (result)
						m_all_xml_maps.emplace(std::pair<std::string, pugi::xml_document>(entry.path().filename().generic_string(), std::move(doc)));
					else
						LOG(WARNING) << "Failed to load XML file: " << entry.path().filename().string() << std::endl;
				}
			}
		}
		catch (const std::exception& e)
		{
			LOG(WARNING) << "Failed fetching XML maps: " << e.what() << std::endl;
		}
	}

	void manage_ipls(pugi::xml_node unload, pugi::xml_node load)
	{
		for (auto node = unload.first_child(); node; node = node.next_sibling())
		{
			auto name = node.text().as_string();
			if (STREAMING::IS_IPL_ACTIVE(name))
				STREAMING::REMOVE_IPL(name);
		}

		for (auto node = load.first_child(); node; node = node.next_sibling())
		{
			auto name = node.text().as_string();
			if (!STREAMING::IS_IPL_ACTIVE(name))
				STREAMING::REQUEST_IPL(name);
		}
	}

	void manage_interiors(pugi::xml_node interiors, pugi::xml_node cap)
	{
		for (auto node = interiors.first_child(); node; node = node.next_sibling())
		{
			auto enabled  = node.attribute("enable").as_bool();
			auto interior = node.attribute("id").as_int(-1);

			if (interior == -1)
			{
				if (node.attribute("X"))
				{
					interior = INTERIOR::GET_INTERIOR_AT_COORDS(node.attribute("X").as_float(),
					    node.attribute("Y").as_float(),
					    node.attribute("Z").as_float());
				}
				else if (node.child("X"))
				{
					interior = INTERIOR::GET_INTERIOR_AT_COORDS(node.child("X").text().as_float(),
					    node.child("Y").text().as_float(),
					    node.child("Z").text().as_float());
				}
			}

			if (INTERIOR::IS_VALID_INTERIOR(interior))
			{
				if (enabled)
				{
					INTERIOR::PIN_INTERIOR_IN_MEMORY(interior);
					if (INTERIOR::IS_INTERIOR_DISABLED(interior))
						INTERIOR::DISABLE_INTERIOR(interior, false);

					for (auto prop = node.child("InteriorProp"); prop; prop = prop.next_sibling("InteriorProp"))
					{
						auto name = prop.attribute("name").as_string();
						if (!std::string(name).empty())
						{
							if (prop.attribute("enable").as_bool(true))
								INTERIOR::ACTIVATE_INTERIOR_ENTITY_SET(interior, name);
							else
								INTERIOR::DEACTIVATE_INTERIOR_ENTITY_SET(interior, name);
						}
					}

					INTERIOR::REFRESH_INTERIOR(interior);
				}
				else
				{
					if (!INTERIOR::IS_INTERIOR_DISABLED(interior))
						INTERIOR::DISABLE_INTERIOR(interior, true);
				}
			}
		}

		for (auto node = cap.first_child(); node; node = node.next_sibling())
		{
			auto capped   = node.attribute("cap").as_bool();
			auto interior = node.attribute("id").as_int(-1);

			if (interior == -1)
			{
				if (node.attribute("X"))
				{
					interior = INTERIOR::GET_INTERIOR_AT_COORDS(node.attribute("X").as_float(),
					    node.attribute("Y").as_float(),
					    node.attribute("Z").as_float());
				}
				else if (node.child("X"))
				{
					interior = INTERIOR::GET_INTERIOR_AT_COORDS(node.child("X").text().as_float(),
					    node.child("Y").text().as_float(),
					    node.child("Z").text().as_float());
				}
			}

			if (INTERIOR::IS_VALID_INTERIOR(interior))
			{
				INTERIOR::CAP_INTERIOR(interior, capped);
			}
		}
	}

	void object_details(pugi::xml_node object_node, Entity ent)
	{
		OBJECT::SET_OBJECT_TINT_INDEX(ent, object_node.child("TextureVariation").text().as_int());
	}

	void vehicle_details(pugi::xml_node vehicle_node, Entity ent)
	{
		auto properties = vehicle_node.child("VehicleProperties");
		auto colors     = properties.child("Colours");

		auto primary_color   = colors.child("Primary").text().as_int();
		auto secondary_color = colors.child("Secondary").text().as_int();
		auto pearl_color     = colors.child("Pearl").text().as_int();
		auto rim_color       = colors.child("Rim").text().as_int();
		auto tyre_smoke_r    = colors.child("tyreSmoke_R").text().as_int();
		auto tyre_smoke_g    = colors.child("tyreSmoke_G").text().as_int();
		auto tyre_smoke_b    = colors.child("tyreSmoke_B").text().as_int();
		auto lr_interior     = colors.child("LrInterior").text().as_int();
		auto lr_dashboard    = colors.child("LrDashboard").text().as_int();

		VEHICLE::SET_VEHICLE_COLOURS(ent, primary_color, secondary_color);
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(ent, pearl_color, -1);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(ent, rim_color);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(ent, tyre_smoke_r, tyre_smoke_g, tyre_smoke_b);

		if (auto neon_node = properties.child("Neons"); !neon_node.empty())
		{
			bool left  = neon_node.child("Left").text().as_bool();
			bool right = neon_node.child("Right").text().as_bool();
			bool front = neon_node.child("Front").text().as_bool();
			bool back  = neon_node.child("Back").text().as_bool();
			int r      = neon_node.child("R").text().as_int();
			int g      = neon_node.child("G").text().as_int();
			int b      = neon_node.child("B").text().as_int();

			VEHICLE::SET_VEHICLE_NEON_ENABLED(ent, 0, left);
			VEHICLE::SET_VEHICLE_NEON_ENABLED(ent, 1, right);
			VEHICLE::SET_VEHICLE_NEON_ENABLED(ent, 2, front);
			VEHICLE::SET_VEHICLE_NEON_ENABLED(ent, 3, back);
			VEHICLE::SET_VEHICLE_NEON_COLOUR(ent, r, g, b);
		}

		auto number_plate_text  = properties.child("NumberPlateText").text().as_string();
		auto number_plate_index = properties.child("NumberPlateIndex").text().as_int();
		auto wheel_type         = properties.child("WheelType").text().as_int();
		auto wheels_invisible   = properties.child("WheelsInvisible").text().as_bool();
		auto engine_sound_name  = properties.child("EngineSoundName").text().as_string();
		auto window_tint        = properties.child("WindowTint").text().as_int();
		auto bulletproof_tyres  = properties.child("BulletProofTyres").text().as_bool();
		auto dirt_level         = properties.child("DirtLevel").text().as_float();
		auto paint_fade         = properties.child("PaintFade").text().as_float();
		auto roof_state         = properties.child("RoofState").text().as_int();
		auto siren_active       = properties.child("SirenActive").text().as_bool();
		auto engine_on          = properties.child("EngineOn").text().as_bool();
		auto engine_health      = properties.child("EngineHealth").text().as_float();
		auto lights_on          = properties.child("LightsOn").text().as_bool();
		auto is_radio_loud      = properties.child("IsRadioLoud").text().as_int();
		auto lock_status        = properties.child("LockStatus").text().as_int();
		auto livery             = properties.child("Livery").text().as_int();

		VEHICLE::SET_VEHICLE_LIVERY(ent, livery);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(ent, (PCHAR)number_plate_text);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(ent, number_plate_index);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(ent, wheel_type);
		VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(ent, !bulletproof_tyres);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(ent, dirt_level);
		VEHICLE::SET_CONVERTIBLE_ROOF_LATCH_STATE(ent, roof_state);
		VEHICLE::SET_VEHICLE_SIREN(ent, siren_active);
		VEHICLE::SET_VEHICLE_ENGINE_ON(ent, engine_on, false, false);
		VEHICLE::SET_VEHICLE_ENGINE_HEALTH(ent, engine_health);
		VEHICLE::SET_VEHICLE_LIGHTS(ent, lights_on ? 3 : 4);
		VEHICLE::SET_VEHICLE_DOORS_LOCKED(ent, lock_status);

		if (auto doors_node = properties.child("DoorsOpen"); !doors_node.empty())
		{
			bool back_left   = doors_node.child("BackLeftDoor").text().as_bool();
			bool back_right  = doors_node.child("BackRightDoor").text().as_bool();
			bool front_left  = doors_node.child("FrontLeftDoor").text().as_bool();
			bool front_right = doors_node.child("FrontRightDoor").text().as_bool();
			bool hood        = doors_node.child("Hood").text().as_bool();
			bool trunk       = doors_node.child("Trunk").text().as_bool();
			bool trunk2      = doors_node.child("Trunk2").text().as_bool();

			if (back_left)
				VEHICLE::SET_VEHICLE_DOOR_OPEN(ent, 2, 0, false);
			if (back_right)
				VEHICLE::SET_VEHICLE_DOOR_OPEN(ent, 3, 0, false);
			if (front_left)
				VEHICLE::SET_VEHICLE_DOOR_OPEN(ent, 0, 0, false);
			if (front_right)
				VEHICLE::SET_VEHICLE_DOOR_OPEN(ent, 1, 0, false);
			if (hood)
				VEHICLE::SET_VEHICLE_DOOR_OPEN(ent, 4, 0, false);
			if (trunk)
				VEHICLE::SET_VEHICLE_DOOR_OPEN(ent, 5, 0, false);
			if (trunk2)
				VEHICLE::SET_VEHICLE_DOOR_OPEN(ent, 6, 0, false);
		}

		if (auto doors_broken_node = properties.child("DoorsBroken"); !doors_broken_node.empty())
		{
			bool back_left_broken   = doors_broken_node.child("BackLeftDoor").text().as_bool();
			bool back_right_broken  = doors_broken_node.child("BackRightDoor").text().as_bool();
			bool front_left_broken  = doors_broken_node.child("FrontLeftDoor").text().as_bool();
			bool front_right_broken = doors_broken_node.child("FrontRightDoor").text().as_bool();
			bool hood_broken        = doors_broken_node.child("Hood").text().as_bool();
			bool trunk_broken       = doors_broken_node.child("Trunk").text().as_bool();
			bool trunk2_broken      = doors_broken_node.child("Trunk2").text().as_bool();

			if (back_left_broken)
				VEHICLE::SET_VEHICLE_DOOR_BROKEN(ent, 2, back_left_broken);
			if (back_right_broken)
				VEHICLE::SET_VEHICLE_DOOR_BROKEN(ent, 3, back_right_broken);
			if (front_left_broken)
				VEHICLE::SET_VEHICLE_DOOR_BROKEN(ent, 0, front_left_broken);
			if (front_right_broken)
				VEHICLE::SET_VEHICLE_DOOR_BROKEN(ent, 1, front_right_broken);
			if (hood_broken)
				VEHICLE::SET_VEHICLE_DOOR_BROKEN(ent, 4, hood_broken);
			if (trunk_broken)
				VEHICLE::SET_VEHICLE_DOOR_BROKEN(ent, 5, trunk_broken);
			if (trunk2_broken)
				VEHICLE::SET_VEHICLE_DOOR_BROKEN(ent, 6, trunk2_broken);
		}

		VEHICLE::SET_VEHICLE_MOD_KIT(ent, 0);
		if (auto mods = properties.child("Mods"); !mods.empty())
		{
			int mod_type = 0;
			for (auto mod = mods.first_child(); mod; mod = mod.next_sibling())
			{
				if (mod_type >= 17 && mod_type <= 22)
				{
					VEHICLE::TOGGLE_VEHICLE_MOD(ent, mod_type, mod.text().as_bool());
					mod_type++;
					continue;
				}

				std::string text = mod.text().as_string();
				size_t comma_pos      = text.find(",");
				int first_val         = std::stoi(text.substr(0, comma_pos));

				auto mod_value = mod.child("value").text().as_int();
				VEHICLE::SET_VEHICLE_MOD(ent, mod_type, first_val, 0);
				mod_type++;
			}
		}
	}

	void ped_details(pugi::xml_node ped_node, Entity ent)
	{
		auto properties = ped_node.child("PedProperties");

		auto is_still       = properties.child("IsStill").text().as_bool();
		auto can_ragdoll    = properties.child("CanRagdoll").text().as_bool();
		auto armour         = properties.child("Armour").text().as_float();
		auto current_weapon = properties.child("CurrentWeapon").text().as_uint();

		if (is_still)
		{
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(ent);
			TASK::TASK_STAND_STILL(ent, -1);
			TASK::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ent, true);
		}

		PED::SET_PED_CAN_RAGDOLL(ent, can_ragdoll);
		PED::SET_PED_ARMOUR(ent, armour);
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ent, current_weapon, 0, true);

		auto ped_props = ped_node.child("PedProps");

		int prop_index = 0;
		for (auto prop_node : ped_props.children())
		{
			std::string prop_text = prop_node.text().as_string();
			size_t comma_pos      = prop_text.find(",");
			int first_val         = std::stoi(prop_text.substr(0, comma_pos));
			int second_val        = std::stoi(prop_text.substr(comma_pos + 1));

			PED::SET_PED_PROP_INDEX(ent, prop_index, first_val, second_val, true, 0);
			prop_index++;
		}

		auto ped_comps = ped_node.child("PedComps");

		int comp_index = 0;
		for (auto prop_node : ped_props.children())
		{
			std::string prop_text = prop_node.text().as_string();
			size_t comma_pos      = prop_text.find(",");
			int first_val         = std::stoi(prop_text.substr(0, comma_pos));
			int second_val        = std::stoi(prop_text.substr(comma_pos + 1));

			PED::SET_PED_COMPONENT_VARIATION(ent, comp_index, first_val, second_val, 0);
			comp_index++;
		}

		if (properties.child("ScenarioActive").text().as_bool())
		{
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(ent);
			TASK::TASK_START_SCENARIO_IN_PLACE(ent, properties.child("ScenarioName").text().as_string(), 0, true);
		}

		if (properties.child("AnimActive").text().as_bool())
		{
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(ent);
			ped::ped_play_animation(ent,
			    properties.child("AnimDict").text().as_string(),
			    properties.child("AnimName").text().as_string(),
			    8.0f,
			    -8.0f,
			    -1,
			    1);
		}
	}

	Entity spawn_entity(pugi::xml_node entity_node)
	{
		Entity ent = 0;
		auto model = entity_node.child("ModelHash").text().as_uint();

		if (!STREAMING::IS_MODEL_VALID(model))
		{
			LOG(WARNING) << "XML map spawner failed spawning entity: " << model << " is not a valid model" << std::endl;
		}

		auto dynamic                = entity_node.child("Dynamic").text().as_bool();
		auto frozenpos              = entity_node.child("FrozenPos").text().as_bool();
		auto visible                = entity_node.child("IsVisible").text().as_bool();
		auto max_health             = entity_node.child("MaxHealth").text().as_int();
		auto health                 = entity_node.child("Health").text().as_float();
		auto gravity                = entity_node.child("HasGravity").text().as_bool();
		auto on_fire                = entity_node.child("IsOnFire").text().as_bool();
		auto invincible             = entity_node.child("IsInvincible").text().as_bool();
		auto bullet_proof           = entity_node.child("IsBulletProof").text().as_bool();
		auto collision_proof        = entity_node.child("IsCollisionProof").text().as_bool();
		auto explosion_proof        = entity_node.child("IsExplosionProof").text().as_bool();
		auto fire_proof             = entity_node.child("IsFireProof").text().as_bool();
		auto melee_proof            = entity_node.child("IsMeleeProof").text().as_bool();
		auto only_damaged_by_player = entity_node.child("IsOnlyDamagedByPlayer").text().as_bool();
		auto position_rotation      = entity_node.child("PositionRotation");

		Vector3 pos = {position_rotation.child("X").text().as_float(),
		    position_rotation.child("Y").text().as_float(),
		    position_rotation.child("Z").text().as_float()};
		Vector3 rot = {position_rotation.child("Pitch").text().as_float(),
		    position_rotation.child("Roll").text().as_float(),
		    position_rotation.child("Yaw").text().as_float()};

		switch (entity_node.child("Type").text().as_int())
		{
		case 3: ent = world_model::spawn(model, pos); break;
		case 2: ent = vehicle::spawn(model, pos, 0); break;
		case 1: ent = ped::spawn(PED_TYPE_CIVMALE, model, 0, pos, 0); break;
		}

		if (ent)
		{
			ENTITY::SET_ENTITY_DYNAMIC(ent, dynamic);
			ENTITY::FREEZE_ENTITY_POSITION(ent, frozenpos);
			ENTITY::SET_ENTITY_VISIBLE(ent, visible, 0);
			ENTITY::SET_ENTITY_MAX_HEALTH(ent, max_health);
			ENTITY::SET_ENTITY_HEALTH(ent, health, 0, 0);
			ENTITY::SET_ENTITY_HAS_GRAVITY(ent, gravity);
			ENTITY::SET_ENTITY_INVINCIBLE(ent, invincible);
			ENTITY::SET_ENTITY_PROOFS(ent, bullet_proof, collision_proof, explosion_proof, fire_proof, melee_proof, false, 0, 0);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, pos.x, pos.y, pos.z, false, false, false);
			ENTITY::SET_ENTITY_ROTATION(ent, rot.x, rot.y, rot.z, 2, false);
			ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(ent, only_damaged_by_player);

			if (on_fire)
				FIRE::START_ENTITY_FIRE(ent);

			if (ENTITY::IS_ENTITY_AN_OBJECT(ent))
				object_details(entity_node, ent);
			else if (ENTITY::IS_ENTITY_A_VEHICLE(ent))
				vehicle_details(entity_node, ent);
			else if (ENTITY::IS_ENTITY_A_PED(ent))
				ped_details(entity_node, ent);
		}
		else
		{
			LOG(WARNING) << "XML map spawner failed spawning entity: " << model << std::endl;
		}

		return ent;
	}

	void xml_map_service::spawn_from_xml(pugi::xml_document& doc)
	{
		auto root             = doc.child("SpoonerPlacements");
		auto ipls_to_unload   = root.child("IPLsToRemove");
		auto ipls_to_load     = root.child("IPLsToLoad");
		auto sp_maps          = ipls_to_load.child("load_sp_maps").text().as_bool();
		auto mp_maps          = ipls_to_load.child("load_mp_maps").text().as_bool();
		auto interiors        = root.child("InteriorsToEnable");
		auto capped_interiors = root.child("InteriorsToCap");
		auto weather          = root.child("WeatherToSet");
		auto ref_coords       = root.child("ReferenceCoords");
		Vector3 reference_coords;

		manage_ipls(ipls_to_unload, ipls_to_load);

		if (sp_maps)
		{
			MISC::SET_INSTANCE_PRIORITY_MODE(true);
			DLC::ON_ENTER_SP();
		}

		if (mp_maps)
		{
			MISC::SET_INSTANCE_PRIORITY_MODE(true);
			DLC::ON_ENTER_MP();
		}

		if (sp_maps || mp_maps)
			MISC::SET_INSTANCE_PRIORITY_MODE(false);

		manage_interiors(interiors, capped_interiors);

		if (weather)
		{
			auto name = weather.text().as_string();

			if (!std::string(name).empty())
			{
				MISC::CLEAR_OVERRIDE_WEATHER();
				MISC::SET_WEATHER_TYPE_OVERTIME_PERSIST(name, 3);
			}
		}

		if (ref_coords)
		{
			reference_coords.x = ref_coords.child("X").text().as_float();
			reference_coords.y = ref_coords.child("Y").text().as_float();
			reference_coords.z = ref_coords.child("Z").text().as_float();

			PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, reference_coords.x, reference_coords.y, reference_coords.z);
		}

		std::map<std::uint32_t, std::uint32_t> initial_to_current_handle_map; //Need this garbage to handle attachments.

		//Actual models to spawn
		try
		{
			for (auto node = root.child("Placement"); node; node = node.next_sibling("Placement"))
			{
				initial_to_current_handle_map.insert(
				    std::pair<std::uint32_t, std::uint32_t>(node.child("InitialHandle").text().as_uint(), spawn_entity(node)));
			}

			//Attachments
			for (auto node = root.child("Placement"); node; node = node.next_sibling("Placement"))
			{
				if (auto attachment = node.child("Attachment"))
				{
					auto attatched_to = attachment.child("AttachedTo").text().as_uint();

					if (attatched_to)
					{
						auto bone_index = attachment.child("BoneIndex").text().as_int();
						auto pos        = attachment.child("Position");
						auto rot        = attachment.child("Rotation");

						Vector3 position = {pos.child("X").text().as_float(),
						    pos.child("Y").text().as_float(),
						    pos.child("Z").text().as_float()};
						Vector3 rotation = {rot.child("Pitch").text().as_float(),
						    rot.child("Roll").text().as_float(),
						    rot.child("Yaw").text().as_float()};

						ENTITY::ATTACH_ENTITY_TO_ENTITY(
						    initial_to_current_handle_map.at(node.child("InitialHandle").text().as_uint()),
						    initial_to_current_handle_map.at(attatched_to),
						    bone_index,
						    position.x,
						    position.y,
						    position.z,
						    rotation.x,
						    rotation.y,
						    rotation.z,
						    false,
						    false,
						    false,
						    false,
						    0,
						    true,
						    0);
					}
				}
			}
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Failed spawning entities: " << e.what() << std::endl;
		}
	}
}