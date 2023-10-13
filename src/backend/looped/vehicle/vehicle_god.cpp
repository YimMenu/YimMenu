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

		bool restore_vehicle_data_when_leaving_it(CVehicle* vehicle)
		{
			const auto is_not_in_vehicle = !PED::GET_PED_CONFIG_FLAG(self::ped, 62, false);
			if (is_not_in_vehicle)
			{
				restore_original_vehicle_data(vehicle);

				return true;
			}

			return false;
		}

		void save_original_veh_data(CVehicle* vehicle)
		{
			if (!m_orig_veh_datas.contains(vehicle))
			{
				m_orig_veh_datas[vehicle].m_deform_god  = vehicle->m_deform_god;
				m_orig_veh_datas[vehicle].m_damage_bits = vehicle->m_damage_bits;
			}
		}

		void apply_godmode_to_vehicle(CVehicle* vehicle, bool personal_vehicle = false)
		{
			if (vehicle == nullptr)
			{
				return;
			}

			if (!personal_vehicle)
			{
				if (restore_vehicle_data_when_leaving_it(vehicle))
				{
					return;
				}
			}

			save_original_veh_data(vehicle);

			vehicle->m_deform_god &= ~(deform_god_bit);

			vehicle->m_damage_bits = static_cast<int>(eEntityProofs::GOD);
		}

		CVehicle* get_personal_vehicle()
		{
			Vehicle personal_vehicle = mobile::mechanic::get_personal_vehicle();
			if (ENTITY::DOES_ENTITY_EXIST(personal_vehicle))
			{
				return reinterpret_cast<CVehicle*>(g_pointers->m_gta.m_handle_to_ptr(personal_vehicle));
			}

			return nullptr;
		}

		virtual void on_tick() override
		{
			if (g_local_player)
			{
				const auto personal_vehicle = get_personal_vehicle();
				apply_godmode_to_vehicle(personal_vehicle, true);
				apply_godmode_to_vehicle(g_local_player->m_vehicle, personal_vehicle == g_local_player->m_vehicle);
			}
		}

		virtual void on_disable() override
		{
			if (g_local_player)
			{
				if (g_local_player->m_vehicle)
					restore_original_vehicle_data(g_local_player->m_vehicle);

				const auto personal_vehicle = get_personal_vehicle();
				if (personal_vehicle)
				{
					restore_original_vehicle_data(personal_vehicle);
				}
			}
		}
	};

	vehicle_godmode
	    g_vehicle_godmode("vehgodmode", "God Mode", "Prevents your vehicle from taking any form of damage", g_vehicle.god_mode);
}