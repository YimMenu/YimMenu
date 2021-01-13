#include "hooking.hpp"
#include "features.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "gta/enums.hpp"

namespace big
{
	bool hooks::script_event_handler(std::int64_t NetEventStruct, std::int64_t CNetGamePlayer)
	{
		auto args = reinterpret_cast<std::int64_t*>(NetEventStruct + 0x70);
		Player player = *reinterpret_cast<std::int8_t*>(CNetGamePlayer + 0x2D);

		int64_t hash = args[0];

		switch (hash)
		{
		case FreemodePlayerEvents::PlayerJoined:
			if (g_settings.options["join_message"].get<bool>() && args[2] == 1289518925)
			{
				char join_msg[128];
				sprintf(join_msg, "<C>%s</C> is joining...", g_pointers->m_get_player_name((Player)args[1]));

				features::notify::above_map(join_msg);
			}
		}

		if (g_settings.options["settings"]["logging"]["script_events"])
		{
			LOG(INFO) << "Received Script Event";
			LOG(INFO) << "Player: " << PLAYER::GET_PLAYER_NAME(player);
			LOG(INFO) << "Hash: " << hash;

			for (int i = 1; i < sizeof(args); i++)
				LOG(INFO) << "Arg #" << i << ": " << args[i];
		}

		return g_hooking->m_script_event_hook.get_original<decltype(&script_event_handler)>()(NetEventStruct, CNetGamePlayer);
	}
}