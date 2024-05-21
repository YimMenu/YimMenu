#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"
#include "services/script_patcher/script_patcher_service.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"

namespace big
{
	class block_ceo_creation : looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			g_script_patcher_service->update();
		}

		virtual void on_tick() override
		{
			if (*g_pointers->m_gta.m_is_session_started && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_J) == 0)
			{
				for (int i = 0; i < 10; i++)
				{
					*scr_globals::gsbd_fm_events.at(11).at(132).at(i, 1).as<Player*>() = self::id;
				}
			}
		}

		virtual void on_disable() override
		{
			g_script_patcher_service->update();
		}
	};

	block_ceo_creation g_block_ceo_creation("blockceos", "BLOCK_CEO_CREATION", "BLOCK_CEO_CREATION_DESC", g.session.block_ceo_creation);
}
