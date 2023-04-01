#pragma once
#include "gta/enums.hpp"

#define MAX_VEHICLE_DOORS 6
#define MAX_VEHICLE_LOCK_STATES 11
#define VEH_OP_ANIM_DICT "ANIM@MP_PLAYER_INTMENU@KEY_FOB@"
#define VEH_OP_ANIM "FOB_CLICK"

namespace big
{

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
		int headlights,
			 highbeams;
	};

	class vehicle_control
	{
	private:
		controlled_vehicle update_vehicle(Vehicle veh);
		void keep_controlled_vehicle_data_updated(controlled_vehicle& veh);
	public:
		controlled_vehicle m_controlled_vehicle;
		std::map<int, std::string_view> radiostations;
		bool controlled_vehicle_exists;

		void animated_vehicle_operation(Ped ped);
		void operate_door(eDoorId, bool);
		void operate_lights(bool headlights, bool highbeams);
		void operate_neons(int index, bool toggle);
		void tick();
	};

	inline vehicle_control g_vehicle_control_service;
}