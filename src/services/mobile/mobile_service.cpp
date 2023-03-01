#include "mobile_service.hpp"

#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/mobile.hpp"

namespace big
{
	personal_vehicle::personal_vehicle(int idx, script_global vehicle_idx) :
	    m_id(idx),
	    m_vehicle_idx(vehicle_idx)
	{
		m_plate          = m_vehicle_idx.at(1).as<char*>();
		m_hash           = *m_vehicle_idx.at(66).as<Hash*>();
		m_state_bitfield = m_vehicle_idx.at(103).as<int*>();

		m_name = std::format("{} ({})", HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(m_hash)), m_plate);
	}

	std::string personal_vehicle::get_display_name() const
	{
		return m_name + "##" + std::to_string(m_id);
	}

	Hash personal_vehicle::get_hash() const
	{
		return m_hash;
	}

	int personal_vehicle::get_id() const
	{
		return m_id;
	}

	const char* personal_vehicle::get_plate() const
	{
		return m_plate;
	}

	script_global personal_vehicle::get_vehicle_idx() const
	{
		return m_vehicle_idx;
	}

	void personal_vehicle::summon() const
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

	void mobile_service::refresh_personal_vehicles()
	{
		const auto now = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(now - m_last_update) < 10s)
			return;
		m_last_update = std::chrono::high_resolution_clock::now();

		g_fiber_pool->queue_job([this] {
			register_vehicles();
		});
	}

	void mobile_service::register_vehicles()
	{
		const auto array_size = *scr_globals::vehicle_global.as<int*>();
		for (int i = 0; i < array_size; i++)
		{
			if (i % 100 == 0)
				script::get_current()->yield();

			auto veh_idx_global = scr_globals::vehicle_global.at(i, 142);

			const auto hash   = *veh_idx_global.at(66).as<Hash*>();
			const auto& it    = m_pv_lookup.find(i);
			const auto exists = it != m_pv_lookup.end();

			// double check if model is a vehicle
			if (STREAMING::IS_MODEL_A_VEHICLE(hash))
			{
				auto veh = std::make_unique<personal_vehicle>(i, veh_idx_global);

				if (exists)
				{
					// vehicle name is no longer the same, update the vehicle at that index
					if (veh->get_display_name() != it->second)
					{
						m_personal_vehicles.erase(it->second);

						it->second = veh->get_display_name();
						m_personal_vehicles.emplace(veh->get_display_name(), std::move(veh));
					}

					continue;
				}

				m_pv_lookup.emplace(i, veh->get_display_name());                     // update lookup table
				m_personal_vehicles.emplace(veh->get_display_name(), std::move(veh));// add new vehicle

				continue;
			}

			// vehicle existed at some point but no longer does
			if (exists)
			{
				m_personal_vehicles.erase(it->second);
				m_pv_lookup.erase(i);
			}
		}
	}
}