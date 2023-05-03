#include "ragdoll_player.hpp"

#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	CommandAccessLevel ragdoll_player::get_access_level()
	{
		return CommandAccessLevel::AGGRESSIVE;
	}

	void ragdoll_player::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		if (auto ped = player->get_ped())
			if (auto net_object = ped->m_net_object)
				g_pointers->m_gta.m_request_ragdoll(net_object->m_object_id);
	}
}
