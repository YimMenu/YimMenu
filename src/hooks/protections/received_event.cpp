#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "gta/net_game_event.hpp"
#include "gta/script_id.hpp"
#include "hooking.hpp"
#include "util/math.hpp"
#include "util/notify.hpp"
#include "util/toxic.hpp"

#include <base/CObject.hpp>
#include <network/CNetGamePlayer.hpp>

namespace big
{
	static void script_id_deserialize(CGameScriptId& id, rage::datBitBuffer& buffer)
	{
		id.m_hash      = buffer.Read<uint32_t>(32);
		id.m_timestamp = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_position_hash = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<int32_t>(8);
	}

	void scan_weapon_damage_event(CNetGamePlayer* player, rage::datBitBuffer* buffer)
	{
		uint8_t damageType;
		uint32_t weaponType;// weaponHash

		bool overrideDefaultDamage;
		bool hitEntityWeapon;
		bool hitWeaponAmmoAttachment;
		bool silenced;

		uint32_t damageFlags;
		bool hasActionResult;

		uint32_t actionResultName;
		uint16_t actionResultId;
		uint32_t f104;

		uint32_t weaponDamage;
		bool isNetTargetPos;

		rage::fvector3 localPos;

		bool f112;

		uint32_t damageTime;
		bool willKill;
		uint32_t f120;
		bool hasVehicleData;

		uint16_t f112_1;

		uint16_t parentGlobalId;// Source entity?
		uint16_t hitGlobalId;   // Target entity?

		uint8_t tyreIndex;
		uint8_t suspensionIndex;
		uint8_t hitComponent;

		bool f133;
		bool hasImpactDir;

		rage::fvector3 impactDir;

		damageType = buffer->Read<uint8_t>(2);
		weaponType = buffer->Read<uint32_t>(32);

		overrideDefaultDamage   = buffer->Read<uint8_t>(1);
		hitEntityWeapon         = buffer->Read<uint8_t>(1);
		hitWeaponAmmoAttachment = buffer->Read<uint8_t>(1);
		silenced                = buffer->Read<uint8_t>(1);

		damageFlags = buffer->Read<uint32_t>(24);
		// (damageFlags >> 1) & 1
		hasActionResult = buffer->Read<uint8_t>(1);

		if (hasActionResult)
		{
			actionResultName = buffer->Read<uint32_t>(32);
			actionResultId   = buffer->Read<uint16_t>(16);
			f104
				= buffer->Read<uint32_t>(32);
		}

		if (overrideDefaultDamage)
		{
			weaponDamage = buffer->Read<uint32_t>(17);
		}
		else
		{
			weaponDamage = 0;
		}

		bool _f92 = buffer->Read<uint8_t>(1);

		if (_f92)
		{
			buffer->Read<uint8_t>(4);
		}

		isNetTargetPos = buffer->Read<uint8_t>(1);

		if (isNetTargetPos)
		{
			localPos.x = buffer->ReadSignedFloat(16, 55.f);// divisor: 0x425C0000
			localPos.y = buffer->ReadSignedFloat(16, 55.f);
			localPos.z = buffer->ReadSignedFloat(16, 55.f);
		}

		if (damageType == 3)
		{
			damageTime = buffer->Read<uint32_t>(32);
			willKill   = buffer->Read<uint8_t>(1);

			if (hasActionResult)
			{
				hitGlobalId = buffer->Read<uint16_t>(13);
			}
			else
			{
				hitGlobalId = 0;
			}

			f112 = buffer->Read<uint8_t>(1);

			if (!f112)
			{
				f112_1 = buffer->Read<uint16_t>(11);
			}
			else
			{
				f112_1 = buffer->Read<uint16_t>(16);
			}
		}
		else
		{
			parentGlobalId = buffer->Read<uint16_t>(13);// +118
			hitGlobalId    = buffer->Read<uint16_t>(13);// +120
		}

		if (damageType < 2)
		{
			localPos.x = buffer->ReadSignedFloat(16, 55.f);// divisor: 0x425C0000
			localPos.y = buffer->ReadSignedFloat(16, 55.f);
			localPos.z = buffer->ReadSignedFloat(16, 55.f);

			if (damageType == 1)
			{
				hasVehicleData = buffer->Read<uint8_t>(1);

				if (hasVehicleData)
				{
					tyreIndex       = buffer->Read<uint8_t>(4);// +122
					suspensionIndex = buffer->Read<uint8_t>(4);// +123
				}
			}
		}
		else
		{
			hitComponent = buffer->Read<uint8_t>(5);// +108
		}

		f133         = buffer->Read<uint8_t>(1);
		hasImpactDir = buffer->Read<uint8_t>(1);

		if (hasImpactDir)
		{
			impactDir.x = buffer->ReadSignedFloat(16, 6.2831854820251f);// divisor: 0x40C90FDB
			impactDir.y = buffer->ReadSignedFloat(16, 6.2831854820251f);
			impactDir.z = buffer->ReadSignedFloat(16, 6.2831854820251f);
		}

		buffer->Seek(0);

		// LOG(INFO) << localPos.x << " " << localPos.y << " " << localPos.z << ". " << math::distance_between_vectors(localPos, *g_local_player->m_navigation->get_position()) << " " << (g_local_player->m_net_object->m_object_id == hitGlobalId ? "TRUE" : "FALSE") << " " << damageType << " " << damageFlags;

		if (damageType == 3 && (damageFlags & (1 << 1)) == 0)
			hitGlobalId = g_local_player ? g_local_player->m_net_object->m_object_id : 0;

		if (g.session.damage_karma && g_local_player && g_local_player->m_net_object
		    && (g_local_player->m_net_object->m_object_id == hitGlobalId
		        || math::distance_between_vectors(localPos, *g_local_player->m_navigation->get_position()) < 1.5f))
		{
			int id = player->m_player_id;
			g_fiber_pool->queue_job([id, hitComponent, overrideDefaultDamage, weaponType, weaponDamage, tyreIndex, suspensionIndex, damageFlags, actionResultName, actionResultId, f104, hitEntityWeapon, hitWeaponAmmoAttachment, silenced, hasImpactDir, impactDir, localPos] {
				auto player = g_player_service->get_by_id(id);

				if (!player->is_valid() || !player->get_ped())
					return;

				g_pointers->m_send_network_damage((CEntity*)g_player_service->get_self()->get_ped(),
				    (CEntity*)player->get_ped(),
				    (rage::fvector3*)&localPos,
				    hitComponent,
				    overrideDefaultDamage,
				    weaponType,
				    weaponDamage,
				    tyreIndex,
				    suspensionIndex,
				    damageFlags,
				    actionResultName,
				    actionResultId,
				    f104,
				    hitEntityWeapon,
				    hitWeaponAmmoAttachment,
				    silenced,
				    false,
				    player->get_ped()->m_navigation->get_position());
			});
		}
	}

	void scan_explosion_event(CNetGamePlayer* player, rage::datBitBuffer* buffer)
	{
		uint16_t f186;
		uint16_t f208;
		int ownerNetId;
		uint16_t f214;
		eExplosionTag explosionType;
		float damageScale;

		float posX;
		float posY;
		float posZ;

		bool f242;
		uint16_t f104;
		float cameraShake;

		bool isAudible;
		bool f189;
		bool isInvisible;
		bool f126;
		bool f241;
		bool f243;

		uint16_t f210;

		float unkX;
		float unkY;
		float unkZ;

		bool f190;
		bool f191;

		uint32_t f164;

		float posX224;
		float posY224;
		float posZ224;

		bool f240;
		uint16_t f218;
		bool f216;

		// clang-format off

		f186 = buffer->Read<uint16_t>(16);
		f208 = buffer->Read<uint16_t>(13);
		ownerNetId  = buffer->Read<uint16_t>(13);
		f214        = buffer->Read<uint16_t>(13);               // 1604+
		explosionType = (eExplosionTag)buffer->ReadSigned<int>(8);// 1604+ bit size
		damageScale = buffer->Read<int>(8) / 255.0f;

		posX        = buffer->ReadSignedFloat(22, 27648.0f);
		posY        = buffer->ReadSignedFloat(22, 27648.0f);
		posZ        = buffer->ReadFloat(22, 4416.0f) - 1700.0f;

		f242        = buffer->Read<uint8_t>(1);
		f104        = buffer->Read<uint16_t>(16);
		cameraShake = buffer->Read<int>(8) / 127.0f;

		isAudible   = buffer->Read<uint8_t>(1);
		f189        = buffer->Read<uint8_t>(1);
		isInvisible = buffer->Read<uint8_t>(1);
		f126        = buffer->Read<uint8_t>(1);
		f241        = buffer->Read<uint8_t>(1);
		f243        = buffer->Read<uint8_t>(1);// 1604+

		f210        = buffer->Read<uint16_t>(13);

		unkX        = buffer->ReadSignedFloat(16, 1.1f);
		unkY        = buffer->ReadSignedFloat(16, 1.1f);
		unkZ        = buffer->ReadSignedFloat(16, 1.1f);

		f190     	= buffer->Read<uint8_t>(1);
		f191        = buffer->Read<uint8_t>(1);
		f164        = buffer->Read<uint32_t>(32);

		if (f242)
		{
			posX224 = buffer->ReadSignedFloat(31, 27648.0f);
			posY224 = buffer->ReadSignedFloat(31, 27648.0f);
			posZ224 = buffer->ReadFloat(31, 4416.0f) - 1700.0f;
		}
		else
		{
			posX224 = 0;
			posY224 = 0;
			posZ224 = 0;
		}

		auto f168 = buffer->Read<uint32_t>(32);// >= 1868: f_168


		f240 = buffer->Read<uint8_t>(1);
		if (f240)
		{
			f218 = buffer->Read<uint16_t>(16);

			if (f191)
			{
				f216 = buffer->Read<uint8_t>(8);
			}
		}

		buffer->Seek(0);

		auto object = g_pointers->m_get_net_object(*g_pointers->m_network_object_mgr, ownerNetId, true);
		auto entity = object ? object->GetGameObject() : nullptr;

		auto offset_object = g_pointers->m_get_net_object(*g_pointers->m_network_object_mgr, f210, true);

		if (f208 == 0 && entity && entity->m_entity_type == 4 && reinterpret_cast<CPed*>(entity)->m_player_info
			&& player->m_player_info->m_ped && player->m_player_info->m_ped->m_net_object
			&& ownerNetId != player->m_player_info->m_ped->m_net_object->m_object_id && !offset_object)
		{
			g_notification_service->push_error("WARNING"_T.data(),
				std::vformat("BLAMED_FOR_EXPLOSION"_T,
					std::make_format_args(player->get_name(),
						reinterpret_cast<CPed*>(entity)->m_player_info->m_net_player_data.m_name)));
			session::add_infraction(g_player_service->get_by_id(player->m_player_id), Infraction::BLAME_EXPLOSION_DETECTED);
			return;
		}

		if (g.session.explosion_karma && g_local_player
			&& math::distance_between_vectors({posX, posY, posZ}, *g_local_player->m_navigation->get_position()) < 3.0f)
		{
			int id = player->m_player_id;
			g_fiber_pool->queue_job([id, explosionType, damageScale, cameraShake, isAudible, isInvisible] {
				toxic::blame_explode_player(g_player_service->get_self(), g_player_service->get_by_id(id), explosionType, damageScale, isAudible, isInvisible, cameraShake);
			});
		}

		// clang-format on
	}

	void hooks::received_event(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int buffer_size, rage::datBitBuffer* buffer)
	{
		if (event_id > 91u)
		{
			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			return;
		}

		const auto event_name = *(char**)((DWORD64)event_manager + 8i64 * event_id + 243376);
		if (event_name == nullptr || source_player == nullptr || source_player->m_player_id < 0 || source_player->m_player_id >= 32)
		{
			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			return;
		}

		auto plyr = g_player_service->get_by_id(source_player->m_player_id);

		switch (static_cast<eNetworkEvents>(event_id))
		{
		case eNetworkEvents::KICK_VOTES_EVENT:
		{
			std::uint32_t player_bitfield = buffer->Read<uint32_t>(32);
			if (player_bitfield & (1 << target_player->m_player_id))
			{
				g.reactions.kick_vote.process(plyr);
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::NETWORK_INCREMENT_STAT_EVENT:
		{
			const auto increment_stat_event = std::make_unique<CNetworkIncrementStatEvent>();
			buffer->ReadDword(&increment_stat_event->m_stat, 0x20);
			buffer->ReadDword(&increment_stat_event->m_amount, 0x20);
			if (hooks::increment_stat_event(increment_stat_event.get(), source_player))
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::SCRIPT_ENTITY_STATE_CHANGE_EVENT:
		{
			uint16_t entity = buffer->Read<uint16_t>(13);
			auto type       = buffer->Read<ScriptEntityChangeType>(4);
			uint32_t unk    = buffer->Read<uint32_t>(32);
			if (type == ScriptEntityChangeType::SettingOfTaskVehicleTempAction)
			{
				uint16_t ped_id = buffer->Read<uint16_t>(13);
				uint32_t action = buffer->Read<uint32_t>(8);

				if ((action >= 15 && action <= 18) || action == 33)
				{
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					notify::crash_blocked(source_player, "vehicle temp action");
					return;
				}
			}
			else if (type > ScriptEntityChangeType::SetVehicleExclusiveDriver || type < ScriptEntityChangeType::BlockingOfNonTemporaryEvents)
			{
				notify::crash_blocked(source_player, "invalid script entity change type");
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::SCRIPTED_GAME_EVENT:
		{
			const auto scripted_game_event = std::make_unique<CScriptedGameEvent>();
			buffer->ReadDword(&scripted_game_event->m_args_size, 32);
			if (scripted_game_event->m_args_size - 1 <= 0x1AF)
				buffer->ReadArray(&scripted_game_event->m_args, 8 * scripted_game_event->m_args_size);

			if (hooks::scripted_game_event(scripted_game_event.get(), source_player))
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				return;
			}
			buffer->Seek(0);

			break;
		}
		case eNetworkEvents::NETWORK_CLEAR_PED_TASKS_EVENT:
		{
			int net_id = buffer->Read<int>(13);

			if (g_local_player && g_local_player->m_net_object && g_local_player->m_net_object->m_object_id == net_id)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				g.reactions.clear_ped_tasks.process(plyr);
				return;
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::RAGDOLL_REQUEST_EVENT:
		{
			int net_id = buffer->Read<int>(13);

			if (g_local_player && g_local_player->m_net_object && g_local_player->m_net_object->m_object_id == net_id)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				g.reactions.remote_ragdoll.process(plyr);
				return;
			}

			buffer->Seek(0);
			break;
		}
		// Don't block this event, we still want to report this player
		// because if we still report others, our account seems less fishy
		case eNetworkEvents::REPORT_CASH_SPAWN_EVENT:
		{
			uint32_t money;

			buffer->Seek(64);
			buffer->ReadDword(&money, 32);
			buffer->Seek(0);

			if (money >= 2000)
			{
				g.reactions.report_cash_spawn.process(plyr);
			}

			break;
		}
		// player sending this event is a modder
		case eNetworkEvents::REPORT_MYSELF_EVENT:
		{
			if (auto plyr = g_player_service->get_by_id(source_player->m_player_id))
				session::add_infraction(plyr, Infraction::TRIGGERED_ANTICHEAT);

			g.reactions.modder_detection.process(plyr);
			break;
		}
		case eNetworkEvents::REQUEST_CONTROL_EVENT:
		{
			int net_id = buffer->Read<int>(13);
			if (g_local_player && g_local_player->m_vehicle && g_local_player->m_vehicle->m_net_object
			    && g_local_player->m_vehicle->m_net_object->m_object_id == net_id && g_local_player->m_vehicle->m_driver == g_local_player)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				g.reactions.request_control_event.process(plyr);
				return;
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::SCRIPT_WORLD_STATE_EVENT:
		{
			auto type = buffer->Read<WorldStateDataType>(4);
			buffer->Read<bool>(1);
			CGameScriptId id;
			script_id_deserialize(id, *buffer);

			if (type == WorldStateDataType::Rope)
			{
				buffer->Read<int>(9);   // network rope id
				buffer->Read<float>(19);// pos x
				buffer->Read<float>(19);// pos y
				buffer->Read<float>(19);// pos z
				buffer->Read<float>(19);// rot x
				buffer->Read<float>(19);// rot y
				buffer->Read<float>(19);// rot z
				buffer->Read<float>(16);// length
				int type             = buffer->Read<int>(4);
				float initial_length = buffer->Read<float>(16);
				float min_length     = buffer->Read<float>(16);

				if (type == 0 || initial_length < min_length)// https://docs.fivem.net/natives/?_0xE832D760399EB220
				{
					// most definitely a crash
					LOG(INFO) << std::hex << std::uppercase << "0x" << id.m_hash;
					notify::crash_blocked(source_player, "rope");
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}
			else if (type == WorldStateDataType::PopGroupOverride)
			{
				int pop_schedule = buffer->ReadSigned<int>(8);// Pop Schedule
				int pop_group    = buffer->Read<int>(32);     // Pop Group
				int percentage   = buffer->Read<int>(7);      // Percentage

				if (pop_group == 0 && (percentage == 0 || percentage == 103))
				{
					notify::crash_blocked(source_player, "pop group override");
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}
			else if (type > WorldStateDataType::VehiclePlayerLocking || type < WorldStateDataType::CarGen)
			{
				notify::crash_blocked(source_player, "invalid world state type");
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::REMOVE_WEAPON_EVENT:
		{
			int net_id    = buffer->Read<int>(13);
			uint32_t hash = buffer->Read<uint32_t>(32);

			if (hash == RAGE_JOAAT("WEAPON_UNARMED"))
			{
				notify::crash_blocked(source_player, "remove unarmed");
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}

			if (g_local_player && g_local_player->m_net_object && g_local_player->m_net_object->m_object_id == net_id)
			{
				g_notification_service->push_warning("PROTECTIONS"_T.data(),
				    std::vformat("REMOVE_WEAPON_ATTEMPT"_T, std::make_format_args(source_player->get_name())));
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::REMOVE_ALL_WEAPONS_EVENT:
		{
			int net_id = buffer->Read<int>(13);

			if (g_local_player && g_local_player->m_net_object && g_local_player->m_net_object->m_object_id == net_id)
			{
				g_notification_service->push_warning("PROTECTIONS"_T.data(),
				    std::vformat("REMOVE_ALL_WEAPONS_ATTEMPT"_T, std::make_format_args(source_player->get_name())));
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::GIVE_CONTROL_EVENT:
		{
			uint32_t timestamp                = buffer->Read<uint32_t>(32);
			int count                         = buffer->Read<int>(2);
			bool all_objects_migrate_together = buffer->Read<bool>(1);

			if (count > 3)
			{
				count = 3;
			}

			for (int i = 0; i < count; i++)
			{
				int net_id              = buffer->Read<int>(13);
				eNetObjType object_type = buffer->Read<eNetObjType>(4);
				int migration_type      = buffer->Read<int>(3);

				if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
				{
					notify::crash_blocked(source_player, "out of bounds give control type");
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}

			buffer->Seek(0);
			g.m_syncing_player = source_player;
			break;
		}
		case eNetworkEvents::NETWORK_PLAY_SOUND_EVENT:
		{
			if (plyr && plyr->m_play_sound_rate_limit.process())
			{
				if (plyr->m_play_sound_rate_limit.exceeded_last_process())
				{
					notify::crash_blocked(source_player, "sound spam");
				}
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}

			bool is_entity = buffer->Read<bool>(1);
			std::int16_t entity_net_id;
			rage::fvector3 position;
			std::uint32_t ref_hash;

			if (is_entity)
				entity_net_id = buffer->Read<std::int16_t>(13);
			else
			{
				position.x = buffer->ReadSignedFloat(19, 1337.0f);
				position.y = buffer->ReadSignedFloat(19, 1337.0f);
				position.z = buffer->ReadFloat(19, 1337.0f);
			}

			bool has_ref = buffer->Read<bool>(1);
			if (has_ref)
				ref_hash = buffer->Read<std::uint32_t>(32);

			std::uint32_t sound_hash = buffer->Read<std::uint32_t>(32);

			if (sound_hash == RAGE_JOAAT("Remote_Ring") && plyr)
			{
				g.reactions.sound_spam.process(plyr);
				return;
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::EXPLOSION_EVENT:
		{
			scan_explosion_event(source_player, buffer);
			break;
		}
		case eNetworkEvents::WEAPON_DAMAGE_EVENT:
		{
			scan_weapon_damage_event(source_player, buffer);
			break;
		}
		default: break;
		}

		return g_hooking->get_original<received_event>()(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, buffer_size, buffer);
	}
}
