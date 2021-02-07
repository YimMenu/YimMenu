#include "features.hpp"
#include "features/notify.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "natives.hpp"

namespace big
{
	bool hooks::get_event_data(int32_t eventGroup, int32_t eventIndex, int64_t* args, uint32_t argCount)
	{		
		bool result = g_hooking->m_get_event_data_hook.get_original<decltype(&hooks::get_event_data)>()(eventGroup, eventIndex, args, argCount);
		Player player = (Player)args[1];

		if (result && player < 32)
		{
			auto hash = args[0];
			auto &protections = g_settings.options["settings"]["script_protections"];

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
			case RemoteEvents::RotateCam:
				if (protections["rotate_cam"])
				{
					//strcpy(type, "Rotate Cam");
					return false;
				}

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
				if (hash == 1317868303 || hash == 495824472) return false;

				for (int64_t kick_hash : kick_hashes)
				{
					if (hash == kick_hash)
					{
						sprintf(type, "General Kick (%" PRId64 ")", hash);

						break;
					}
				}
			}

			if (strlen(type) != 0)
			{
				char msg[128];
				strcpy(msg, "~g~BLOCKED EVENT~s~\nFrom: <C>");
				strcat(msg, g_pointers->m_get_player_name(player));
				strcat(msg, "</C>\nEvent Type: ~b~");
				strcat(msg, type);

				notify::above_map(msg);

				return false;
			}

			if (g_settings.options["settings"]["logging"]["get_event_data"])
			{
				const char* sender = g_pointers->m_get_player_name(player);
				LOG(INFO) << "Player: " << sender;
				LOG(INFO) << "Script hash: " << args[0];
				LOG(INFO) << "Script event group: " << eventGroup;
				LOG(INFO) << "Script event index: " << eventIndex;
				LOG(INFO) << "Script event argcount: " << argCount;
				for (std::uint32_t i = 0; i < argCount; i++)
					LOG(INFO) << "Script event args[" << i << "] : " << args[i];
			}
		}

		return result;
	}
}