#pragma once
#include "command_arguments.hpp"
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
		rage::joaat_t m_label_hash;
		std::string m_description;
		rage::joaat_t m_description_hash;
		std::optional<uint8_t> m_num_args;
		bool m_fiber_pool;

		virtual void execute(const command_arguments& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) = 0;
		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>())
		{
			return {0};
		};
		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::ADMIN;
		}

	public:
		command(const std::string& name, const std::string& label, const std::string& description, std::optional<uint8_t> num_args, bool fiber_pool = true);
		inline const std::string& get_name()
		{
			return m_name;
		}
		inline const std::string get_label()
		{
			std::string key;
			if (key = g_translation_service.get_translation(m_label_hash); key.empty())
				key = m_label;

			return key;
		}
		inline const std::string get_description()
		{
			std::string key;
			if (key = g_translation_service.get_translation(m_description_hash); key.empty())
				key = m_description;

			return key;
		}
		inline const std::optional<uint8_t>& get_num_args()
		{
			return m_num_args;
		}

		void call(command_arguments& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>());
		void call(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>());
		static std::vector<command*> get_suggestions(std::string, int limit = 7);

		static command* get(rage::joaat_t command);

		static void call(rage::joaat_t command, command_arguments& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>());
		static void call(rage::joaat_t command, const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>());

		static bool process(const std::string& text, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>(), bool use_best_suggestion = false);
	};

	inline std::unordered_map<rage::joaat_t, command*> g_commands;
}