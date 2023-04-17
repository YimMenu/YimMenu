#include "backend/looped/looped.hpp"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/is_key_pressed.hpp"
#include "windows.h"

struct key_state
{
	key_state(int v_key) :
	    v_key(v_key)
	{
	}

	enum
	{
		up,
		down,
		just_pressed,
		just_released,
	};

	uint8_t state = up;
	int v_key;
};

inline key_state right_signal_key{'L'};
inline key_state left_signal_key{'J'};
inline key_state hazzards_key{'K'};

void update_key_state(key_state& key_last_tick)
{
	if (big::is_key_pressed(key_last_tick.v_key))
	{
		switch (key_last_tick.state)
		{
		case key_state::up: key_last_tick.state = key_state::just_pressed; break;

		case key_state::just_pressed: key_last_tick.state = key_state::down; break;
		}
	}
	else
	{
		switch (key_last_tick.state)
		{
		case key_state::down: key_last_tick.state = key_state::just_released; break;

		case key_state::just_released: key_last_tick.state = key_state::up; break;
		}
	}
}


void update_key_states()
{
	update_key_state(left_signal_key);
	update_key_state(hazzards_key);
	update_key_state(right_signal_key);
}

struct signal_state
{
	enum
	{
		right,
		left,
		hazzards
	};
};

inline void set_turn_signals(int signal_state, bool on)
{
	static constexpr int off = 0;

	if (self::veh && big::g.vehicle.turn_signals)
	{
		switch (signal_state)
		{
		case signal_state::hazzards:
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::veh, signal_state::left, on);
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::veh, signal_state::right, on);
			break;

		case signal_state::right:
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::veh, signal_state::left, off);
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::veh, signal_state::right, on);
			break;

		case signal_state::left:
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::veh, signal_state::left, on);
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::veh, signal_state::right, off);
			break;
		}
	}
}

namespace big
{
	static bool b_last_turn_signals = false;

	void looped::vehicle_turn_signals()
	{
		static bool hazzards = false;
		bool b_turn_signals  = g.vehicle.turn_signals;

		if (!b_turn_signals && b_turn_signals != b_last_turn_signals)
		{
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0, 0);
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, 0);
		}

		if (g.vehicle.turn_signals)
		{
			static bool ran_once = [] {
				g_notification_service->push("Instructions", "Manual: J = Left, L = Right, K = Toggle Hazzards");
				return true;
			}();
		}


		update_key_states();

		if (left_signal_key.state == key_state::just_pressed || g.vehicle.auto_turn_signals && PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY))
		{
			set_turn_signals(signal_state::left, true);
		}

		if (right_signal_key.state == key_state::just_pressed || g.vehicle.auto_turn_signals && PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY))
		{
			set_turn_signals(signal_state::right, true);
		}

		if (hazzards_key.state == key_state::just_pressed && !hazzards)
		{
			set_turn_signals(signal_state::hazzards, true);
			hazzards = true;
		}
		else if (hazzards_key.state == key_state::just_pressed && hazzards || !g.vehicle.turn_signals)
		{
			set_turn_signals(signal_state::hazzards, false);
			hazzards = false;
		}


		if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY))
		{
			if (g.vehicle.turn_signals)
			{
				script::get_current()->yield(1500ms);
			}
			set_turn_signals(signal_state::left, false);
		}

		if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY))
		{
			if (g.vehicle.turn_signals)
			{
				script::get_current()->yield(1500ms);
			}
			set_turn_signals(signal_state::right, false);
		}

		b_last_turn_signals = g.vehicle.turn_signals;
	}
}