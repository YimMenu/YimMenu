#include "kill_player.hpp"

#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	CommandAccessLevel kill_player::get_access_level()
	{
		return CommandAccessLevel::AGGRESSIVE;
	}

	void kill_player::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		if (!player->get_ped())
			return;

		g_pointers->m_gta.m_send_network_damage(g_player_service->get_self()->get_ped(),
		    player->get_ped(),
		    player->get_ped()->m_navigation->get_position(),
		    0,
		    true,
		    RAGE_JOAAT("weapon_explosion"),
		    10000.0f,
		    2,
		    0,
		    (1 << 4),
		    0,
		    0,
		    0,
		    false,
		    false,
		    true,
		    true,
		    nullptr);
	}
}
