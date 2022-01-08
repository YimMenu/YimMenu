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
			script::get_current()->yield();

			auto veh_idx_global = mobile::vehicle_global.at(i, 142);

			Hash hash = *veh_idx_global.at(66).as<Hash*>();
			auto& it = m_pv_lookup.find(i);

			if (STREAMING::IS_MODEL_A_VEHICLE(hash))
			{
				auto veh = std::make_unique<PersonalVehicle>(i, veh_idx_global);

				if (it != m_pv_lookup.end())
				{
					m_personal_vehicles.erase(it->second);

					it->second = veh->get_display_name();
					m_personal_vehicles.emplace(veh->get_display_name(), std::move(veh));

					continue;
				}

				m_pv_lookup.emplace(i, veh->get_display_name());
				m_personal_vehicles.emplace(veh->get_display_name(), std::move(veh));

				continue;
			}

			if (it != m_pv_lookup.end())
			{
				m_personal_vehicles.erase(it->second);
				m_pv_lookup.erase(i);
			}
		}
	}
}