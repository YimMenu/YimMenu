#include "vehicle_control_service.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "util/pathfind.hpp"
#include "backend/bool_command.hpp"

namespace big
{

	bool_command g_vehicle_control("vehiclecontrol", "Vehicle controller", "Enables/Disables the vehicle controller.",
	    g.window.vehicle_control.opened);

	void update_controlled_vehicle_doors(controlled_vehicle& veh)
	{

		vehicle_door vehdoor{};

		for (int i = 0; i < MAX_VEHICLE_DOORS; i++)
		{
			if (!VEHICLE::GET_IS_DOOR_VALID(veh.handle, i))
			{
				veh.doors[i].valid = false;
				continue;
			}

			vehdoor.valid     = true;
			vehdoor.id		  = (eDoorId) i;
			vehdoor.lockstate = (eVehicleLockState)VEHICLE::GET_VEHICLE_INDIVIDUAL_DOOR_LOCK_STATUS(veh.handle, i);
			vehdoor.open	  = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh.handle, i) > 0;
			vehdoor.doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh.handle, i);
			
			veh.doors[i] = vehdoor;
		}

		veh.lockstate = (eVehicleLockState) VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(veh.handle);
	}

	void update_controlled_vehicle_lights(controlled_vehicle& veh)
	{
		VEHICLE::GET_VEHICLE_LIGHTS_STATE(veh.handle, &veh.headlights, &veh.highbeams);

		for (int i = 0; i < 4; i++)
			veh.neons[i] = VEHICLE::GET_VEHICLE_NEON_ENABLED(veh.handle, i);
		
	}

	controlled_vehicle vehicle_control::update_vehicle(Vehicle veh)
	{
		controlled_vehicle newveh{};

		newveh.handle = veh;
		newveh.ptr = (CVehicle*)g_pointers->m_handle_to_ptr(veh);
		strcpy(newveh.model_name, HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(veh))));
		newveh.doorCount = VEHICLE::GET_NUMBER_OF_VEHICLE_DOORS(veh);
		newveh.lockstate = (eVehicleLockState)VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(veh);
		newveh.isconvertible = VEHICLE::IS_VEHICLE_A_CONVERTIBLE(veh, 0);
		update_controlled_vehicle_doors(newveh);
		update_controlled_vehicle_lights(newveh);

		for (int i = 0; i < AUDIO::GET_NUM_UNLOCKED_RADIO_STATIONS(); i++)
			this->radiostations.insert(std::pair<int, std::string_view>(i, HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(AUDIO::GET_RADIO_STATION_NAME(i))));

		return newveh;
	}

	void vehicle_control::keep_controlled_vehicle_data_updated(controlled_vehicle& veh)
	{


		if (!this->controlled_vehicle_exists)
			return;

		update_controlled_vehicle_doors(veh);
		update_controlled_vehicle_lights(veh);

		veh.convertibelstate = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(veh.handle);
		veh.engine			 = VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(veh.handle);
		veh.radio			 = AUDIO::IS_VEHICLE_RADIO_ON(veh.handle);
		veh.radiochannel	 = AUDIO::GET_PLAYER_RADIO_STATION_INDEX();

		if (g.window.vehicle_control.render_distance_on_veh && math::distance_between_vectors(self::pos, ENTITY::GET_ENTITY_COORDS(this->m_controlled_vehicle.handle, true)) > 10.f)
			vehicle_control::render_distance_on_vehicle();

	}

	/*
	* Imitated from freemode.c script, findable by searching for MISC::GET_HASH_KEY("BONEMASK_HEAD_NECK_AND_R_ARM");
	* Script uses TASK::TASK_SCRIPTED_ANIMATION but can be dissected to use as follows
	*/
	void vehicle_control::animated_vehicle_operation(Ped ped)
	{
		ped::ped_play_animation(ped, VEH_OP_ANIM_DICT, VEH_OP_ANIM, 4, -4, -1, 48, 0, false);
		AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "Remote_Control_Fob", self::ped, "PI_Menu_Sounds", true, 0);
		script::get_current()->yield(100ms);
		for (int i = 0; i < 35 && ENTITY::IS_ENTITY_PLAYING_ANIM(self::ped, VEH_OP_ANIM_DICT, VEH_OP_ANIM, 3); i++)
		{
			script::get_current()->yield(10ms);
		}
	}

	void vehicle_control::operate_door(eDoorId door, bool open)
	{
		if (g.window.vehicle_control.operation_animation)
			animated_vehicle_operation(self::ped);

		vehicle::operate_vehicle_door(this->m_controlled_vehicle.handle, door, open);
	}

	void vehicle_control::operate_lights(bool headlights, bool highbeams)
	{
		if (g.window.vehicle_control.operation_animation)
			animated_vehicle_operation(self::ped);

		vehicle::operate_vehicle_headlights(this->m_controlled_vehicle.handle, headlights, highbeams);
	}

	void vehicle_control::operate_neons(int index, bool toggle)
	{
		if (g.window.vehicle_control.operation_animation)
			animated_vehicle_operation(self::ped);

		vehicle::operate_vehicle_neons(this->m_controlled_vehicle.handle, index, toggle);
	}

	void vehicle_control::driver_tick()
	{

		if (!this->controlled_vehicle_exists)
			return;

		if (ENTITY::DOES_ENTITY_EXIST(this->driver))
		{

			if (!this->driver_performing_task)
			{
				if(entity::take_control_of(this->driver))
				{
					entity::delete_entity(this->driver);
				}
			}
			else
			{
				if (math::distance_between_vectors(this->destination, ENTITY::GET_ENTITY_COORDS(this->driver, true)) < 13.f)
				{
					this->driver_performing_task = false;
					VEHICLE::BRING_VEHICLE_TO_HALT(this->m_controlled_vehicle.handle, 6.f, 5, false);
				}

				this->distance_to_destination = math::distance_between_vectors(this->destination, ENTITY::GET_ENTITY_COORDS(this->m_controlled_vehicle.handle, true));
			}
		}
	}

	bool vehicle_control::ensure_driver()
	{

		if (!this->controlled_vehicle_exists)
		{
			if (ENTITY::DOES_ENTITY_EXIST(this->driver) && entity::take_control_of(this->driver))
			{
				entity::delete_entity(this->driver);
			}
			return false;
		}
			

		if (!ENTITY::DOES_ENTITY_EXIST(this->driver))
		{
			//LOG(INFO) << "Driver didnt exist, creating one";
			this->driver = ped::spawn(PED_TYPE_CIVMALE,
			    RAGE_JOAAT("s_m_y_devinsec_01"),
			    -1,
			    ENTITY::GET_ENTITY_COORDS(this->m_controlled_vehicle.handle, 1),
			    0,
			    true);
		}

		if (entity::take_control_of(this->driver))
		{
			if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(this->m_controlled_vehicle.handle, (int)eVehicleSeats::DRIVER, true) != this->driver)
			{
				//LOG(INFO) << "Driver wasnt in the driver seat";
				PED::SET_PED_INTO_VEHICLE(this->driver, this->m_controlled_vehicle.handle, (int)eVehicleSeats::DRIVER);
			}

			//LOG(INFO) << "Changing driver attributes";
			ENTITY::SET_ENTITY_INVINCIBLE(this->driver, true);
			ENTITY::SET_ENTITY_VISIBLE(this->driver, false, false);
			PED::SET_PED_COMBAT_ATTRIBUTES(this->driver, (int) eCombatAttributes::CA_LEAVE_VEHICLES, false);
			PED::SET_PED_COMBAT_ATTRIBUTES(this->driver, (int) eCombatAttributes::CA_USE_VEHICLE, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(this->driver, (int) eCombatAttributes::CA_DISABLE_FLEE_FROM_COMBAT, true);
			PED::SET_PED_CONFIG_FLAG(this->driver, (int) ePedConfigFlags::PCF_DisableShockingEvents, true);
			PED::SET_PED_CONFIG_FLAG(this->driver, (int) ePedConfigFlags::PCF_DisableExplosionReactions, true);
			PED::SET_PED_CONFIG_FLAG(this->driver, (int) ePedConfigFlags::PCF_DisablePanicInVehicle, true);
			PED::SET_PED_CONFIG_FLAG(this->driver, (int) ePedConfigFlags::PCF_DisableVehicleCombat, true);
			PED::SET_PED_CONFIG_FLAG(this->driver, (int) ePedConfigFlags::PCF_DisableUnarmedDrivebys, true);
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(this->driver, true);
			PED::SET_PED_CAN_BE_DRAGGED_OUT(this->driver, false);
			PED::SET_PED_CAN_BE_SHOT_IN_VEHICLE(this->driver, false);
		}

		return ENTITY::DOES_ENTITY_EXIST(this->driver);
	}

	void vehicle_control::render_distance_on_vehicle()
	{
		if (ENTITY::DOES_ENTITY_EXIST(this->m_controlled_vehicle.handle))
		{
			Vector3 vehpos = ENTITY::GET_ENTITY_COORDS(this->m_controlled_vehicle.handle, true);
			Vector2 screenpos{}; GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(vehpos.x, vehpos.y, vehpos.z, &screenpos.x, &screenpos.y);

			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::SET_TEXT_FONT(4);
			HUD::SET_TEXT_SCALE(0.3f, 0.463);
			HUD::SET_TEXT_COLOUR(0, 150, 0, 255);
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(std::to_string(math::distance_between_vectors(self::pos, vehpos)).data());
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(screenpos.x, screenpos.y, 0);
		}
	}

	void vehicle_control::summon_vehicle()
	{
		if (!this->controlled_vehicle_exists
		    || math::distance_between_vectors(self::pos, ENTITY::GET_ENTITY_COORDS(this->m_controlled_vehicle.handle, true)) < 13.f)
			return;

		
		Vector3 behindpos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.f, -4.f, 0.f);

		if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(self::ped, this->m_controlled_vehicle.handle))
		{
			behindpos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.f, 4.f, 0.f);
		}

		if (math::distance_between_vectors(self::pos, ENTITY::GET_ENTITY_COORDS(this->m_controlled_vehicle.handle, true))>
			g.window.vehicle_control.max_summon_range)
		{
			//LOG(INFO) << "Vehicle is too far, teleporting";
			this->destination = behindpos;
			ENTITY::SET_ENTITY_COORDS(this->m_controlled_vehicle.handle, behindpos.x, behindpos.y, behindpos.z, 0, 0, 0, false);
			return;
		}

		this->driver_performing_task = true;

		if (ensure_driver()) {
			Vector3 destination{};
			float heading{};

			pathfind::find_closest_vehicle_node(self::pos, destination, heading, eNodeFlags::NF_NONE);
			for (int i = 0; i < 10 && math::distance_between_vectors(self::pos, destination) < 3.f; i++)
			{	
				pathfind::find_closest_vehicle_node(self::pos, destination, heading, eNodeFlags::NF_NONE, i);
				//LOG(INFO) << "Node too close to player, iterating next closest";
			}

			//LOG(INFO) << "Searched for closest vehicle node";
			if (math::distance_between_vectors(self::pos, destination) > 7.f)
			{
				//LOG(INFO) << "Node was too far, trying to find safe ped pos";
				if (!pathfind::find_safe_pos_ped(self::pos, destination, true, eGetSafeCoordFlags::GSC_FLAG_ONLY_NETWORK_SPAWN) || math::distance_between_vectors(self::pos, destination) > 30.f)
				{
					//LOG(INFO) << "Couldnt find a safe ped pos";
					destination = behindpos;
				}
	
			}

			this->destination = destination;

			//LOG(INFO) << "Issuing task to the driver\n";
			TASK::TASK_VEHICLE_DRIVE_TO_COORD(this->driver,
			    this->m_controlled_vehicle.handle,
			    destination.x,
			    destination.y,
			    destination.z,
			    50.f,
			    (int)eDrivingStyle::DRIVINGSTYLE_RACING,
			    0,
			    (int)eDrivingMode::DRIVINGMODE_AVOIDCARS_RECKLESS,
			    4.f,
			    -1);

			PED::SET_PED_KEEP_TASK(this->driver, true);
		}

	}

	void vehicle_control::tick()
	{

		if (!*g_pointers->m_is_session_started)
			return;

		
		this->controlled_vehicle_exists = this->m_controlled_vehicle.ptr
		    && ENTITY::DOES_ENTITY_EXIST(this->m_controlled_vehicle.handle)
		    && VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(this->m_controlled_vehicle.handle));

		driver_tick();

		if (!g.window.vehicle_control.opened)
			return;

		if (ENTITY::DOES_ENTITY_EXIST(self::veh) && self::veh != this->m_controlled_vehicle.handle)
		{
			this->m_controlled_vehicle = vehicle_control::update_vehicle(self::veh);
		}

		keep_controlled_vehicle_data_updated(this->m_controlled_vehicle);
		
	}
}