#include "vehicle_control_service.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
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

		this->controlled_vehicle_exists = veh.ptr && ENTITY::DOES_ENTITY_EXIST(veh.handle) &&
			VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh.handle));

		if (!this->controlled_vehicle_exists)
			return;

		update_controlled_vehicle_doors(veh);
		update_controlled_vehicle_lights(veh);

		veh.convertibelstate = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(veh.handle);
		veh.engine			 = VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(veh.handle);
		veh.radio			 = AUDIO::IS_VEHICLE_RADIO_ON(veh.handle);
		veh.radiochannel	 = AUDIO::GET_PLAYER_RADIO_STATION_INDEX();

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

	void vehicle_control::tick()
	{

		if (!*g_pointers->m_is_session_started || !g.window.vehicle_control.opened)
			return;

		if (ENTITY::DOES_ENTITY_EXIST(self::veh) && self::veh != this->m_controlled_vehicle.handle)
		{
			this->m_controlled_vehicle = vehicle_control::update_vehicle(self::veh);
		}

		keep_controlled_vehicle_data_updated(this->m_controlled_vehicle);
		
	}
}