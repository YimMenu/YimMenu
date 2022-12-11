#pragma once
#include "services/players/player_service.hpp"

namespace big
{
	class esp
	{
	public:
		static void draw();
		static void draw_player(const player_ptr& plyr, ImDrawList* const draw_list);
	};
}