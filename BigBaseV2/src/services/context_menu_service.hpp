#pragma once
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{

	struct context_option
	{
		std::string name;
		std::function<void()> command;
	};

	class context_menu_service final
	{
		double distance_to_middle_of_screen(rage::vector2);
	public:
		context_menu_service();
		virtual ~context_menu_service();

		bool enabled = false;
		void get_entity_closest_to_screen_center();

		int current_option = 0;

		Entity handle;
		rage::fwEntity* pointer;

		std::vector<context_option> options = {
			{"EXPLODE", [this] {
				rage::fvector3 pos = this->pointer->m_navigation->m_position;
				FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 1, 1000, 1, 0, 1, 0);
				}},
			{"DELETE", [this] {
				entity::delete_entity(this->handle);
				}}
		};
	};

	enum class ContextEntityType
	{
		PED,
		PLAYER,
		VEHICLE
	};

	inline context_menu_service* g_context_menu_service{};
}
