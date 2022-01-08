#include "mobile_service.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "thread_pool.hpp"
#include "util/mobile.hpp"

namespace big
{
	PersonalVehicle::PersonalVehicle(int idx, script_global vehicle_idx)
	{
		m_id = idx;

		m_hash = *vehicle_idx.at(66).as<Hash*>();
		m_state_bitfield = vehicle_idx.at(103).as<int*>();

		m_name = HUD::GET_LABEL_TEXT_(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(m_hash));
	}

	std::string PersonalVehicle::get_display_name()
	{
		return m_name + "##" + std::to_string(m_id);
	}

	Hash PersonalVehicle::get_hash()
	{
		return m_hash;
	}

	int PersonalVehicle::get_id()
	{
		return m_id;
	}

	void PersonalVehicle::summon()
	{
		mobile::mechanic::summon_vehicle_by_index(m_id);
	}

	mobile_service::mobile_service()
	{
		g_mobile_service = this;
	}

	mobile_service::~mobile_service()
	{
		g_mobile_service = nullptr;
	}

	void mobile_service::register_vehicles()
	{
		for (int i = 0; i < *mobile::vehicle_global.as<int*>(); i++)
		{
			auto veh_idx_global = mobile::vehicle_global.at(i, 142);

			Hash hash = *veh_idx_global.at(66).as<Hash*>();
			if (STREAMING::IS_MODEL_A_VEHICLE(hash))
			{
				if (auto& it = m_personal_vehicles.find(i); it != m_personal_vehicles.end() && it->second.get_hash() != hash)
					it->second = PersonalVehicle(i, veh_idx_global);
				else
					m_personal_vehicles.emplace(i, PersonalVehicle(i, veh_idx_global));
			}

			script::get_current()->yield();
		}
	}
}