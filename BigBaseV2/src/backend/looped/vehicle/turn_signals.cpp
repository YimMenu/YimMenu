#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "windows.h"

struct key_state
{
	key_state(int v_key) : v_key(v_key) {}

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

bool is_key_pressed(int const v_key)
{
	return GetAsyncKeyState(v_key) & 0x8000;
}

void update_key_state(key_state& key_last_tick)
{
	if (is_key_pressed(key_last_tick.v_key))
	{
		switch (key_last_tick.state)
		{
		case key_state::up:
			key_last_tick.state = key_state::just_pressed;
			break;

		case key_state::just_pressed:
			key_last_tick.state = key_state::down;
			break;
		}
	}
	else
	{
		switch (key_last_tick.state)
		{
		case key_state::down:
			key_last_tick.state = key_state::just_released;
			break;

		case key_state::just_released:
			key_last_tick.state = key_state::up;
			break;
		}
	}
}

void update_key_states()
{
	update_key_state(left_signal_key);
	update_key_state(hazzards_key);
	update_key_state(right_signal_key);
}

struct signal_state {
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

	if (const Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		veh != 0 && big::g->vehicle.turn_signals)
	{
		switch (signal_state)
		{
		case signal_state::hazzards:
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, signal_state::left, on);
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, signal_state::right, on);
			break;

		case signal_state::right:
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, signal_state::left, off);
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, signal_state::right, on);
			break;

		case signal_state::left:
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, signal_state::left, on);
			VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, signal_state::right, off);
			break;
		}
	}
}

namespace big
{
	void looped::vehicle_turn_signal()
	{

		static bool hazzards = false;

		update_key_states();

		if (left_signal_key.state == key_state::just_pressed)
		{
			set_turn_signals(signal_state::left, true);
		}
		
		if (right_signal_key.state == key_state::just_pressed)
		{
			set_turn_signals(signal_state::right, true);
		}

		if (hazzards_key.state == key_state::just_pressed && !hazzards)
		{
			set_turn_signals(signal_state::hazzards, true);
			hazzards = true;
		}
		else if (hazzards_key.state == key_state::just_pressed && hazzards)
		{
			set_turn_signals(signal_state::hazzards, false);
			hazzards = false;
		}

		
		if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY))
		{
			script::get_current()->yield(1500ms);
			set_turn_signals(signal_state::right, false);
		}

		if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY))
		{
			script::get_current()->yield(1500ms);
			set_turn_signals(signal_state::left, false);
		}
	}
}
