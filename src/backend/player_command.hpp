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
		virtual void execute(const std::vector<std::uint64_t>& args, const command_context& ctx) override;
		virtual std::optional<std::vector<std::uint64_t>> parse_args(const std::vector<std::string>& args, const command_context& ctx = default_command_context()) override;
	public:
		player_all_component(player_command* parent, const std::string& name, std::uint8_t num_args);
	};

	class player_command : public command
	{
		friend player_all_component;
		std::unique_ptr<player_all_component> m_all_component;

	protected:
		virtual void execute(const std::vector<std::uint64_t>& args, const command_context& ctx) override;
		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& args, const command_context& ctx) = 0;
		virtual std::optional<std::vector<std::uint64_t>> parse_args(const std::vector<std::string>& args, const command_context& ctx = default_command_context()) override;
		virtual std::optional<std::vector<std::uint64_t>> parse_args_p(const std::vector<std::string>& args, const command_context& ctx = default_command_context()) { return std::vector<std::uint64_t>(); };
	public:
		void call(player_ptr player, const std::vector<std::uint64_t>& args, const command_context& ctx = default_command_context());
		player_command(const std::string& name, std::uint8_t num_args, bool make_all_version = true);
	};
}