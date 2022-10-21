#pragma 
#include "chat_service.hpp"
#include "network/CNetGamePlayer.hpp"
#include "gta/enums.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	chat_service::chat_service()
	{
		g_chat_service = this;
	}

	chat_service::~chat_service()
	{
		g_chat_service = nullptr;
	}

	bool chat_service::did_player_use_chat(Player player_id)
	{
		for (const auto& [player, msg, is_team] : m_msgs)
		{
			if (player->m_player_id == player_id)
			{
				return true;
			}
		}
		return false;
	}

	void chat_service::add_msg(CNetGamePlayer* player, std::string msg, bool is_team)
	{
		m_msgs.push_back({ player, is_team, msg });
	}

	void chat_service::chat_menu()
	{
		while (g_running)
		{
			if (*g_pointers->m_is_session_started)
			{
				if (!g->window.chat && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_MP_TEXT_CHAT_ALL))
				{
					HUD::MP_TEXT_CHAT_DISABLE(true);
					g->window.chat = true;
				}

				if (g->window.chat)
				{
					PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
					if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_FRONTEND_PAUSE_ALTERNATE))
					{
						script::get_current()->yield(150ms); // Stop pause menu // Steel opens
						LOG(G3LOG_DEBUG) << "Pause menu closed";
						g->window.chat = false;
						continue;
					}
				}
			}

			script::get_current()->yield();
		}
	}
}