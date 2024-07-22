#include "backend/looped/looped.hpp"
#include "services/players/player_service.hpp"
#include "util/toxic.hpp"

namespace big
{
	void looped::player_toxic_options()
	{
		if (!*g_pointers->m_gta.m_is_session_started)
			return;

		int rotate_cam_bits = 0;

		g_player_service->iterate([&rotate_cam_bits](const player_entry& entry) {
			if (g_player_service->get_self()->get_ped() && entry.second->get_ped() && entry.second->get_ped()->m_health > 0)
			{
				if (entry.second->kill_loop && !(entry.second->get_ped()->m_damage_bits & (1 << 8)))
					g_pointers->m_gta.m_send_network_damage(g_player_service->get_self()->get_ped(),
					    entry.second->get_ped(),
					    entry.second->get_ped()->m_navigation->get_position(),
					    0,
					    true,
					    "weapon_explosion"_J,
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

				if (entry.second->explosion_loop)
					toxic::blame_explode_player(entry.second, entry.second, EXP_TAG_SUBMARINE_BIG, 9999.0f, true, false, 9999.0f);

				if (entry.second->ragdoll_loop && entry.second->get_ped()->m_net_object)
					g_pointers->m_gta.m_request_ragdoll(entry.second->get_ped()->m_net_object->m_object_id);

				if (entry.second->rotate_cam_loop)
					rotate_cam_bits |= (1 << entry.second->id());
			}

			if (rotate_cam_bits)
			{
				const size_t arg_count = 4;
				int64_t args[arg_count] = {(int64_t)eRemoteEvent::TSECommand, (int64_t)self::id, (int64_t)rotate_cam_bits, (int64_t)eRemoteEvent::TSECommandRotateCam};

				g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, rotate_cam_bits, (int)eRemoteEvent::TSECommand);
			}
		});
	}
}
