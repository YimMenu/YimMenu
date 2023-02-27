#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/scripts.hpp"

namespace big
{
	class turn_into_beast : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			auto id = player->id();

			if (!NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(id, "am_hunt_the_beast", -1))
			{
				if (!NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(id, "am_launcher", -1))
				{
					g_notification_service->push_error("Turn to Beast", "Cannot start the Hunt the Beast event, player not a participant of am_launcher");
					return;
				}

				g_notification_service->push("Turn to Beast", "Starting Hunt The Beast event. Please wait...");

				scripts::start_launcher_script(47);

				for (int i = 0; !NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(id, "am_hunt_the_beast", -1); i++)
				{
					if (i >= 1000)
					{
						g_notification_service->push_error("Turn to Beast", "Failed to start the Hunt The Beast event");
						return;
					}

					script::get_current()->yield(1ms);
				}
			}

			if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(id))
				return;

			if (!scripts::force_host(RAGE_JOAAT("am_hunt_the_beast")))
			{
				g_notification_service->push_error("Turn to Beast", "Failed to take control of am_hunt_the_beast");
				return;
			}

			auto thread        = gta_util::find_script_thread(RAGE_JOAAT("am_hunt_the_beast"));
			auto stack         = thread->m_stack;
			auto net_component = thread->m_net_component;
			auto idx           = scr_locals::am_hunt_the_beast::broadcast_idx;

			if (!stack || !net_component || !player->is_valid())
				return;

			*script_local(stack, idx).as<int*>()       = 1;
			*script_local(stack, idx).at(1).as<int*>() = 2;// stage
			*script_local(stack, idx).at(1).at(6).as<int*>() = net_component->get_participant_index(player->get_net_game_player());// beast participant idx
			*script_local(stack, idx).at(1).at(7).as<Player*>()     = id;     // beast player idx
			*script_local(stack, idx).at(1).at(2).as<int*>()        = INT_MAX;// stopwatch time
			*script_local(stack, idx).at(1).at(2).at(1).as<bool*>() = true;   // stopwatch initialized
			*script_local(stack, idx).at(1).at(4).at(1).as<bool*>() = false;  // destroy old stage 1 stopwatch
			*script_local(stack, idx).at(1).at(9).as<int*>()        = 2;      // some distance check
			*script_local(stack, idx).at(83).as<int*>()             = 0;      // transformed bitset
		}
	};

	class turn_into_beast_all : command
	{
		using command::command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			scripts::start_launcher_script(47);

			for (int i = 0; !scripts::is_running(RAGE_JOAAT("am_launcher")); i++)
			{
				if (i >= 7000)
				{
					g_notification_service->push_error("Turn to Beast", "Failed to start the Hunt The Beast event");
					return;
				}

				script::get_current()->yield(1ms);
			}

			script::get_current()->yield(500ms);

			if (!scripts::force_host(RAGE_JOAAT("am_hunt_the_beast")))
			{
				g_notification_service->push_error("Turn to Beast", "Failed to take control of am_hunt_the_beast");
				return;
			}

			script::get_current()->yield(3s);

			auto thread = gta_util::find_script_thread(RAGE_JOAAT("am_hunt_the_beast"));

			if (!thread)
				return;

			auto stack         = thread->m_stack;
			auto net_component = thread->m_net_component;
			auto idx           = scr_locals::am_hunt_the_beast::broadcast_idx;

			if (!stack || !net_component)
				return;

			thread->m_net_component->block_host_migration(true);
			thread->m_context.m_state = rage::eThreadState::unk_3;
			g.m_hunt_the_beast_thread = thread;

			for (int i = 0; i < 15; i++)
			{
				*script_local(stack, idx).as<int*>()                    = 1;
				*script_local(stack, idx).at(1).as<int*>()              = 2;        // stage
				*script_local(stack, idx).at(1).at(6).as<int*>()        = __rdtsc();// participant idx
				*script_local(stack, idx).at(1).at(7).as<Player*>()     = __rdtsc();// beast player idx
				*script_local(stack, idx).at(1).at(2).as<int*>()        = INT_MAX;  // stopwatch time
				*script_local(stack, idx).at(1).at(2).at(1).as<bool*>() = true;     // stopwatch initialized
				*script_local(stack, idx).at(1).at(4).at(1).as<bool*>() = false;    // destroy old stage 1 stopwatch
				*script_local(stack, idx).at(1).at(9).as<int*>()        = 2;        // some distance check
				*script_local(stack, idx).at(83).as<int*>()             = 0;        // transformed bitset
				script::get_current()->yield(350ms);
			}

			// unfortunately we must also turn ourselves into the beast to prevent the script from exiting due to a "missing player"

			*script_local(stack, idx).at(1).at(6).as<int*>() = net_component->m_local_participant_index;// participant idx
			*script_local(stack, idx).at(1).at(7).as<Player*>() = self::id;// beast player idx
			*script_local(stack, idx).at(1).at(2).as<int*>()    = INT_MAX; // stopwatch time
			*script_local(stack, idx).at(83).as<int*>()         = 0;       // transformed bitset

			thread->m_context.m_state = rage::eThreadState::running;
		}
	};

	turn_into_beast g_turn_into_beast("beast", "Turn Into Beast", "Turns the player into the beast", 0, false);
	turn_into_beast_all g_turn_into_beast_all("beastall", "Turn Everyone Into Beast", "Turns everyone into the beast, including you", 0);
}