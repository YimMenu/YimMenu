#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class vehicle_godmode_internal : looped_command
	{
		using looped_command::looped_command;

		uint32_t last_bits                   = 0;
		float last_water_collistion_strength = 0;
		bool last_driving                    = false;

		virtual void on_tick() override
		{
			if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr)
			{
				return;
			}

			if (!PED::GET_PED_CONFIG_FLAG(self::ped, 62, false))
			{
				if (last_driving)
				{
					g_local_player->m_vehicle->m_deform_god  = 0x9C;
					g_local_player->m_vehicle->m_damage_bits = 0;
				}

				last_driving = false;
				return;
			}

			last_driving = true;

			if (g.vehicle.god_mode || g.vehicle.proof_collision)
			{
				g_local_player->m_vehicle->m_deform_god = 0x8C;
			}
			else
			{
				g_local_player->m_vehicle->m_deform_god = 0x9C;
			}

			uint32_t bits                    = g.vehicle.proof_mask;
			uint32_t changed_bits            = bits ^ last_bits;
			uint32_t changed_or_enabled_bits = bits | changed_bits;

			if (changed_or_enabled_bits)
			{
				uint32_t unchanged_bits = g_local_player->m_vehicle->m_damage_bits & ~changed_or_enabled_bits;
				g_local_player->m_vehicle->m_damage_bits = unchanged_bits | bits;
				last_bits                                = bits;
			}
		}

		virtual void on_disable() override
		{
			if (g_local_player && g_local_player->m_vehicle)
			{
				g_local_player->m_vehicle->m_deform_god  = 0x9C;
				g_local_player->m_vehicle->m_damage_bits = 0;
			}
		}
	};

	static bool true_ref = true;
	vehicle_godmode_internal g_vehicle_godmode_internal("$$vehgodmode", "", "", true_ref);
	bool_command g_vehicle_godmode("vehgodmode", "Vehicle God Mode", "Prevents your vehicle from taking any form of damage",
	    g.vehicle.god_mode);
}