#pragma once
#include "command.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	class player_command;

	class player_all_component : public command
	{
		player_command* m_parent;

	protected:
		virtual void execute(const command_arguments& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;
		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;

	public:
		player_all_component(player_command* parent, const std::string& name, const std::string& label, const std::string& description, std::optional<uint8_t> num_args);
	};

	inline std::unordered_map<rage::joaat_t, player_command*> g_player_commands;

	class player_command : public command
	{
		friend player_all_component;
		std::unique_ptr<player_all_component> m_all_component;

	protected:
		virtual void execute(const command_arguments& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;
		virtual void execute(player_ptr player, const command_arguments& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) = 0;
		virtual std::optional<command_arguments> parse_args(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>()) override;
		virtual std::optional<command_arguments> parse_args_p(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>())
		{
			return {0};
		};

	public:
		static player_command* get(rage::joaat_t command)
		{
			return g_player_commands[command];
		}

		void call(player_ptr player, const command_arguments& args, const std::shared_ptr<command_context> ctx = std::make_shared<default_command_context>());
		player_command(const std::string& name, const std::string& label, const std::string& description, std::optional<uint8_t> num_args, bool make_all_version = true);
	};

}