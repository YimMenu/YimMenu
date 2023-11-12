#include "core/data/infractions.hpp"
#include "core/data/reactions.hpp"
#include "gta/net_game_event.hpp"
#include "hooking.hpp"
#include "services/notifications/notification_service.hpp"
#include "services/players/player_service.hpp"
#include "util/globals.hpp"
#include "util/misc.hpp"

#include <entities/CDynamicEntity.hpp>
#include <script/globals/GPBD_FM.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	inline bool is_invincible(big::player_ptr player)
	{
		return player->get_ped() && (player->get_ped()->m_damage_bits & (1 << 8));
	}

	inline bool is_invisible(big::player_ptr player)
	{
		if (!player->get_ped())
			return false;

		if (scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[player->id()].IsInvisible)
			return true;

		if ((player->get_current_vehicle() && player->get_current_vehicle()->m_driver == player->get_ped())
		    || PLAYER::IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(player->id()))
			return false; // can't say

		return false; // TODO! have to get data from CPhysicalGameStateDataNode
		              //return (player->get_ped()->m_flags & (int)rage::fwEntity::EntityFlags::IS_VISIBLE) == 0;
	}

	inline bool is_hidden_from_player_list(big::player_ptr player)
	{
		return scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[player->id()].CayoPericoFlags & 1;
	}

	inline bool is_using_rc_vehicle(big::player_ptr player)
	{
		if (misc::has_bit_set(&scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[player->id()].PropertyData.PAD_0365, 29))
			return true; // bandito

		if (misc::has_bit_set(&scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[player->id()].PropertyData.ArcadeData.AppearanceBitset2, 16))
			return true; // tank

		return false;
	}

	inline bool is_using_orbital_cannon(big::player_ptr player)
	{
		return scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[player->id()].OrbitalBitset.IsSet(eOrbitalBitset::kOrbitalCannonActive);
	}

	rage::CEventNetwork* hooks::get_network_event_data(int64_t unk, rage::CEventNetwork* net_event)
	{
		switch (net_event->get_type())
		{
		case rage::eEventNetworkType::CEventNetworkRemovedFromSessionDueToComplaints:
		{
			g_notification_service->push_warning("Kicked", "You have been desync kicked.", true);
			break;
		}
		case rage::eEventNetworkType::CEventNetworkEntityDamage:
		{
			rage::sEntityDamagedData damage_data;
			net_event->get_extra_information(&damage_data, sizeof(damage_data));

			if (damage_data.m_weapon_used == RAGE_JOAAT("WEAPON_STICKYBOMB") || damage_data.m_weapon_used == RAGE_JOAAT("VEHICLE_WEAPON_MINE_KINETIC_RC")
			    || damage_data.m_weapon_used == RAGE_JOAAT("VEHICLE_WEAPON_MINE_EMP_RC") || damage_data.m_weapon_used == RAGE_JOAAT("VEHICLE_WEAPON_MINE_KINETIC")
			    || damage_data.m_weapon_used == RAGE_JOAAT("VEHICLE_WEAPON_MINE_EMP") || damage_data.m_weapon_used == RAGE_JOAAT("VEHICLE_WEAPON_MINE_SPIKE"))
				break;

			if (auto damager = g_pointers->m_gta.m_handle_to_ptr(damage_data.m_damager_index);
			    damager && damager->m_entity_type == 4 && reinterpret_cast<CPed*>(damager)->m_player_info)
			{
				if (auto player = g_player_service->get_by_host_token(
				        reinterpret_cast<CPed*>(damager)->m_player_info->m_net_player_data.m_host_token))
				{
					if (PLAYER::IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(player->id()))
					{
						if (scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[player->id()].PlayerBlip.PlayerVehicleBlipType == eBlipType::SUBMARINE)
							break;

						if (is_using_rc_vehicle(player))
							break;
					}
					else
					{
						if (auto vehicle = player->get_current_vehicle())
							if (auto model_info = vehicle->m_model_info)
								if (model_info->m_hash == RAGE_JOAAT("rcbandito") || model_info->m_hash == RAGE_JOAAT("minitank")
								    || model_info->m_hash == RAGE_JOAAT("kosatka"))
									break;
					}

					if (NETWORK::NETWORK_IS_ACTIVITY_SESSION())
						break;

					if (!NETWORK::NETWORK_ARE_PLAYERS_IN_SAME_TUTORIAL_SESSION(self::id, player->id()))
						break;

					if (globals::get_interior_from_player(player->id()) != 0)
						break;

					if (player->get_player_info() && player->get_player_info()->m_game_state == eGameState::InMPCutscene)
						break;

					if (auto victim = g_pointers->m_gta.m_handle_to_ptr(damage_data.m_victim_index); victim && victim->m_entity_type == 4)
					{
						if (is_invincible(player))
							g_reactions.modder_detection.process(player, false, Infraction::ATTACKING_WITH_GODMODE, true);

						if (is_invisible(player))
						{
							if (!reinterpret_cast<CPed*>(victim)->m_player_info)
								break;

							if (damage_data.m_weapon_used == RAGE_JOAAT("WEAPON_EXPLOSION") || damage_data.m_weapon_used == RAGE_JOAAT("WEAPON_RAMMED_BY_CAR")
							    || damage_data.m_weapon_used == RAGE_JOAAT("WEAPON_RUN_OVER_BY_CAR"))
								break;

							g_reactions.modder_detection.process(player, false, Infraction::ATTACKING_WITH_INVISIBILITY, true);
						}

						if (is_hidden_from_player_list(player))
							g_reactions.modder_detection.process(player, false, Infraction::ATTACKING_WHEN_HIDDEN_FROM_PLAYER_LIST, true);

						if (is_using_orbital_cannon(player))
							g_reactions.modder_detection.process(player, false, Infraction::SPOOFED_DATA, true);
					}
				}
			}
			break;
		}
		}

		return g_hooking->get_original<get_network_event_data>()(unk, net_event);
	}
}
