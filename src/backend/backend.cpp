#include "backend.hpp"

#include "looped/looped.hpp"
#include "looped_command.hpp"
#include "script.hpp"
#include "script_patches.hpp"
#include "services/context_menu/context_menu_service.hpp"
#include "services/custom_teleport/custom_teleport_service.hpp"
#include "services/ped_animations/ped_animations_service.hpp"
#include "services/tunables/tunables_service.hpp"
#include "thread_pool.hpp"
#include "services/bad_players/bad_players.hpp"

namespace big
{
	void backend::loop()
	{
		for (auto& command : g_bool_commands)
			command->refresh();

		register_script_patches();

		g_custom_teleport_service.fetch_saved_locations();
		g_ped_animation_service.fetch_saved_animations();
		bad_players_nm::load_blocked_list();

		while (g_running)
		{
			looped::system_self_globals();
			looped::system_update_pointers();
			looped::system_desync_kick_protection();
			looped::system_spoofing();

			for (auto command : g_looped_commands)
				if (command->is_enabled())
					command->on_tick();

			script::get_current()->yield();
		}
	}

	void backend::vehicles_loop()
	{
		LOG(INFO) << "Starting script: Vehicles";

		while (g_running)
		{
			looped::vehicle_auto_drive();

			script::get_current()->yield();
		}
	}

	void backend::misc_loop()
	{
		LOG(INFO) << "Starting script: Miscellaneous";

		while (g_running)
		{
			looped::hud_transition_state();
			looped::hud_disable_input();
			looped::session_force_thunder();

			script::get_current()->yield();
		}
	}

	void backend::remote_loop()
	{
		LOG(INFO) << "Starting script: Remote";

		while (g_running)
		{
			looped::player_spectate();

			script::get_current()->yield();
		}
	}

	void backend::disable_control_action_loop()
	{
		LOG(INFO) << "Starting script: Disable Control Action";

		while (g_running)
		{
			context_menu_service::disable_control_action_loop();

			script::get_current()->yield();
		}
	}

	void backend::world_loop()
	{
		LOG(INFO) << "Starting script: World";

		while (g_running)
		{
			looped::casino();
			script::get_current()->yield();
		}
	}

	void backend::tunables_script()
	{
		g_tunables_service->run_script();
	}
}
