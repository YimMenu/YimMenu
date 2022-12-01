#include "gta/enums.hpp"
#include "gta/net_game_event.hpp"
#include "hooking.hpp"
#include <network/CNetGamePlayer.hpp>
#include "gta/script_id.hpp"
#include "util/notify.hpp"
#include <base/CObject.hpp>

namespace big
{
	static void script_id_deserialize(CGameScriptId& id, rage::datBitBuffer& buffer)
	{
		id.m_hash = buffer.Read<uint32_t>(32);
		id.m_timestamp = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_position_hash = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<int32_t>(8);
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

		f186 = buffer->Read<uint16_t>(16);
		f208 = buffer->Read<uint16_t>(13);
		ownerNetId = buffer->Read<uint16_t>(13);
		f214 = buffer->Read<uint16_t>(13); // 1604+
		explosionType = (eExplosionTag)buffer->ReadSigned<int>(8); // 1604+ bit size
		damageScale = buffer->Read<int>(8) / 255.0f;

		posX = buffer->ReadSignedFloat(22, 27648.0f);
		posY = buffer->ReadSignedFloat(22, 27648.0f);
		posZ = buffer->ReadFloat(22, 4416.0f) - 1700.0f;

		f242 = buffer->Read<uint8_t>(1);
		f104 = buffer->Read<uint16_t>(16);
		cameraShake = buffer->Read<int>(8) / 127.0f;

		isAudible = buffer->Read<uint8_t>(1);
		f189 = buffer->Read<uint8_t>(1);
		isInvisible = buffer->Read<uint8_t>(1);
		f126 = buffer->Read<uint8_t>(1);
		f241 = buffer->Read<uint8_t>(1);
		f243 = buffer->Read<uint8_t>(1); // 1604+

		f210 = buffer->Read<uint16_t>(13);

		unkX = buffer->ReadSignedFloat(16, 1.1f);
		unkY = buffer->ReadSignedFloat(16, 1.1f);
		unkZ = buffer->ReadSignedFloat(16, 1.1f);

		f190 = buffer->Read<uint8_t>(1);
		f191 = buffer->Read<uint8_t>(1);

		f164 = buffer->Read<uint32_t>(32);

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

		auto f168 = buffer->Read<uint32_t>(32);		 // >= 1868: f_168


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

		if (f208 == 0 && entity && entity->gap28 == 4 && reinterpret_cast<CPed*>(entity)->m_player_info && player->m_player_info->m_ped && player->m_player_info->m_ped->m_net_object && ownerNetId != player->m_player_info->m_ped->m_net_object->m_object_id)
		{
			g_notification_service->push_error("Warning!", std::format("{} blamed {} for explosion", player->get_name(), reinterpret_cast<CPed*>(entity)->m_player_info->m_net_player_data.m_name));
			session::add_infraction(g_player_service->get_by_id(player->m_player_id), Infraction::BLAME_EXPLOSION_DETECTED);
		}
	}

	void hooks::received_event(
		rage::netEventMgr* event_manager,
		CNetGamePlayer* source_player,
		CNetGamePlayer* target_player,
		uint16_t event_id,
		int event_index,
		int event_handled_bitset,
		int buffer_size,
		rage::datBitBuffer* buffer
	)
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

		switch (static_cast<eNetworkEvents>(event_id))
		{
		case eNetworkEvents::KICK_VOTES_EVENT:
		{
			std::uint32_t player_bitfield = buffer->Read<uint32_t>(32);
			if (player_bitfield & (1 << target_player->m_player_id))
			{
				if (g->notifications.received_event.kick_vote.log)
					LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " is voting to kick us.";
				if (g->notifications.received_event.kick_vote.notify)
					g_notification_service->push_warning("Kick Vote", std::format("{} is voting to kick us.", source_player->get_name()));
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
			auto type = buffer->Read<ScriptEntityChangeType>(4);
			uint32_t unk = buffer->Read<uint32_t>(32);
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

				if (g->notifications.received_event.clear_ped_task.log)
					LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " sent CLEAR_PED_TASKS event.";
				if (g->notifications.received_event.clear_ped_task.notify)
					g_notification_service->push_warning("Protections", std::format("{} tried to freeze player.", source_player->get_name()));

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

				if (g->notifications.received_event.clear_ped_task.log)
					LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " sent RAGDOLL_REQUEST event.";
				if (g->notifications.received_event.clear_ped_task.notify)
					g_notification_service->push_warning("Protections", std::format("{} tried to ragdoll player.", source_player->get_name()));

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
				if (g->notifications.received_event.report_cash_spawn.log)
					LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " sent REPORT_CASH_SPAWN event.";
				if (g->notifications.received_event.report_cash_spawn.notify)
					g_notification_service->push_warning("Protections", std::format("{} is spawning cash.", source_player->get_name()));
			}

			break;
		}
		// player sending this event is a modder
		case eNetworkEvents::REPORT_MYSELF_EVENT:
		{
			if (g->notifications.received_event.modder_detect.log)
				LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " sent modder event.";
			if (g->notifications.received_event.modder_detect.notify)
				g_notification_service->push_warning("Protections", std::format("{} sent out a modder event.", source_player->get_name()));

			if (auto plyr = g_player_service->get_by_id(source_player->m_player_id))
				session::add_infraction(plyr, Infraction::TRIGGERED_ANTICHEAT);

			break;
		}
		case eNetworkEvents::REQUEST_CONTROL_EVENT:
		{
			int net_id = buffer->Read<int>(13);
			if (g_local_player && g_local_player->m_vehicle && g_local_player->m_vehicle->m_net_object && g_local_player->m_vehicle->m_net_object->m_object_id == net_id)
			{
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

				if (g->notifications.received_event.request_control_event.log)
					LOG(INFO) << "RECEIVED_EVENT_HANDLER : " << source_player->get_name() << " requested control of player vehicle.";
				if (g->notifications.received_event.request_control_event.notify)
					g_notification_service->push_warning("Protections", std::format("Denied player control request from {}", source_player->get_name()));

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
				buffer->Read<int>(9); // network rope id 
				buffer->Read<float>(19); // pos x
				buffer->Read<float>(19); // pos y
				buffer->Read<float>(19); // pos z
				buffer->Read<float>(19); // rot x
				buffer->Read<float>(19); // rot y
				buffer->Read<float>(19); // rot z
				buffer->Read<float>(16); // length
				int type = buffer->Read<int>(4);

				if (type != 7)
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
				int pop_schedule = buffer->ReadSigned<int>(8); // Pop Schedule
				int pop_group = buffer->Read<int>(32); // Pop Group
				int percentage = buffer->Read<int>(7); // Percentage

				if (pop_group == 0 && (percentage == 0 || percentage == 103))
				{
					notify::crash_blocked(source_player, "pop group override");
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::REMOVE_WEAPON_EVENT:
		{
			int net_id = buffer->Read<int>(13);
			uint32_t hash = buffer->Read<uint32_t>(32);

			if (hash == RAGE_JOAAT("WEAPON_UNARMED"))
			{
				notify::crash_blocked(source_player, "remove unarmed");
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}

			if (g_local_player && g_local_player->m_net_object && g_local_player->m_net_object->m_object_id == net_id)
			{
				g_notification_service->push_warning("Protections", std::format("{} tried to remove a weapon.", source_player->get_name()));
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
				g_notification_service->push_warning("Protections", std::format("{} tried to remove all weapons.", source_player->get_name()));
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}

			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::GIVE_CONTROL_EVENT:
		{
			uint32_t timestamp = buffer->Read<uint32_t>(32);
			int count = buffer->Read<int>(2);
			bool all_objects_migrate_together = buffer->Read<bool>(1);

			if (count > 3)
			{
				count = 3;
			}

			for (int i = 0; i < count; i++)
			{
				int net_id = buffer->Read<int>(13);
				eNetObjType object_type = buffer->Read<eNetObjType>(4);
				int migration_type = buffer->Read<int>(3);

				if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
				{
					notify::crash_blocked(source_player, "out of bounds give control type");
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return;
				}
			}

			buffer->Seek(0);
			g->m_syncing_player = source_player;
			break;
		}
		case eNetworkEvents::NETWORK_PLAY_SOUND_EVENT:
		{
			auto plyr = g_player_service->get_by_id(source_player->m_player_id);
			if (plyr->m_play_sound_rate_limit.process())
			{
				if (plyr->m_play_sound_rate_limit.exceeded_last_process())
				{
					notify::crash_blocked(source_player, "sound spam");
				}
				g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return;
			}
			break;
		}
		case eNetworkEvents::EXPLOSION_EVENT:
		{
			scan_explosion_event(source_player, buffer);
			break;
		}
		default:
			break;
		}

		return g_hooking->get_original<received_event>()(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, buffer_size, buffer);
	}
}
