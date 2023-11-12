#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "core/settings/vehicle.hpp"
#include "natives.hpp"
#include "util/mobile.hpp"

namespace big
{
	class vehicle_godmode : looped_command
	{
		using looped_command::looped_command;

		static constexpr uint8_t deform_god_bit = 1 << 4;

		struct orig_veh_data
		{
			uint8_t m_deform_god   = 0;
			uint32_t m_damage_bits = 0;
		};

		std::unordered_map<CVehicle*, orig_veh_data> m_orig_veh_datas;

		void restore_original_vehicle_data(CVehicle* vehicle)
		{
			if (m_orig_veh_datas.contains(vehicle))
			{
				vehicle->m_deform_god  = m_orig_veh_datas[vehicle].m_deform_god;
				vehicle->m_damage_bits = m_orig_veh_datas[vehicle].m_damage_bits;

				m_orig_veh_datas.erase(vehicle);
			}
		}

		virtual void on_tick() override
		{
			if (g_local_player)
			{
				if (auto vehicle = g_local_player->m_vehicle)
				{
					if (const auto is_not_in_vehicle = !PED::GET_PED_CONFIG_FLAG(self::ped, 62, false))
					{
						restore_original_vehicle_data(vehicle);
						return;
					}

					if (!m_orig_veh_datas.contains(vehicle))
					{
						m_orig_veh_datas[vehicle].m_deform_god  = vehicle->m_deform_god;
						m_orig_veh_datas[vehicle].m_damage_bits = vehicle->m_damage_bits;
					}

					vehicle->m_deform_god &= ~(deform_god_bit);
					vehicle->m_damage_bits = static_cast<int>(eEntityProofs::GOD);
				}
			}
		}

		virtual void on_disable() override
		{
			if (g_local_player && g_local_player->m_vehicle)
				restore_original_vehicle_data(g_local_player->m_vehicle);
		}
	};

	vehicle_godmode
	    g_vehicle_godmode("vehgodmode", "God Mode", "Prevents your vehicle from taking any form of damage", g_vehicle.god_mode);
}