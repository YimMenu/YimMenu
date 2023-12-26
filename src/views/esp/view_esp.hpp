#pragma once
#include "services/players/player_service.hpp"
#include "entities/CDynamicEntity.hpp"

namespace big
{
	class esp
	{
	public:
		static void draw();
		static void draw_player(const player_ptr& plyr, ImDrawList* const draw_list);
		static void draw_object(const rage::CDynamicEntity* object, ImDrawList* const draw_list, std::string name);
	};
}