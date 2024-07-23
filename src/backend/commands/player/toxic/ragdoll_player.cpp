#include "backend/player_command.hpp"
#include "pointers.hpp"

namespace big
{
	class ragdoll_player : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{ 
			if (auto ped = player->get_ped())
				if (auto net_object = ped->m_net_object)
					g_pointers->m_gta.m_request_ragdoll(net_object->m_object_id);
		}
	};

	ragdoll_player g_ragdoll_player("ragdoll", "RAGDOLL_PLAYER", "RAGDOLL_PLAYER_DESC", 0);
}