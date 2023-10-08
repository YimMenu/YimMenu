#include "xml_map_service.hpp"
#include "natives.hpp"
#include "util/world_model.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"

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

	void vehicle_details(pugi::xml_node object_node, Entity ent)
	{
	}

	void ped_details(pugi::xml_node object_node, Entity ent)
	{
	}

	Entity spawn_entity(pugi::xml_node entity_node)
	{
		Entity ent                  = 0;
		auto model                  = entity_node.child("ModelHash").text().as_uint();
		
		if(!STREAMING::IS_MODEL_VALID(model))
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
		case 3: 
			ent = world_model::spawn(model, pos);
		 	break;
		case 2: 
			ent = vehicle::spawn(model, pos, 0);
			break;
		case 1:
			ent = ped::spawn(PED_TYPE_CIVMALE, model, 0, pos, 0);
			break;
		}

		script::get_current()->yield();

		if(ent)
		{
			ENTITY::SET_ENTITY_DYNAMIC(ent, dynamic);
			ENTITY::FREEZE_ENTITY_POSITION(ent, frozenpos);
			ENTITY::SET_ENTITY_VISIBLE(ent, visible, 0);
			ENTITY::SET_ENTITY_MAX_HEALTH(ent, max_health);
			ENTITY::SET_ENTITY_HEALTH(ent, health, 0);
			ENTITY::SET_ENTITY_HAS_GRAVITY(ent, gravity);
			ENTITY::SET_ENTITY_INVINCIBLE(ent, invincible);
			ENTITY::SET_ENTITY_PROOFS(ent, bullet_proof, collision_proof, explosion_proof, fire_proof, melee_proof, false, 0, 0);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, pos.x, pos.y, pos.z, false, false, false);
			ENTITY::SET_ENTITY_ROTATION(ent, rot.x, rot.y, rot.z, 2, false);
			ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(ent, only_damaged_by_player);

			if(on_fire)
				FIRE::START_ENTITY_FIRE(ent);

			if(ENTITY::IS_ENTITY_AN_OBJECT(ent))
				object_details(entity_node, ent);
			else if(ENTITY::IS_ENTITY_A_VEHICLE(ent))
				vehicle_details(entity_node, ent);
			else if(ENTITY::IS_ENTITY_A_PED(ent))
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
		auto root             = doc.child("SpoonerPlacementes");
		auto ipls_to_unload   = root.child("IPLsToRemove");
		auto ipls_to_load     = root.child("IPLsToLoad");
		auto sp_maps          = ipls_to_load.attribute("load_sp_maps").as_bool();
		auto mp_maps          = ipls_to_load.attribute("load_mp_maps").as_bool();
		auto interiors        = root.child("InteriorsToEnable");
		auto capped_interiors = root.child("InteriorsToCap");
		auto weather          = root.child("WeatherToSet");
		auto time_cycle       = root.child("TimecycleModifier");
		auto img_coords       = root.child("ImgLoadingCoords");
		Vector3 img_coords_vec;

		LOG(INFO) << "Managing IPLs...";
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

		LOG(INFO) << "Managing interiors...";
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

		if (time_cycle)
		{
			auto name     = time_cycle.text().as_string();
			auto strength = time_cycle.attribute("strength").as_float(1.0f);

			if (!std::string(name).empty())
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER(name);
				GRAPHICS::SET_TIMECYCLE_MODIFIER_STRENGTH(strength);
			}
		}

		if (img_coords)
		{
			img_coords_vec.x = img_coords.child("X").text().as_float();
			img_coords_vec.y = img_coords.child("Y").text().as_float();
			img_coords_vec.z = img_coords.child("Z").text().as_float();

			PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, img_coords_vec.x, img_coords_vec.y, img_coords_vec.z);
		}

		std::map<std::uint32_t, std::uint32_t> initial_to_current_handle_map; //Need this garbage to handle attachments.

		LOG(INFO) << "Spawning entities...";
		//Actual models to spawn
		for (auto node = root.child("Placement"); node; node = node.next_sibling("Placement"))
		{
			initial_to_current_handle_map.insert(std::pair<std::uint32_t, std::uint32_t>(node.attribute("InitialHandle").as_uint(), spawn_entity(node)));

			LOG(INFO) << "Spawning entity: " << node.attribute("ModelHash").as_uint() << " with initial handle " << node.attribute("InitialHanlde").as_uint() << std::endl;
		}
	}
}