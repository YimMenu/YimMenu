#include "send_to_warehouse.hpp"

#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	std::optional<std::vector<std::uint64_t>> send_to_warehouse::parse_args_p(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
	{
		return std::vector<std::uint64_t>{(uint64_t)std::atoi(args[0].c_str())};
	}

	CommandAccessLevel send_to_warehouse::get_access_level()
	{
		return CommandAccessLevel::AGGRESSIVE;
	}

	void send_to_warehouse::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		const size_t arg_count = 6;
		int64_t args[arg_count] = {(int64_t)eRemoteEvent::TeleportToWarehouse, self::id, (int64_t)player->id(), 1, (int64_t)_args[0]};

		g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id());
	}
}
