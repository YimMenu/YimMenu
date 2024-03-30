#include "backend/command.hpp"
#include "util/session.hpp"

namespace big
{
	class switch_session : command
	{
		std::unordered_map<eSessionType, const char*> m_session_types = {
		    {eSessionType::JOIN_PUBLIC, "PUB"},
		    {eSessionType::NEW_PUBLIC, "NEWPUB"},
		    {eSessionType::CLOSED_CREW, "CLOSEDCREW"},
		    {eSessionType::CREW, "NEWCREW"},
		    {eSessionType::CLOSED_FRIENDS, "CLOSEDFRIENDS"},
		    {eSessionType::FIND_FRIEND, "FRIENDS"},
		    {eSessionType::SOLO, "SOLO"},
		    {eSessionType::INVITE_ONLY, "INVITE"},
		    {eSessionType::JOIN_CREW, "CREW"},
		    {eSessionType::SC_TV, "SCTV"},
		    {eSessionType::LEAVE_ONLINE, "SINGLEPLAYER"},
		};

		using command::command;

		std::string valid_args(bool was_session_string = false)
		{
			std::string valid_args;
			if (was_session_string)
			{
				for (const auto& session_type_string : m_session_types | std::ranges::views::values)
				{
					if (!empty(valid_args))
					{
						valid_args += ", ";
					}
					valid_args += session_type_string;
				}

				return valid_args;
			}

			for (const auto& session_type_id : m_session_types | std::ranges::views::keys)
			{
				if (!empty(valid_args))
				{
					valid_args += ", ";
				}
				valid_args += std::to_string(static_cast<int>(session_type_id));
			}

			return valid_args;
		}

		virtual std::optional<std::vector<std::string>> get_argument_suggestions(int arg) override
		{
			if (arg == 1)
			{
				std::vector<std::string> suggestions;
				for (const auto& session_type_string : m_session_types | std::ranges::views::values)
				{
					suggestions.push_back(session_type_string);
				}
				return suggestions;
			}

			return std::nullopt;
		}

		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx) override
		{
			command_arguments result(1);
			auto sessionType = static_cast<eSessionType>(std::atoi(args[0].c_str()));
			if (m_session_types.find(sessionType) == m_session_types.end())
			{
				ctx->report_error(std::format("Invalid session type ID given \"{}\", valid inputs are [{}].", args[0], valid_args()));

				return std::nullopt;
			}

			if (sessionType == eSessionType::JOIN_PUBLIC && args[0] != "0")
			{
				const auto it = std::find_if(m_session_types.begin(), m_session_types.end(), [&args](const std::pair<eSessionType, const char*>& t) -> bool {
					return t.second == args[0];
				});
				if (it == m_session_types.end())
				{
					ctx->report_error(std::format("Unknown session type \"{}\", valid inputs are [{}].", args[0], valid_args(true)));

					return std::nullopt;
				}

				sessionType = it->first;
			}

			result.push<eSessionType>(sessionType);
			return result;
		}

		virtual void execute(const command_arguments& args, const std::shared_ptr<command_context> ctx) override
		{
			session::join_type(args.shift<eSessionType>());
		}
	};
	switch_session g_switch_session("joinsession", "JOIN_SESSION", "BACKEND_SESSION_JOIN_SESSION_DESC", 1);
}