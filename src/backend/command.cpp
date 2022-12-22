#include "command.hpp"
#include "fiber_pool.hpp"

namespace
{
	// https://stackoverflow.com/a/7408245
	static std::vector<std::string> split(const std::string& text, char sep)
	{
		std::vector<std::string> tokens;
		std::size_t start = 0, end = 0;
		while ((end = text.find(sep, start)) != std::string::npos)
		{
			if (end != start)
			{
				tokens.push_back(text.substr(start, end - start));
			}
			start = end + 1;
		}
		if (end != start)
		{
			tokens.push_back(text.substr(start));
		}
		return tokens;
	}
}

namespace big
{
	command::command(const std::string& name, const std::string& label, const std::string& description, std::optional<std::uint8_t> num_args, bool fiber_pool) :
		m_name(name),
		m_label(label),
		m_description(description),
		m_num_args(num_args),
		m_fiber_pool(fiber_pool)
	{
		g_commands[rage::joaat(name)] = this;
	}

	void command::call(const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx)
	{
		if (m_num_args.has_value() && args.size() != m_num_args.value())
		{
			ctx->report_error(std::format("Command {} called with the wrong number of arguments. Expected {}, got {}", m_name, m_num_args.value(), args.size()));
			return;
		}

		if (ctx->get_access_level() < get_access_level())
		{
			ctx->report_error(std::format("You do not have sufficient permissions to call command {}", m_name));
			return;
		}

		if (m_fiber_pool)
			g_fiber_pool->queue_job([this, args, ctx] { execute(args, ctx); });
		else
			execute(args, ctx);
	}

	void command::call(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
	{
		if (m_num_args.has_value() && args.size() != m_num_args.value())
		{
			ctx->report_error(std::format("Command {} called with the wrong number of arguments. Expected {}, got {}", m_name, m_num_args.value(), args.size()));
			return;
		}

		if (ctx->get_access_level() < get_access_level())
		{
			ctx->report_error(std::format("You do not have sufficient permissions to call command {}", m_name));
			return;
		}

		auto parsed = parse_args(args, ctx);
		if (parsed.has_value())
			call(parsed.value(), ctx);
	}

	command* command::get(rage::joaat_t command)
	{
		return g_commands[command];
	}

	void command::call(rage::joaat_t command, const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx)
	{
		g_commands[command]->call(args, ctx);
	}

	void command::call(rage::joaat_t command, const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
	{
		g_commands[command]->call(args, ctx);
	}

	void command::process(const std::string& text, const std::shared_ptr<command_context> ctx)
	{
		auto args = split(text, ' ');
		if (args.size() == 0 || args[0].empty())
		{
			ctx->report_error("No command to call");
			return;
		}
		
		std::uint32_t hash = rage::joaat(args[0]);
		if (!g_commands.contains(hash))
		{
			ctx->report_error(std::format("Command {} does not exist", args[0]));
			return;
		}

		args.erase(args.begin());
		call(hash, args, ctx);
	}
}