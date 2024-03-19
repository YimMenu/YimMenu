#pragma once
#include "gta/enums.hpp"

namespace big
{
	constexpr auto MAX_VEHICLE_DOORS       = 6;
	constexpr auto MAX_VEHICLE_WINDOWS     = 4;
	constexpr auto MAX_VEHICLE_LOCK_STATES = 11;
	constexpr auto VEH_OP_ANIM_DICT        = "ANIM@MP_PLAYER_INTMENU@KEY_FOB@";
	constexpr auto VEH_OP_ANIM             = "FOB_CLICK";

	enum class eControlledVehSelectionMode
	{
		LAST_DRIVEN,
		PERSONAL,
		CLOSEST
	};

	struct vehicle_door
	{
		eDoorId id;
		eVehicleLockState lock_state;
		bool open;
		float doorAngle;
		bool valid;
	};

	struct vehicle_window
	{
		eWindowId id;
	};

	struct controlled_vehicle
	{
		Vehicle handle;
		CVehicle* ptr;
		char model_name[100];
		vehicle_door doors[6];
		vehicle_window windows[4];
		int door_count;
		eVehicleLockState lock_state;
		bool engine;
		bool neons[4];
		bool is_convertible;
		int convertible_state;
		bool headlights, highbeams;
	};

	class vehicle_control
	{
	private:
		controlled_vehicle update_vehicle(Vehicle veh);
		void keep_controlled_vehicle_data_updated(controlled_vehicle& veh);
		void get_last_driven_vehicle();
		void get_personal_vehicle();
		void get_closest_vehicle();

		//Autonomy
		void driver_tick();
		bool ensure_driver();
		void render_distance_on_vehicle();
		bool find_suitable_destination_near_player(Vector3& outcoords, float& heading);
		Vector3 m_destination;
		Ped m_driver;


	public:
		controlled_vehicle m_controlled_vehicle;
		bool m_controlled_vehicle_exists;
		eControlledVehSelectionMode m_selection_mode = eControlledVehSelectionMode::LAST_DRIVEN;

		//Autonomy
		bool m_driver_performing_task;
		int m_distance_to_destination;
		char m_currentask[100];

		void vehicle_operation(std::function<void()> operation);
		void summon_vehicle();

		void tick();
	};

	inline vehicle_control g_vehicle_control_service;
}