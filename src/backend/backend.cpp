#include "backend.hpp"

#include "looped/looped.hpp"
#include "looped_command.hpp"
#include "script.hpp"
#include "script_patches.hpp"
#include "services/context_menu/context_menu_service.hpp"
#include "thread_pool.hpp"

namespace big
{
	void backend::loop()
	{
		for (auto& command : g_looped_commands)
			command->refresh();

		register_script_patches();

		while (g_running)
		{
			looped::system_self_globals();
			looped::system_update_pointers();
			looped::system_desync_kick_protection();
			looped::system_spoofing();
			looped::system_mission_creator();

			for (auto command : g_looped_commands)
				if (command->is_enabled())
					command->on_tick();

			script::get_current()->yield();
		}
	}

	void backend::self_loop()
	{
		LOG(INFO) << "Starting script: Self";

		while (g_running)
		{
			looped::self_police();
			looped::self_hud();
			looped::self_dance_mode();

			script::get_current()->yield();
		}
	}

	void backend::weapons_loop()
	{
		LOG(INFO) << "Starting script: Weapons";

		while (g_running)
		{
			looped::weapons_ammo_special_type();
			looped::weapons_cage_gun();
			looped::weapons_delete_gun();
			looped::weapons_gravity_gun();
			looped::weapons_increased_damage();
			looped::weapons_repair_gun();
			looped::weapons_steal_vehicle_gun();
			looped::weapons_vehicle_gun();
			looped::weapons_c4_limit();

			script::get_current()->yield();
		}
	}

	void backend::vehicles_loop()
	{
		LOG(INFO) << "Starting script: Vehicles";

		while (g_running)
		{
			looped::vehicle_auto_drive();
			looped::vehicle_boost_behavior();
			looped::vehicle_god_mode();
			looped::vehicle_speedo_meter();
			looped::derail_train();
			looped::drive_train();

			script::get_current()->yield();
		}
	}

	void backend::turnsignal_loop()
	{
		LOG(INFO) << "Starting script: turnsignal";

		while (g_running)
		{
			looped::vehicle_turn_signals();

			script::get_current()->yield();
		}
	}

	void backend::misc_loop()
	{
		LOG(INFO) << "Starting script: Miscellaneous";

		while (g_running)
		{
			looped::hud_transition_state();
			looped::session_local_time();
			looped::session_pop_multiplier_areas();
			looped::session_force_thunder();
			looped::session_randomize_ceo_colors();
			looped::session_auto_kick_host();
			looped::session_block_jobs();

			script::get_current()->yield();
		}
	}

	void backend::remote_loop()
	{
		LOG(INFO) << "Starting script: Remote";

		while (g_running)
		{
			looped::player_good_options();
			looped::player_toxic_options();
			looped::player_spectate();
			looped::player_remote_control_vehicle();

			script::get_current()->yield();
		}
	}

	void backend::lscustoms_loop()
	{
		LOG(INFO) << "Starting script: Ls customs";

		while (g_running)
		{
			looped::vehicle_ls_customs();

			script::get_current()->yield();
		}
	}

	void backend::rainbowpaint_loop()
	{
		LOG(INFO) << "Starting script: Rainbow paint";

		while (g_running)
		{
			looped::vehicle_rainbow_paint();

			script::get_current()->yield();
		}
	}

	void backend::vehiclefly_loop()
	{
		LOG(INFO) << "Starting script: Vehicle fly";

		while (g_running)
		{
			looped::vehicle_fly();

			script::get_current()->yield();
		}
	}

	void backend::disable_control_action_loop()
	{
		LOG(INFO) << "Starting script: Disable Control Action";

		while (g_running)
		{
			looped::custom_gun_disable_control_action();
			context_menu_service::disable_control_action_loop();

			script::get_current()->yield();
		}
	}

	void backend::world_loop()
	{
		LOG(INFO) << "Starting script: World";

		while (g_running)
		{
			looped::world_spawn_ped();
			script::get_current()->yield();
		}
	}
}
