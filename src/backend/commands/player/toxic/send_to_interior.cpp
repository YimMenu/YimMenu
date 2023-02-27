#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class send_to_interior : player_command
	{
		using player_command::player_command;

		virtual std::optional<std::vector<std::uint64_t>> parse_args_p(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
		{
			return std::vector<std::uint64_t>{(uint64_t)std::atoi(args[0].c_str())};
		}

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			float max   = 1e+38f;
			auto coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), FALSE);
			const size_t arg_count  = 15;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::InteriorControl,
			    (int64_t)self::id,
			    (int64_t)(int)_args[0],
			    (int64_t)self::id,
			    (int64_t) false,
			    (int64_t) true,// true means enter sender interior
			    (int64_t) * (uint32_t*)&coords.x,
			    (int64_t) * (uint32_t*)&coords.y,
			    (int64_t) * (uint32_t*)&coords.z,
			    0,
			    0,
			    1,
			    (int64_t) * (uint32_t*)&max,
			    (int64_t) true,
			    -1};

			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
		}
	};

	send_to_interior g_send_to_interior("interiortp", "TP To Interior", "Teleports the player to the specified interior index", 1);
}