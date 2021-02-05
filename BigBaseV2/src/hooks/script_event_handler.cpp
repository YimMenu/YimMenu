#include "hooking.hpp"
#include "features.hpp"
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

		switch (hash)
		{
		case FreemodePlayerEvents::PlayerJoined:
			if (g_settings.options["join_message"].get<bool>() && args[2] == 1289518925)
			{
				char join_msg[128];
				sprintf(join_msg, "<C>%s</C> is joining...", g_pointers->m_get_player_name((Player)args[1]));

				notify::above_map(join_msg);
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

		return g_hooking->m_script_event_hook.get_original<decltype(&script_event_handler)>()(NetEventStruct, net_game_player);
	}
}