#include "backend/looped_command.hpp"
#include "pointers.hpp"
#include "natives.hpp"

namespace big
{
	class increase_player_limit : looped_command
	{
		using looped_command::looped_command;
		memory::byte_patch* m_join_request_patch;

		virtual void on_enable() override
		{
			if (!m_join_request_patch)
				m_join_request_patch = memory::byte_patch::make(g_pointers->m_gta.m_session_request_patch, std::to_array({0x90, 0x90, 0x90, 0x90, 0x90, 0x90})).get();
			m_join_request_patch->apply();
		}

		virtual void on_tick() override
		{
			if (*g_pointers->m_gta.m_is_session_started && !NETWORK::NETWORK_IS_ACTIVITY_SESSION())
				NETWORK::NETWORK_SESSION_CHANGE_SLOTS(32, 0);
		}

		virtual void on_disable() override
		{
			m_join_request_patch->restore();
		}
	};

	increase_player_limit g_increase_player_limit("32players", "INCREASE_PLAYER_LIMIT", "INCREASE_PLAYER_LIMIT_DESC", g.spoofing.increase_player_limit);
}
