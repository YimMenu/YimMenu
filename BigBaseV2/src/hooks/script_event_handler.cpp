#include "hooking.hpp"
#include "gta/enums.hpp"
#include "util/notify.hpp"

namespace big
{
	bool hooks::scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player)
	{
		auto args = scripted_game_event->m_args;

		RemoteEvent hash = (RemoteEvent)args[0];

		char type[32] = "";


		switch (hash)
		{
		case RemoteEvent::Bounty:
			if (g.protections.bounty)
				strcpy(type, "Bounty");

			break;
		case RemoteEvent::CeoBan:
			if (g.protections.ceo_ban)
				strcpy(type, "Ceo Ban");

			break;
		case RemoteEvent::CeoKick:
			if (g.protections.ceo_kick)
				strcpy(type, "Ceo Kick");

			break;
		case RemoteEvent::CeoMoney:
			if (g.protections.ceo_money)
				strcpy(type, "Ceo Money");

			break;
		case RemoteEvent::ClearWantedLevel:
			if (g.protections.clear_wanted_level)
				strcpy(type, "Clear Wanted Level");

			break;
		case RemoteEvent::FakeDeposit:
			if (g.protections.fake_deposit)
				strcpy(type, "Fake Deposit");

			break;
		case RemoteEvent::ForceMission:
			if (g.protections.force_mission)
				strcpy(type, "Force Mission");

			break;
		case RemoteEvent::GtaBanner:
			if (g.protections.gta_banner)
				strcpy(type, "GTA Banner");

			break;
		case RemoteEvent::PersonalVehicleDestroyed:
			if (g.protections.personal_vehicle_destroyed)
				strcpy(type, "Personal Vehicle Destroyed");

			break;
		case RemoteEvent::RemoteOffradar:
			if (g.protections.remote_off_radar)
				strcpy(type, "Remote Off Radar");

			break;
		case RemoteEvent::SendToCutscene:
			if (g.protections.send_to_cutscene)
				strcpy(type, "Send To Cutscene");

			break;
		case RemoteEvent::SendToIsland:
			if (g.protections.send_to_island)
				strcpy(type, "Send To Island");

			break;
		case RemoteEvent::SoundSpam:
			if (g.protections.sound_spam)
				strcpy(type, "Sound Spam");

			break;
		case RemoteEvent::Spectate:
			if (g.protections.spectate)
				strcpy(type, "Specate");

			break;
		case RemoteEvent::Teleport:
			if (g.protections.force_teleport)
				strcpy(type, "Force Teleport");

			break;
		case RemoteEvent::TransactionError:
			if (g.protections.transaction_error)
				strcpy(type, "Transaction Error");

			break;
		case RemoteEvent::VehicleKick:
			if (g.protections.vehicle_kick)
				strcpy(type, "Vehicle Kick");

			break;
		}

		if (strlen(type) != 0)
		{
			char msg[128];
			strcpy(msg, "~g~BLOCKED SCRIPT EVENT~s~\nFrom: <C>");
			strcat(msg, player->get_name());
			strcat(msg, "</C>\nEvent Type: ~b~");
			strcat(msg, type);

			notify::above_map(msg);

			return true;
		}

		if (false)
		{
			LOG(INFO) << "Received Script Event";
			LOG(INFO) << "Player: " << player->get_name();
			LOG(INFO) << "Hash: " << (int64_t)hash;

			for (int i = 1; i < sizeof(args); i++)
				LOG(INFO) << "Arg #" << i << ": " << args[i];
		}

		return g_hooking->m_scripted_game_event_hook.get_original<decltype(&hooks::scripted_game_event)>()(scripted_game_event, player);
	}
}