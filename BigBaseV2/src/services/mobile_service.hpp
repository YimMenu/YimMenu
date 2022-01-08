#pragma once

namespace big
{
	class script_global;

	class PersonalVehicle
	{
		std::string m_name;
		int m_id;
		Hash m_hash;
		int* m_state_bitfield;

	public:
		PersonalVehicle(int idx, script_global vehicle_idx);

		std::string get_display_name();
		Hash get_hash();
		int get_id();

		void summon();
	};

	class mobile_service
	{
	public:
		mobile_service();
		~mobile_service();

		void register_vehicles();

		std::map<std::string, std::unique_ptr<PersonalVehicle>> m_personal_vehicles;
		std::map<int, std::string> m_pv_lookup;

	};

	class mobile_service;
	inline mobile_service* g_mobile_service{};
}