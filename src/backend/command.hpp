#pragma once
#include "context/command_context.hpp"
#include "context/default_command_context.hpp"
#include "core/enums.hpp"
#include "gta/joaat.hpp"

namespace big
{
	class command
	{
	protected:
		std::string m_name;
		std::string m_label;
		std::string m_description;
		std::optional<std::uint8_t> m_num_args;
		bool m_fiber_pool;

		virtual void execute(const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) = 0;
		virtual std::optional<std::vector<std::uint64_t>> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>())
		{
			return std::vector<std::uint64_t>();
		};
		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::ADMIN;
		}

	public:
		command(const std::string& name, const std::string& label, const std::string& description, std::optional<std::uint8_t> num_args, bool fiber_pool = true);
		inline const std::string& get_name()
		{
			return m_name;
		}
		inline const std::string& get_label()
		{
			return m_label;
		}
		inline const std::string& get_description()
		{
			return m_description;
		}
		inline const std::optional<std::uint8_t>& get_num_args()
		{
			return m_num_args;
		}

		void call(const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>());
		void call(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>());
		static std::vector<command*> get_suggestions(std::string, int limit = 7);

		static command* get(rage::joaat_t command);

		static void call(rage::joaat_t command, const std::vector<std::uint64_t>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>());
		static void call(rage::joaat_t command, const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>());

		static bool process(const std::string& text, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>(), bool use_best_suggestion = false);
	};

	inline std::unordered_map<rage::joaat_t, command*> g_commands;
}