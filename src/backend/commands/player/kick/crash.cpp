#include "backend/bool_command.hpp"
#include "backend/command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "backend/player_command.hpp"
#include "util/vehicle.hpp"
#include <thread>

namespace big
{
	class hak_player : player_command
	{
		using player_command::player_command;
		
		virtual std::optional<std::vector<std::uint64_t>> parse_args(const command_arguments& args, const std::shared_ptr<command_context> ctx)
		{
			auto hash = rage::joaat("HAKUCHOU2");
			return std::vector<std::uint64_t>{hash};
		}
		
		virtual CommandAccessLevel get_access_level() 
		{
			return CommandAccessLevel::FRIENDLY;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			if (!STREAMING::IS_MODEL_IN_CDIMAGE(rage::joaat("HAKUCHOU2")) || !STREAMING::IS_MODEL_A_VEHICLE(rage::joaat("HAKUCHOU2")))
			{
				ctx->report_error("Specified model is invalid");
				return;
			}
			int delayms = 500;
			auto spawn_location = *reinterpret_cast<rage::fvector3*>(g_player_service->get_selected()->get_ped()->get_position());
			spawn_location.z += 50.0f;

			const auto veh = vehicle::spawn(rage::joaat("HAKUCHOU2"), spawn_location, 0);
			if (veh == 0)
			{
				g_notification_service->push_error("Crash", "Can't crash him, unable to spawn vehicle");
				return;
			}

			vehicle::max_vehicle(veh);

			std::thread([this, delayms, &veh]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(delayms));
				if (ENTITY::DOES_ENTITY_EXIST(veh))
					entity::delete_entity(veh);
			}).detach();
			
		}
	};

	hak_player g_hak_player("crash", "Crash Player", "Spawns a bugged Hakuchou Drag, so it crashes him. Doesn't work on popular menus. CRASHES ALL PLAYERS AROUND", 0, false);
}


