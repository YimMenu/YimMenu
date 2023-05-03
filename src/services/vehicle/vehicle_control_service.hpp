#pragma once

#include "backend/looped_command.hpp"

#include "gta/enums.hpp"

namespace big
{
	constexpr auto MAX_VEHICLE_DOORS       = 6;
	constexpr auto MAX_VEHICLE_LOCK_STATES = 11;
	constexpr auto VEH_OP_ANIM_DICT        = "ANIM@MP_PLAYER_INTMENU@KEY_FOB@";
	constexpr auto VEH_OP_ANIM             = "FOB_CLICK";

	struct vehicle_door
	{
		eDoorId id;
		eVehicleLockState lockstate;
		bool open;
		float doorAngle;
		bool valid;
	};

	struct controlled_vehicle
	{
		Vehicle handle;
		CVehicle* ptr;
		char model_name[100];
		vehicle_door doors[6];
		int doorCount;
		eVehicleLockState lockstate;
		bool engine;
		bool neons[4];
		bool isconvertible;
		bool radio;
		int radiochannel;
		int convertibelstate;
		int headlights;
		int highbeams;
	};

	class vehicle_control_command : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline vehicle_control_command g_vehicle_control("vehiclecontrol", "Vehicle controller", "Enables/Disables the vehicle controller.",
		    g.window.vehicle_control.opened);
	}

	class vehicle_control
	{
	private:
		Vector3 m_destination;
		Ped m_driver;

		controlled_vehicle update_vehicle(Vehicle veh);
		void keep_controlled_vehicle_data_updated(controlled_vehicle& veh);

		// Autonomy
		void driver_tick();
		bool ensure_driver();
		void render_distance_on_vehicle();
		bool find_suitable_destination_near_player(Vector3& outcoords, float& heading);


	public:
		controlled_vehicle m_controlled_vehicle;
		bool m_controlled_vehicle_exists;

		//Autonomy
		bool m_driver_performing_task;
		int m_distance_to_destination;
		char m_currentask[100];

		// Imitated from freemode.c script, findable by searching for MISC::GET_HASH_KEY("BONEMASK_HEAD_NECK_AND_R_ARM");
		// Script uses TASK::TASK_SCRIPTED_ANIMATION but can be dissected to use as follows
		void animated_vehicle_operation(Ped ped);

		void operate_door(eDoorId door, bool open);
		void operate_lights(bool headlights, bool highbeams);
		void operate_neons(int index, bool toggle);

		void summon_vehicle();

		void tick();
	};

	inline vehicle_control g_vehicle_control_service;
}
