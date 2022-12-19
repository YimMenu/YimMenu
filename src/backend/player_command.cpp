#include "player_command.hpp"
#include "fiber_pool.hpp"

namespace big
{
	player_all_component::player_all_component(player_command* parent, const std::string& name, std::uint8_t num_args) :
		command(name + "all", num_args),
		m_parent(parent)
	{
	}

	void player_all_component::execute(const std::vector<std::uint64_t>& args)
	{
		g_fiber_pool->queue_job([this, args]
		{
			g_player_service->iterate([this, args](const player_entry& player) {
				m_parent->execute(player.second, args);
			});
		});
	}

	player_command::player_command(const std::string& name, std::uint8_t num_args, bool make_all_version) : 
		command(name, num_args + 1)
	{
		if (make_all_version)
			m_all_component = std::make_unique<player_all_component>(this, name, num_args);
	}

	void player_command::execute(const std::vector<std::uint64_t>& args)
	{
		g_fiber_pool->queue_job([this, args]
		{
			std::vector<std::uint64_t> new_args;

			// TODO: This looks ugly and inefficient
			for (int i = 1; i < m_num_args; i++)
				new_args.push_back(args[i]);

			for (auto& plyr : g_player_service->players())
			{
				if (plyr.second->id() == args[0])
				{
					execute(plyr.second, new_args);
					return;
				}
			}

			LOG(WARNING) << "Tried to execute command " << m_name << ", but a player with index " << args[0] << " was not found";
		});
	}

	void player_command::call(player_ptr player, const std::vector<std::uint64_t>& args)
	{
		// TODO: Code duplication
		if (args.size() != (m_num_args - 1))
		{
			LOG(WARNING) << "Command " << m_name << " called with the wrong number of arguments. Expected " << (m_num_args - 1) << ", got " << args.size();
			return;
		}

		g_fiber_pool->queue_job([this, player, args] {
			if (player->is_valid())
				execute(player, args);
		});
	}
}