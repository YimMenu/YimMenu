#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_global.hpp"

namespace big
{
	class bounty_player : player_command
	{
		using player_command::player_command;

		virtual std::optional<std::vector<std::uint64_t>> parse_args_p(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
		{
			uint64_t bounty = std::atoi(args[0].c_str());

			if (bounty < 0 || bounty > 10000)
			{
				ctx->report_error(std::format("Bounty {} is invalid, The range is 1-10000", bounty));
				return std::nullopt;
			}

			return std::vector<std::uint64_t>{ bounty };
		}

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{	
			const size_t arg_count = 22;

			int64_t arguments[arg_count] =
			{
				(int64_t)eRemoteEvent::Bounty,
				self::id,
				player->id(),
				1,
				static_cast<int64_t>(_args[0]), // cast to int instead?
				0,
				1,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				*script_global(1923597).at(9).as<int64_t*>(),
				*script_global(1923597).at(10).as<int64_t*>()
			};

			g_pointers->m_trigger_script_event(1, arguments, arg_count, 1 << player->id());
		}
	};

	bounty_player g_bounty_player("bounty", "Set bounty on the player", "Up to $10,000", 1, false);
}
