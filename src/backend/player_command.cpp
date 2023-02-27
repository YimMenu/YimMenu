#include "player_command.hpp"

#include "fiber_pool.hpp"

namespace big
{
	player_all_component::player_all_component(player_command* parent, const std::string& name, const std::string& label, const std::string& description, std::optional<std::uint8_t> num_args) :
	    command(name + "all", label, description, num_args),
	    m_parent(parent)
	{
	}

	void player_all_component::execute(const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx)
	{
		g_fiber_pool->queue_job([this, args, &ctx] {
			g_player_service->iterate([this, args, &ctx](const player_entry& player) {
				m_parent->execute(player.second, args, ctx);
			});
		});
	}

	std::optional<std::vector<std::uint64_t>> player_all_component::parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
	{
		return m_parent->parse_args_p(args, ctx);
	}

	player_command::player_command(const std::string& name, const std::string& label, const std::string& description, std::optional<std::uint8_t> num_args, bool make_all_version) :
	    command(name, label, description, num_args.has_value() ? std::optional{num_args.value() + 1} : std::nullopt)
	{
		if (make_all_version)
			m_all_component = std::make_unique<player_all_component>(this, name, label, description, num_args);
	}

	void player_command::execute(const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx)
	{
		g_fiber_pool->queue_job([this, args, ctx] {
			std::vector<std::uint64_t> new_args;

			// TODO: This looks ugly and inefficient
			for (int i = 1; i < m_num_args; i++)
				new_args.push_back(args[i]);

			if (g_player_service->get_self()->id() == args[0])
			{
				execute(g_player_service->get_self(), new_args, ctx);
				return;
			}

			for (auto& plyr : g_player_service->players())
			{
				if (plyr.second->id() == args[0])
				{
					execute(plyr.second, new_args, ctx);
					return;
				}
			}

			ctx->report_error(std::format("Tried to execute command {}, but a player with index {} was not found", m_name, args[0]));
		});
	}

	std::optional<std::vector<std::uint64_t>> player_command::parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
	{
		std::vector<std::string> new_args;
		std::vector<std::uint64_t> result;

		if (args[0] == "me" || args[0] == "self")
		{
			result.push_back(ctx->get_sender()->id());
		}
		else
		{
			int plyr_id = -1;

			for (auto& plyr : g_player_service->players())
			{
				if (stricmp(plyr.second->get_name(), args[0].c_str()) == 0)
				{
					plyr_id = plyr.second->id();
					break;
				}
			}

			if (ctx->get_access_level() != CommandAccessLevel::ADMIN && (get_access_level() == CommandAccessLevel::TOXIC || get_access_level() == CommandAccessLevel::AGGRESSIVE) && plyr_id == self::id)
			{
				ctx->report_error("Permission denied, cannot call toxic commands on me");
				return std::nullopt;
			}

			if (plyr_id == -1)
			{
				ctx->report_error(std::format("Cannot find player with name {} in command {}", args[0], m_name));
				return std::nullopt;
			}

			result.push_back(plyr_id);
		}

		for (int i = 1; i < args.size(); i++)
			new_args.push_back(args[i]);

		auto res = parse_args_p(new_args, ctx);
		if (!res.has_value())
			return std::nullopt;

		for (auto& p : res.value())
			result.push_back(p);

		return result;
	}

	void player_command::call(player_ptr player, const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx)
	{
		// TODO: Code duplication
		if (m_num_args.has_value() && args.size() != (m_num_args.value() - 1))
		{
			ctx->report_error(std::format("Command {} called with the wrong number of arguments. Expected {}, got {}",
			    m_name,
			    m_num_args.value(),
			    args.size()));
			return;
		}

		g_fiber_pool->queue_job([this, player, args, ctx] {
			if (player->is_valid())
				execute(player, args, ctx);
		});
	}
}