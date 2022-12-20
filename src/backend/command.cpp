#include "command.hpp"
#include "fiber_pool.hpp"

namespace big
{
	command::command(const std::string& name, std::uint8_t num_args, bool fiber_pool) :
		m_name(name),
		m_num_args(num_args),
		m_fiber_pool(fiber_pool)
	{
		g_commands[rage::joaat(name)] = this;
	}

	void command::call(const std::vector<std::uint64_t>& args, const command_context& ctx)
	{
		if (args.size() != m_num_args)
		{
			ctx.report_error(std::format("Command {} called with the wrong number of arguments. Expected {}, got {}", m_name, m_num_args, args.size()));
			return;
		}

		if (ctx.get_access_level() < get_access_level())
		{
			ctx.report_error(std::format("You do not have sufficient permissions to call command {}", m_name));
			return;
		}

		if (m_fiber_pool)
			g_fiber_pool->queue_job([this, args, &ctx] { execute(args, ctx); });
		else
			execute(args, ctx);
	}

	void command::call(const std::vector<std::string>& args, const command_context& ctx)
	{
		if (args.size() != m_num_args)
		{
			ctx.report_error(std::format("Command {} called with the wrong number of arguments. Expected {}, got {}", m_name, m_num_args, args.size()));
			return;
		}

		if (ctx.get_access_level() < get_access_level())
		{
			ctx.report_error(std::format("You do not have sufficient permissions to call command {}", m_name));
			return;
		}

		auto parsed = parse_args(args);
		if (parsed.has_value())
			call(parsed.value(), ctx);
	}

	command* command::get(rage::joaat_t command)
	{
		return g_commands[command];
	}

	void command::call(rage::joaat_t command, const std::vector<std::uint64_t>& args, const command_context& ctx)
	{
		g_commands[command]->call(args, ctx);
	}

	void command::call(rage::joaat_t command, const std::vector<std::string>& args, const command_context& ctx)
	{
		g_commands[command]->call(args, ctx);
	}
}