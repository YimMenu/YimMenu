#pragma once
#include "gta/enums.hpp"
#include "natives.hpp"
#include "network/CNetGamePlayer.hpp"
#include "network/ChatData.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/players/player_service.hpp"
#include "fiber_pool.hpp"
#include "hooking/hooking.hpp"
#include "chat.hpp"

#include <script/HudColor.hpp>

namespace big::notify
{
	void above_map(std::string_view text);

	void crash_blocked(CNetGamePlayer* player, const char* crash);

	// Shows a busy spinner till the value at the address equals the value passed or if timeout is hit
	void busy_spinner(std::string_view text, int* address, int value, int timeout = 15);

	void show_subtitle(std::string_view text, int ms = 2000);

	void display_help_text(std::string_view text);

	void player_joined(CNetGamePlayer* net_game_player);
}
