#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "pointers.hpp"

namespace
{
	inline bool is_key_pressed(uint16_t key)
	{
		if (GetForegroundWindow() == big::g_pointers->m_hwnd)
		{
			if (GetAsyncKeyState(key) & 0x8000)
			{
				return true;
			}
		}
		return false;
	}
}

namespace big
{
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

	class turn_signals : looped_command
	{
		using looped_command::looped_command;

		key_state right_signal_key{'L'};
		key_state left_signal_key{'J'};
		key_state hazzards_key{'K'};
		std::optional<std::chrono::system_clock::time_point> queued_left_turn_signal;
		std::optional<std::chrono::system_clock::time_point> queued_right_turn_signal;
		bool hazzards = false;
		bool left;
		bool right;

		void update_key_state(key_state& key_last_tick)
		{
			if (is_key_pressed(key_last_tick.v_key))
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

				default:
					VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::veh, signal_state::left, off);
					VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::veh, signal_state::right, off);
				}
			}
		}

		virtual void on_enable() override
		{
			g_notification_service.push("TURN_SIGNALS"_T.data(), "BACKEND_LOOPED_VEHICLE_TURN_SIGNALS_HELP"_T.data());
		}

		virtual void on_tick() override
		{
			update_key_states();


			if (left_signal_key.state == key_state::just_pressed && !left || g.vehicle.auto_turn_signals && PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY)
			    || queued_left_turn_signal.has_value() && queued_left_turn_signal.value() - std::chrono::system_clock::now() > 1500ms)
			{
				set_turn_signals(signal_state::left, true);
				queued_left_turn_signal = std::nullopt;
				left = true;
			}

			else if (left_signal_key.state == key_state::just_pressed && left || !g.vehicle.turn_signals)
			{
				set_turn_signals(signal_state::left, false);
				left = false;
			}

			if (right_signal_key.state == key_state::just_pressed && !right || g.vehicle.auto_turn_signals && PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY)
			    || queued_right_turn_signal.has_value() && queued_right_turn_signal.value() - std::chrono::system_clock::now() > 1500ms)
			{
				set_turn_signals(signal_state::right, true);
				queued_right_turn_signal = std::nullopt;
				right = true;
			}

			else if (right_signal_key.state == key_state::just_pressed && right || !g.vehicle.turn_signals)
			{
				set_turn_signals(signal_state::right, false);
				right = false;
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

			if (!queued_left_turn_signal.has_value() && !queued_right_turn_signal.has_value())
			{
				if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY))
				{
					queued_left_turn_signal = std::chrono::system_clock::now();
				}

				if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY))
				{
					queued_right_turn_signal = std::chrono::system_clock::now();
				}
			}
		}

		virtual void on_disable() override
		{
			if (self::veh)
			{
				VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::veh, 0, 0);
				VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::veh, 1, 0);
			}
		}
	};

	turn_signals g_turn_signals("turnsignals", "TURN_SIGNALS", "TURN_SIGNALS_DESC", g.vehicle.turn_signals);
}
