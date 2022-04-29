#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "script_global.hpp"

// Credits: QuickNET
namespace big
{
	constexpr char transition_states[][48] = {
		"TRANSITION_STATE_EMPTY",
		"Singleplayer Swoop Up",
		"Multiplayer Swoop Up",
		"Creator Swoop Up",
		"Pre-HUD Checks",
		"Wait HUD Exit",
		"Wait For Summon",
		"Singleplayer Swoop Down",
		"Multiplayer Swoop Down",
		"Cancel Joining",
		"Retry Loading",
		"Retry Loading Slot 1",
		"Retry Loading Slot 2",
		"Retry Loading Slot 3",
		"Retry Loading Slot 4",
		"Wait On Invite",
		"Prejoining Freemode Session Checks",
		"Look For Fresh Join Freemode",
		"Look To Join Another Session Freemode",
		"Confirm Freemode Session Joining",
		"Wait Join Freemode Session",
		"Creation Enter Session",
		"Pre-Freemode Launch Script",
		"Freemode Teamfull Check",
		"Start Freemode Launch Script",
		"Freemode Transition Create Player",
		"Is Freemode And Transition Ready",
		"Freemode Swoop Down",
		"Post Bink Video Warp",
		"Freemode Final Setup Player",
		"Move Freemode To Running State",
		"Freemode How To Terminate",
		"Start Creator Pre-Launch Script Check",
		"Start Creator Launch Script",
		"Creator Transition Create Player",
		"Is Creator And Transition Ready",
		"Creator Swoop Down",
		"Creator Final Setup Player",
		"Move Creator To Running State",
		"Prejoining Testbed Session Checks",
		"Look For Fresh Join Testbed",
		"Look For Fresh Host Testbed",
		"Look To Join Another Session Testbed",
		"Look To Host Session Testbed",
		"Confirm Testbed Session Joining",
		"Wait Join Testbed Session",
		"Start Testbed Launch Script",
		"Testbed Transition Create Player",
		"Is Testbed And Transition Ready",
		"Testbed Swoop Down",
		"Testbed Final Setup Player",
		"Move Testbed To Running State",
		"Testbed How To Terminate",
		"Quit Current Session Prompt",
		"Wait For Transition Session To Setup",
		"Terminate Singleplayer",
		"Wait Terminate Singleplayer",
		"Kick Terminate Session",
		"Terminate Session",
		"Wait Terminate Session",
		"Terminate Session And Hold",
		"Terminate Session And Move Into Holding State",
		"Team Swapping Checks",
		"Return To Singleplayer",
		"Wait For Singleplayer To Start",
		"Waiting For External Termination Call",
		"Terminate Maintransition",
		"Wait For Dirty Load Confirm",
		"DLC Intro Bink",
	};

	auto transition_state = script_global(1574988);
	eTransitionState last_state = eTransitionState::TRANSITION_STATE_MAX;
	void looped::hud_transition_state()
	{
		const auto state = *transition_state.as<eTransitionState*>();
		if (last_state == eTransitionState::TRANSITION_STATE_MAX)
			last_state = state;

		// When freemode script loaded remove loading screen.
		if (state == eTransitionState::TRANSITION_STATE_WAIT_JOIN_FM_SESSION && DLC::GET_IS_LOADING_SCREEN_ACTIVE())
			SCRIPT::SHUTDOWN_LOADING_SCREEN();

		if (last_state == state || state == eTransitionState::TRANSITION_STATE_EMPTY || state > eTransitionState::TRANSITION_STATE_DLC_INTRO_BINK)
			return;

		if (HUD::BUSYSPINNER_IS_ON())
			HUD::BUSYSPINNER_OFF();

		// sometimes when going into a single player mission or transition this one remains on screen permanently
		if (state == eTransitionState::TRANSITION_STATE_TERMINATE_MAINTRANSITION)
			return;

		HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(
			fmt::format("{} | {}", transition_states[(int)state], state).c_str()
		);
		HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(5);

		last_state = state;
	}
}