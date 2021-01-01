#include "features.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "natives.hpp"

namespace big
{
	bool hooks::get_event_data(int32_t eventGroup, int32_t eventIndex, int64_t* args, uint32_t argCount)
	{		
		bool result = g_hooking->m_get_event_data.get_original<decltype(&hooks::get_event_data)>()(eventGroup, eventIndex, args, argCount);

		if (result)
		{
			Player player = (Player)args[1];
			auto hash = args[0];

			char type[32] = "";

			switch (hash)
			{
			case RemoteEvents::Bounty:
				strcpy(type, "Bounty");

				break;
			case RemoteEvents::CeoBan:
				strcpy(type, "Ceo Ban");

				break;
			case RemoteEvents::CeoKick:
				strcpy(type, "Ceok Kick");

				break;
			case RemoteEvents::CeoMoney:
				strcpy(type, "Ceo Money");

				break;
			case RemoteEvents::ClearWantedLevel:
				strcpy(type, "Clear Wanted Level");

				break;
			case RemoteEvents::FakeDeposit:
				strcpy(type, "Fake Deposit");

				break;
			case RemoteEvents::ForceMission:
			case RemoteEvents::ForceMission2:
			case RemoteEvents::ForceMission3:
				strcpy(type, "Force Mission");

				break;
			case RemoteEvents::GtaBanner:
				strcpy(type, "GTA Banner");

				break;
			case RemoteEvents::PersonalVehicleDestroyed:
				strcpy(type, "Personal Vehicle Destroyed");

				break;
			case RemoteEvents::RemoteOffradar:
				strcpy(type, "Remote Off Radar");

				break;
			case RemoteEvents::RotateCam:
				strcpy(type, "Rotate Cam");

				break;
			case RemoteEvents::SendToCutscene:
				strcpy(type, "Send To Cutscene");

				break;
			case RemoteEvents::SendToIsland:
				strcpy(type, "Send To Island");

				break;
			case RemoteEvents::SoundSpam:
			case RemoteEvents::SoundSpam2:
				strcpy(type, "Sound Spam");

				break;
			case RemoteEvents::Spectate:
				strcpy(type, "Specate");
				
				break;
			case RemoteEvents::Teleport:
				strcpy(type, "Force Teleport");

				break;
			case RemoteEvents::TransactionError:
				strcpy(type, "Transaction Error");

				break;
			case RemoteEvents::VehicleKick:
				strcpy(type, "Vehicle Kick");

				break;
			}

			for (int64_t kick_hash : kick_hashes)
				if (hash == kick_hash)
					strcpy(type, "General Kick");

			if (strlen(type) != 0)
			{
				char msg[128];
				strcpy(msg, "~g~BLOCKED EVENT~s~\nFrom: <C>");
				strcat(msg, g_pointers->m_get_player_name(player));
				strcat(msg, "</C>\nEvent Type: ~b~");
				strcat(msg, type);

				features::notify::above_map(msg);

				return false;
			}

			const char* sender = g_pointers->m_get_player_name(player);
			LOG(INFO) << "Player: " << sender;
			LOG(INFO) << "Script hash: " << args[0];
			LOG(INFO) << "Script event group: " << eventGroup;
			LOG(INFO) << "Script event index: " << eventIndex;
			LOG(INFO) << "Script event argcount: " << argCount;
			for (std::uint32_t i = 0; i < argCount; i++)
				LOG(INFO) << "Script event args[" << i << "] : " << args[i];
		}

		return result;
	}
}