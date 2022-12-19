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
		virtual void execute(const std::vector<std::uint64_t>& args) override;
	public:
		player_all_component(player_command* parent, const std::string& name, std::uint8_t num_args);
	};

	class player_command : public command
	{
		friend player_all_component;
		std::unique_ptr<player_all_component> m_all_component;

	protected:
		virtual void execute(const std::vector<std::uint64_t>& args) override;
		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& args) = 0;
	public:
		void call(player_ptr player, const std::vector<std::uint64_t>& args);
		player_command(const std::string& name, std::uint8_t num_args, bool make_all_version = true);
	};
}