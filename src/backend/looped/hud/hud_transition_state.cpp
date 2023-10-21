#include "backend/looped/looped.hpp"
#include "core/scr_globals.hpp"
#include "gta/joaat.hpp"
#include "gta/net_array.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "services/players/player_service.hpp"

// Credits: QuickNET
namespace big
{
	static float old_percent = NAN;
	constexpr char transition_states[][48] = {"TRANSITION_STATE_EMPTY", "Singleplayer Swoop Up", "Multiplayer Swoop Up", "Creator Swoop Up", "Pre-HUD Checks", "Wait HUD Exit", "Wait For Summon", "Singleplayer Swoop Down", "Multiplayer Swoop Down", "Cancel Joining", "Retry Loading", "Retry Loading Slot 1", "Retry Loading Slot 2", "Retry Loading Slot 3", "Retry Loading Slot 4", "Wait On Invite", "Prejoining Freemode Session Checks", "Look For Fresh Join Freemode", "Look To Join Another Session Freemode", "Confirm Freemode Session Joining", "Wait Join Freemode Session", "Creation Enter Session", "Pre-Freemode Launch Script", "Freemode Teamfull Check", "Start Freemode Launch Script", "Freemode Transition Create Player", "Is Freemode And Transition Ready", "Freemode Swoop Down", "Post Bink Video Warp", "Freemode Final Setup Player", "Move Freemode To Running State", "Freemode How To Terminate", "Start Creator Pre-Launch Script Check", "Start Creator Launch Script", "Creator Transition Create Player", "Is Creator And Transition Ready", "Creator Swoop Down", "Creator Final Setup Player", "Move Creator To Running State", "Prejoining Testbed Session Checks", "Look For Fresh Join Testbed", "Look For Fresh Host Testbed", "Look To Join Another Session Testbed", "Look To Host Session Testbed", "Confirm Testbed Session Joining", "Wait Join Testbed Session", "Start Testbed Launch Script", "Testbed Transition Create Player", "Is Testbed And Transition Ready", "Testbed Swoop Down", "Testbed Final Setup Player", "Move Testbed To Running State", "Testbed How To Terminate", "Quit Current Session Prompt", "Wait For Transition Session To Setup", "Terminate Singleplayer", "Wait Terminate Singleplayer", "Kick Terminate Session", "Terminate Session", "Wait Terminate Session", "Terminate Session And Hold", "Terminate Session And Move Into Holding State", "Team Swapping Checks", "Return To Singleplayer", "Wait For Singleplayer To Start", "Waiting For External Termination Call", "Terminate Maintransition", "Wait For Dirty Load Confirm", "DLC Intro Bink", "Spawn Into Personal Vehicle"};

	eTransitionState last_state = eTransitionState::TRANSITION_STATE_EMPTY;
	void looped::hud_transition_state()
	{
		const auto state = *scr_globals::transition_state.as<eTransitionState*>();

		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) == 0)
			return;

		// When freemode script loaded remove loading screen.
		if (state == eTransitionState::TRANSITION_STATE_WAIT_JOIN_FM_SESSION && DLC::GET_IS_LOADING_SCREEN_ACTIVE())
		{
			SCRIPT::SHUTDOWN_LOADING_SCREEN();
		}

		if ((last_state == state && state != eTransitionState::TRANSITION_STATE_FM_TRANSITION_CREATE_PLAYER) || state == eTransitionState::TRANSITION_STATE_EMPTY || state > eTransitionState::TRANSITION_STATE_SPAWN_INTO_PERSONAL_VEHICLE)
		{
			return;
		}

		if (state != eTransitionState::TRANSITION_STATE_FM_TRANSITION_CREATE_PLAYER && HUD::BUSYSPINNER_IS_ON())
		{
			HUD::BUSYSPINNER_OFF();
		}

		if ((int)state > 0 && (int)state < std::size(transition_states))
		{
			rage::scrThread* freemode{};
			if (state == eTransitionState::TRANSITION_STATE_FM_TRANSITION_CREATE_PLAYER
			    && (freemode = gta_util::find_script_thread(RAGE_JOAAT("freemode")), freemode && freemode->m_net_component))
			{
				int num_array_handlers{};
				int received_array_handlers{};

				while (
				    auto handler = g_pointers->m_gta.m_get_host_array_handler_by_index((CGameScriptHandlerNetComponent*)freemode->m_net_component, num_array_handlers++))
					if (handler->m_flags & 1)
						received_array_handlers++;

				if (num_array_handlers == 0)
					num_array_handlers = 1;

				float percent = round((static_cast<float>(received_array_handlers) / num_array_handlers) * 100);

				if (percent != old_percent)
				{
					HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
					HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(
					    std::format("Wait For Host Broadcast Data: {}%", (percent)).c_str());
					HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(5);
				}

				old_percent = percent;
			}
			else
			{
				old_percent = NAN;
				HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(transition_states[(int)state]);
				HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(5);
			}
		}

		last_state = state;
	}
}
