#include "backend/player_command.hpp"
#include "pointers.hpp"

namespace big
{
	class send_to_apartment : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			const size_t arg_count = 10;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::Teleport,
			    self::id,
			    1 << player->id(),
				(int64_t) player->id(),
			    (int64_t)(int)-1,
			    1,
			    (int64_t)_args.get<int64_t>(0),
			    1,
			    1,
			    1};

			g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id(), (int)eRemoteEvent::Teleport);
		}
	};

	send_to_apartment g_send_to_apartment("apartmenttp", "TP_TO_APARTMENT", "TP_TO_APARTMENT_DESC", 1);
}