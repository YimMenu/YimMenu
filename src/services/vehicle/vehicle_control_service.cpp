#include "vehicle_control_service.hpp"

#include "backend/looped_command.hpp"
#include "gui.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/pathfind.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "util/mobile.hpp"

namespace big
{
	class vehicle_control_command : looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			g_gui->override_mouse(true);
		}

		virtual void on_tick() override
		{
			if (!g_gui->mouse_override())
			{
				g_gui->override_mouse(true);
			}
		}

		virtual void on_disable() override
		{
			g_gui->override_mouse(false);
		}
	};

	vehicle_control_command g_vehicle_control("vehiclecontrol", "VEHICLE_CONTROLLER"_T.data(), "VEHICLE_CONTROLLER_DESC"_T.data(),
	    g.window.vehicle_control.opened);

	void update_controlled_vehicle_doors(controlled_vehicle& veh)
	{
		vehicle_door veh_door{};

		for (int i = 0; i < MAX_VEHICLE_DOORS; i++)
		{
			if (!VEHICLE::GET_IS_DOOR_VALID(veh.handle, i))
			{
				veh.doors[i].valid = false;
				continue;
			}

			veh_door.valid     = true;
			veh_door.id        = (eDoorId)i;
			veh_door.lock_state = (eVehicleLockState)VEHICLE::GET_VEHICLE_INDIVIDUAL_DOOR_LOCK_STATUS(veh.handle, i);
			veh_door.open      = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh.handle, i) > 0;
			veh_door.doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh.handle, i);

			veh.doors[i] = veh_door;
		}

		veh.lock_state = (eVehicleLockState)VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(veh.handle);
	}

	void update_controlled_vehicle_lights(controlled_vehicle& veh)
	{
		VEHICLE::GET_VEHICLE_LIGHTS_STATE(veh.handle, (BOOL*)&veh.headlights, (BOOL*)&veh.highbeams);

		for (int i = 0; i < 4; i++)
			veh.neons[i] = VEHICLE::GET_VEHICLE_NEON_ENABLED(veh.handle, i);
	}

	controlled_vehicle vehicle_control::update_vehicle(Vehicle veh)
	{
		if(!ENTITY::DOES_ENTITY_EXIST(veh))
			return {};
		
		controlled_vehicle new_veh{};

		new_veh.handle = veh;
		new_veh.ptr    = (CVehicle*)g_pointers->m_gta.m_handle_to_ptr(veh);
		strcpy(new_veh.model_name, HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(veh))));
		new_veh.door_count     = VEHICLE::GET_NUMBER_OF_VEHICLE_DOORS(veh);
		new_veh.lock_state     = (eVehicleLockState)VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(veh);
		new_veh.is_convertible = VEHICLE::IS_VEHICLE_A_CONVERTIBLE(veh, 0);

		update_controlled_vehicle_doors(new_veh);
		update_controlled_vehicle_lights(new_veh);

		return new_veh;
	}

	void vehicle_control::keep_controlled_vehicle_data_updated(controlled_vehicle& veh)
	{
		if (!m_controlled_vehicle_exists)
			return;

		update_controlled_vehicle_doors(veh);
		update_controlled_vehicle_lights(veh);

		veh.convertible_state = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(veh.handle);
		veh.engine           = VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(veh.handle);
		
		if (g.window.vehicle_control.render_distance_on_veh
		    && math::distance_between_vectors(self::pos, ENTITY::GET_ENTITY_COORDS(m_controlled_vehicle.handle, true)) > 10.f)
			vehicle_control::render_distance_on_vehicle();
	}

	/*
	* Imitated from freemode.c script, findable by searching for MISC::GET_HASH_KEY("BONEMASK_HEAD_NECK_AND_R_ARM");
	* Script uses TASK::TASK_SCRIPTED_ANIMATION but can be dissected to use as follows
	*/
	void vehicle_control::vehicle_operation(std::function<void()> operation)
	{
		if (g.window.vehicle_control.operation_animation)
		{
			ped::ped_play_animation(self::ped, VEH_OP_ANIM_DICT, VEH_OP_ANIM, 4, -4, -1, 48, 0, false);
			AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "Remote_Control_Fob", self::ped, "PI_Menu_Sounds", true, 0);
			script::get_current()->yield(100ms);
			for (int i = 0; i < 35 && ENTITY::IS_ENTITY_PLAYING_ANIM(self::ped, VEH_OP_ANIM_DICT, VEH_OP_ANIM, 3); i++)
			{
				script::get_current()->yield(10ms);
			}
		}

		if (entity::take_control_of(m_controlled_vehicle.handle))
			operation();
	}

	void vehicle_control::driver_tick()
	{
		if (!m_controlled_vehicle_exists)
			return;

		if (ENTITY::DOES_ENTITY_EXIST(m_driver))
		{
			int task = 0;
			for (int i = 0; i < ped::task_names.size(); i++)
			{
				if (TASK::GET_IS_TASK_ACTIVE(m_driver, i))
					task = i;
			}
			strcpy(m_currentask, ped::task_names.at(task));

			if (!m_driver_performing_task)
			{
				if (entity::take_control_of(m_driver))
				{
					pathfind::remove_navmesh_required_areas();
					entity::delete_entity(m_driver);
				}
			}
			else
			{
				if (math::distance_between_vectors(m_destination, ENTITY::GET_ENTITY_COORDS(m_driver, true)) < 10.f || math::distance_between_vectors(self::pos, ENTITY::GET_ENTITY_COORDS(m_driver, true)) < 10.f)
				{
					m_driver_performing_task = false;
					VEHICLE::BRING_VEHICLE_TO_HALT(m_controlled_vehicle.handle, 6.f, 5, false);
					pathfind::remove_navmesh_required_areas();
				}

				if (strcmp(m_currentask, "CTaskInVehicleBasic") == 0)
				{
					TASK::TASK_VEHICLE_DRIVE_TO_COORD(m_driver,
					    m_controlled_vehicle.handle,
					    m_destination.x,
					    m_destination.y,
					    m_destination.z,
					    100.f,
					    0,
					    0,
					    786468,
					    4.f,
					    5.f);
					//LOG(INFO) << "Navmesh probably failed, issiuing regular task ";
					g_notification_service.push_warning("VEHICLE_CONTROLLER"_T.data(),
					    "VEHICLE_CONTROLLER_TRY_ALT_PATHFINDING"_T.data());
					script::get_current()->yield(500ms);
				}

				m_distance_to_destination =
				    math::distance_between_vectors(m_destination, ENTITY::GET_ENTITY_COORDS(m_controlled_vehicle.handle, true));
			}
		}
	}

	bool vehicle_control::ensure_driver()
	{
		if (!m_controlled_vehicle_exists)
		{
			if (ENTITY::DOES_ENTITY_EXIST(m_driver) && entity::take_control_of(m_driver))
			{
				entity::delete_entity(m_driver);
			}
			return false;
		}


		if (!ENTITY::DOES_ENTITY_EXIST(m_driver))
		{
			//LOG(INFO) << "Driver didnt exist, creating one";
			m_driver = ped::spawn(PED_TYPE_CIVMALE,
			    "s_m_y_devinsec_01"_J,
			    -1,
			    ENTITY::GET_ENTITY_COORDS(m_controlled_vehicle.handle, 1),
			    0,
			    true);
		}

		if (entity::take_control_of(m_driver))
		{
			if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(m_controlled_vehicle.handle, (int)eVehicleSeats::DRIVER, true) != m_driver)
			{
				//LOG(INFO) << "Driver wasnt in the driver seat";
				PED::SET_PED_INTO_VEHICLE(m_driver, m_controlled_vehicle.handle, (int)eVehicleSeats::DRIVER);
			}

			//LOG(INFO) << "Changing driver attributes";
			ENTITY::SET_ENTITY_INVINCIBLE(m_driver, true);
			ENTITY::SET_ENTITY_VISIBLE(m_driver, false, false);
			PED::SET_PED_COMBAT_ATTRIBUTES(m_driver, 3, false);
			PED::SET_PED_COMBAT_ATTRIBUTES(m_driver, 1, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(m_driver, 58, true);
			PED::SET_PED_CONFIG_FLAG(m_driver, 294, true);
			PED::SET_PED_CONFIG_FLAG(m_driver, 208, true);
			PED::SET_PED_CONFIG_FLAG(m_driver, 229, true);
			PED::SET_PED_CONFIG_FLAG(m_driver, 422, true);
			PED::SET_PED_CONFIG_FLAG(m_driver, 123, true);
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(m_driver, true);
			PED::SET_PED_CAN_BE_DRAGGED_OUT(m_driver, false);
			PED::SET_PED_CAN_BE_SHOT_IN_VEHICLE(m_driver, false);
			PED::SET_DRIVER_ABILITY(m_driver, 1);
			PED::SET_DRIVER_RACING_MODIFIER(m_driver, 1);

			PED::CLEAR_RELATIONSHIP_BETWEEN_GROUPS(0, PED::GET_PED_RELATIONSHIP_GROUP_HASH(m_driver), PED::GET_PED_RELATIONSHIP_GROUP_HASH(self::ped));
			PED::SET_RELATIONSHIP_BETWEEN_GROUPS(0, PED::GET_PED_GROUP_INDEX(m_driver), PED::GET_PED_GROUP_INDEX(self::ped));
			PED::SET_RELATIONSHIP_BETWEEN_GROUPS(0, PED::GET_PED_GROUP_INDEX(self::ped), PED::GET_PED_GROUP_INDEX(m_driver));
			PED::SET_PED_AS_GROUP_MEMBER(m_driver, PED::GET_PED_GROUP_INDEX(self::ped));
		}

		return ENTITY::DOES_ENTITY_EXIST(m_driver);
	}

	void vehicle_control::render_distance_on_vehicle()
	{
		if (ENTITY::DOES_ENTITY_EXIST(m_controlled_vehicle.handle))
		{
			Vector3 veh_pos = ENTITY::GET_ENTITY_COORDS(m_controlled_vehicle.handle, true);
			Vector2 screen_pos{};
			GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(veh_pos.x, veh_pos.y, veh_pos.z, &screen_pos.x, &screen_pos.y);

			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::SET_TEXT_FONT(4);
			HUD::SET_TEXT_SCALE(0.3f, 0.463);
			HUD::SET_TEXT_COLOUR(0, 150, 0, 255);
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(
			    std::to_string(math::distance_between_vectors(self::pos, veh_pos)).data());
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(screen_pos.x, screen_pos.y, 0);
		}
	}


	bool vehicle_control::find_suitable_destination_near_player(Vector3& outcoords, float& heading)
	{
		Vector3 original_coords = outcoords;
		float original_heading  = heading;
		pathfind::find_closest_vehicle_node(self::pos, outcoords, heading, 0);
		for (int i = 0; i < 10 && math::distance_between_vectors(self::pos, outcoords) < 3.f; i++)
		{
			pathfind::find_closest_vehicle_node(self::pos, outcoords, heading, 0, i);
			//LOG(INFO) << "Node too close to player, iterating next closest";
		}
		//LOG(INFO) << "Searched for closest vehicle node";
		if (math::distance_between_vectors(self::pos, outcoords) > 7.f)
		{
			//LOG(INFO) << "Node was too far, trying to find safe ped pos";
			if (!pathfind::find_safe_pos_ped(self::pos, outcoords, true, 8) || math::distance_between_vectors(self::pos, outcoords) > 30.f)
			{
				//LOG(INFO) << "Couldnt find a safe ped pos";
				outcoords = original_coords;
				heading   = original_heading;
				return false;
			}
		}

		return true;
	}

	void vehicle_control::summon_vehicle()
	{
		if (!m_controlled_vehicle_exists
		    || math::distance_between_vectors(self::pos, ENTITY::GET_ENTITY_COORDS(m_controlled_vehicle.handle, true)) < 13.f)
			return;

		Vector3 behind_pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.f, -4.f, 0.f);

		if (ensure_driver() && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(self::ped, m_driver))
		{
			behind_pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.f, 4.f, 0.f);
		}

		m_driver_performing_task = true;

		if (ensure_driver())
		{
			Vector3 destination{};
			float heading{};

			if (vehicle_control::find_suitable_destination_near_player(destination, heading))
			{
				//LOG(INFO) << "Suitable destination found";
				g_notification_service.push_success("VEHICLE_CONTROLLER"_T.data(),
				    "VEHICLE_CONTROLLER_FOUND_LOCATION"_T.data());
			}
			else
			{
				//LOG(INFO) << "Couldn't find suitable destionation, defaulting to offset of player\nThis might go wrong";
				g_notification_service.push_error("VEHICLE_CONTROLLER"_T.data(),
				    "VEHICLE_CONTROLLER_FORCE_PATHFINDING"_T.data());
				destination = behind_pos;
			}

			m_destination = destination;

			Vector3 nav_mesh_region = ENTITY::GET_ENTITY_COORDS(m_driver, true);

			if (pathfind::load_navmesh_area(nav_mesh_region, m_distance_to_destination))
			{
				TASK::TASK_VEHICLE_GOTO_NAVMESH(m_driver,
				    m_controlled_vehicle.handle,
				    destination.x,
				    destination.y,
				    destination.z,
				    100.f,
				    786468,
				    4.f);
				PED::SET_PED_KEEP_TASK(m_driver, true);
			}
			else
			{
				//LOG(INFO) << "Navmesh load failed";
				g_notification_service.push_error("VEHICLE_CONTROLLER"_T.data(), "VEHICLE_CONTROLLER_NAVMESH_FAILURE"_T.data());
				m_driver_performing_task = false;
			}
		}
	}

	void vehicle_control::get_last_driven_vehicle()
	{
		//Check in memory for vehicle
		if (g_local_player)
		{
			if (g_local_player->m_vehicle)
			{
				if (m_controlled_vehicle.handle != g_pointers->m_gta.m_ptr_to_handle(g_local_player->m_vehicle))
					m_controlled_vehicle = vehicle_control::update_vehicle(self::veh);
			}
		}

		//Manually check if vehicle has changed
		if (ENTITY::DOES_ENTITY_EXIST(self::veh) && self::veh != m_controlled_vehicle.handle)
		{
			m_controlled_vehicle = vehicle_control::update_vehicle(self::veh);
		}

		//Manual check if there is a last driven vehicle
		if (!m_controlled_vehicle_exists && ENTITY::DOES_ENTITY_EXIST(VEHICLE::GET_LAST_DRIVEN_VEHICLE()))
			m_controlled_vehicle = vehicle_control::update_vehicle(VEHICLE::GET_LAST_DRIVEN_VEHICLE());
	}

	void vehicle_control::get_personal_vehicle()
	{
		if(ENTITY::DOES_ENTITY_EXIST(mobile::mechanic::get_personal_vehicle()))
			m_controlled_vehicle = vehicle_control::update_vehicle(mobile::mechanic::get_personal_vehicle());
	}

	void vehicle_control::get_closest_vehicle()
	{
		if(PED::IS_PED_IN_ANY_VEHICLE(self::ped, true))
			m_controlled_vehicle = vehicle_control::update_vehicle(PED::GET_VEHICLE_PED_IS_USING(self::ped));
		else
		{
			m_controlled_vehicle = vehicle_control::update_vehicle(vehicle::get_closest_to_location(self::pos, 1000));
		}
	}

	void vehicle_control::tick()
	{
		m_controlled_vehicle_exists = m_controlled_vehicle.ptr && ENTITY::DOES_ENTITY_EXIST(m_controlled_vehicle.handle);

		driver_tick();
		keep_controlled_vehicle_data_updated(m_controlled_vehicle);

		if (!g.window.vehicle_control.opened)
			return;

		switch (m_selection_mode)
		{
		case eControlledVehSelectionMode::LAST_DRIVEN: get_last_driven_vehicle(); break;
		case eControlledVehSelectionMode::PERSONAL: get_personal_vehicle(); break;
		case eControlledVehSelectionMode::CLOSEST: get_closest_vehicle(); break;
		}
	}
}
