#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class godmode_internal : looped_command
	{
		using looped_command::looped_command;

		uint32_t last_bits = 0;

		virtual void on_tick() override
		{
			if (g_local_player == nullptr)
			{
				return;
			}

			uint32_t bits                    = g.self.proof_mask;
			uint32_t changed_bits            = bits ^ last_bits;
			uint32_t changed_or_enabled_bits = bits | changed_bits;

			if (changed_or_enabled_bits)
			{
				uint32_t unchanged_bits       = g_local_player->m_damage_bits & ~changed_or_enabled_bits;
				g_local_player->m_damage_bits = unchanged_bits | bits;
				last_bits                     = bits;
			}
		}

		virtual void on_disable() override
		{
			g_local_player->m_damage_bits = 0;
		}
	};

	static bool true_ref = true;
	godmode_internal g_godmode_internal("$$godmode", "", "", true_ref);
	bool_command g_godmode("godmode", "God Mode", "Prevents you from taking any form of damage", g.self.god_mode);
}