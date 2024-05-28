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
	command::command(const std::string& name, const std::string& label, const std::string& description, std::optional<uint8_t> num_args, bool fiber_pool) :
	    m_name(name),
	    m_label(label),
	    m_label_hash(rage::joaat(label)),
	    m_description(description),
	    m_description_hash(rage::joaat(description)),
	    m_num_args(num_args),
	    m_fiber_pool(fiber_pool)
	{
		g_commands[rage::joaat(name)] = this;

		constexpr bool generate_command_documentation = false;
		if constexpr (generate_command_documentation)
		{
			auto translated_label = g_translation_service.get_translation(m_label);
			auto translated_desc  = g_translation_service.get_translation(m_description);
			if (!translated_label.empty())
			{
				LOG(INFO) << "Command | " << m_name << " | " << translated_label << " | " << translated_desc << " | "
				          << std::to_string(m_num_args.value_or(0));
			}
		}
	}

	void command::call(command_arguments& args, const std::shared_ptr<command_context> ctx)
	{
		if (m_num_args.has_value() && args.size() != m_num_args.value())
		{
			ctx->report_error(std::format("Command {} called with the wrong number of arguments. Expected {}, got {}",
			    m_name,
			    m_num_args.value(),
			    args.size()));
			return;
		}

		if (ctx->get_access_level() < get_access_level())
		{
			ctx->report_error(std::format("You do not have sufficient permissions to call command {}", m_name));
			return;
		}

		args.reset_idx();
		if (m_fiber_pool)
			g_fiber_pool->queue_job([this, args, ctx] {
				execute(args, ctx);
			});
		else
			execute(args, ctx);
	}

	void command::call(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
	{
		if (m_num_args.has_value() && args.size() != m_num_args.value())
		{
			ctx->report_error(std::format("Command {} called with the wrong number of arguments. Expected {}, got {}",
			    m_name,
			    m_num_args.value(),
			    args.size()));
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

	void command::call(rage::joaat_t command, command_arguments& args, const std::shared_ptr<command_context> ctx)
	{
		g_commands[command]->call(args, ctx);
	}

	void command::call(rage::joaat_t command, const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
	{
		g_commands[command]->call(args, ctx);
	}

	std::vector<command*> command::get_suggestions(std::string search, const int limit)
	{
		std::vector<command*> result_cmds{};
		for (auto& [hash, command] : g_commands)
		{
			if (command && &command->get_name() && command->get_label().length() == 0)
				continue;

			std::string cmd_name  = command->get_name();
			std::string cmd_label = command->get_label();

			//transform all strings to lower case
			std::transform(cmd_name.begin(), cmd_name.end(), cmd_name.begin(), tolower);
			std::transform(cmd_label.begin(), cmd_label.end(), cmd_label.begin(), tolower);
			std::transform(search.begin(), search.end(), search.begin(), tolower);

			for (auto& cmd : split(search, ';'))
			{
				std::string search_label = split(cmd, ' ')[0];

				if (cmd_name.contains(search_label))
					result_cmds.push_back(command);
				else if (cmd_label.contains(search_label))
					result_cmds.push_back(command);
			}

			// apply our maximum vector size..
			if (result_cmds.size() >= limit)
				break;
		}

		auto compare_by_substring_match = [](command*& a, command*& b, const std::string& sub) -> bool {
			std::string cmd_name_a = a->get_name();
			std::string cmd_name_b = b->get_name();

			if (cmd_name_a == sub && cmd_name_b != sub)
				return true;
			if (cmd_name_b == sub && cmd_name_a != sub)
				return false;

			auto pos_a = cmd_name_a.find(sub);
			auto pos_b = cmd_name_b.find(sub);

			if (pos_a != std::string::npos && pos_b != std::string::npos)
			{
				if (pos_a != pos_b)
					return pos_a < pos_b;

				return cmd_name_a.length() < cmd_name_b.length();
			}

			return pos_a < pos_b;
		};

		std::sort(result_cmds.begin(), result_cmds.end(), [&search, &compare_by_substring_match](command*& a, command*& b) {
			return compare_by_substring_match(a, b, search);
		});

		return result_cmds;
	}

	bool command::process(const std::string& text, const std::shared_ptr<command_context> ctx, bool use_best_suggestion)
	{
		bool success = true;

		for (auto& cmd : split(text, ';'))
		{
			auto args = split(cmd, ' ');
			if (args.size() == 0 || args[0].empty())
			{
				ctx->report_error("No command to call");
				success = false;
				continue;
			}

			//build the best command based on the input
			if (use_best_suggestion)
			{
				const auto cmd_suggestions = get_suggestions(args[0]);

				//is valid suggestion
				if (cmd_suggestions.size() >= 1)
				{
					args[0] = cmd_suggestions[0]->get_name();
				}
				else
				{
					ctx->report_error(std::format("Command {} does not exist", args[0]));
					success = false;
					continue;
				}
			}


			uint32_t hash = rage::joaat(args[0]);
			if (!g_commands.contains(hash))
			{
				ctx->report_error(std::format("Command {} does not exist", args[0]));
				success = false;
				continue;
			}

			args.erase(args.begin());
			call(hash, args, ctx);
		}

		return success;
	}
}