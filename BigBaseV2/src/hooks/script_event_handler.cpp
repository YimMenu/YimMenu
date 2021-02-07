#include "hooking.hpp"
#include "features/notify.hpp"
#include "gta/enums.hpp"
#include "pointers.hpp"
#include "natives.hpp"

namespace big
{
	bool hooks::script_event_handler(std::int64_t NetEventStruct, CNetGamePlayer* net_game_player)
	{
		auto args = reinterpret_cast<std::int64_t*>(NetEventStruct + 0x70);
		Player player = net_game_player->player_id;

		int64_t hash = args[0];

		auto& protections = g_settings.options["settings"]["script_protections"];
		char type[32] = "";


		switch (hash)
		{
		case RemoteEvents::Bounty:
			if (protections["bounty"])
				strcpy(type, "Bounty");

			break;
		case RemoteEvents::CeoBan:
			if (protections["ceo_ban"])
				strcpy(type, "Ceo Ban");

			break;
		case RemoteEvents::CeoKick:
			if (protections["ceo_kick"])
				strcpy(type, "Ceo Kick");

			break;
		case RemoteEvents::CeoMoney:
			if (protections["ceo_money"])
				strcpy(type, "Ceo Money");

			break;
		case RemoteEvents::ClearWantedLevel:
			if (protections["clear_wanted_level"])
				strcpy(type, "Clear Wanted Level");

			break;
		case RemoteEvents::FakeDeposit:
			if (protections["fake_deposit"])
				strcpy(type, "Fake Deposit");

			break;
		case RemoteEvents::ForceMission:
		case RemoteEvents::ForceMission2:
		case RemoteEvents::ForceMission3:
			if (protections["force_mission"])
				strcpy(type, "Force Mission");

			break;
		case RemoteEvents::GtaBanner:
			if (protections["gta_banner"])
				strcpy(type, "GTA Banner");

			break;
		case RemoteEvents::PersonalVehicleDestroyed:
			if (protections["personal_vehicle_destroyed"])
				strcpy(type, "Personal Vehicle Destroyed");

			break;
		case RemoteEvents::RemoteOffradar:
			if (protections["remote_off_radar"])
				strcpy(type, "Remote Off Radar");

			break;
		case RemoteEvents::SendToCutscene:
			if (protections["send_to_cutscene"])
				strcpy(type, "Send To Cutscene");

			break;
		case RemoteEvents::SendToIsland:
			if (protections["send_to_island"])
				strcpy(type, "Send To Island");

			break;
		case RemoteEvents::SoundSpam:
		case RemoteEvents::SoundSpam2:
			if (protections["sound_spam"])
				strcpy(type, "Sound Spam");

			break;
		case RemoteEvents::Spectate:
			if (protections["spectate"])
				strcpy(type, "Specate");

			break;
		case RemoteEvents::Teleport:
			if (protections["force_teleport"])
				strcpy(type, "Force Teleport");

			break;
		case RemoteEvents::TransactionError:
			if (protections["transaction_error"])
				strcpy(type, "Transaction Error");

			break;
		case RemoteEvents::VehicleKick:
			if (protections["vehicle_kick"])
				strcpy(type, "Vehicle Kick");

			break;
		}

		if (protections["kick"])
		{
			if (hash == 1317868303 || hash == 495824472) return true;

			for (int64_t kick_hash : kick_hashes)
			{
				if (hash == kick_hash)
				{
					sprintf(type, "General Kick (%zd)", hash);

					break;
				}
			}
		}

		if (strlen(type) != 0)
		{
			char msg[128];
			strcpy(msg, "~g~BLOCKED SCRIPT EVENT~s~\nFrom: <C>");
			strcat(msg, g_pointers->m_get_player_name(player));
			strcat(msg, "</C>\nEvent Type: ~b~");
			strcat(msg, type);

			notify::above_map(msg);

			return true;
		}

		if (g_settings.options["settings"]["logging"]["script_events"])
		{
			LOG(INFO) << "Received Script Event";
			LOG(INFO) << "Player: " << PLAYER::GET_PLAYER_NAME(player);
			LOG(INFO) << "Hash: " << hash;

			for (int i = 1; i < sizeof(args); i++)
				LOG(INFO) << "Arg #" << i << ": " << args[i];
		}

		return g_hooking->m_script_event_hook.get_original<decltype(&script_event_handler)>()(NetEventStruct, net_game_player);
	}
}