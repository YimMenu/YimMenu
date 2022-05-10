#pragma once
#include "natives.hpp"
#include "util/entity.hpp"
#include "util/ped.hpp"
#include "util/teleport.hpp"

namespace big
{
	enum class ContextEntityType
	{
		PED,
		PLAYER,
		VEHICLE,
		OBJECT,
		SHARED
	};

	struct context_option
	{
		std::string name;
		std::function<void()> command;
	};

	struct s_context_menu
	{
		ContextEntityType type;
		int current_option = 0;
		ImVec2 menu_size = {};
		std::vector<context_option> options;
	};

	class context_menu_service final
	{
		double distance_to_middle_of_screen(rage::vector2);
	public:
		context_menu_service();
		virtual ~context_menu_service();

		bool enabled = false;
		void get_entity_closest_to_screen_center();
		void load_shared();
		s_context_menu* get_context_menu();

		Entity handle;
		rage::fwEntity* pointer;

		s_context_menu vehicle_menu{
			ContextEntityType::VEHICLE,
			0,{}, {
			{"KILL ENGINE", [this] {
					VEHICLE::SET_VEHICLE_ENGINE_HEALTH(this->handle, 0.f);
					VEHICLE::SET_VEHICLE_ENGINE_ON(this->handle, false, true, false);
				}},
			{"DELETE", [this] {
					entity::delete_entity(this->handle);
				}},
			{ "TP INTO", [this]{
				teleport::into_vehicle(this->handle);
				}}

		} };

		s_context_menu ped_menu{
			ContextEntityType::PED,
			0,{}, {}};

		s_context_menu player_menu{
			ContextEntityType::PLAYER,
			0,{}, {
				{"STEAL IDENTITY", [this]
				{
					ped::steal_identity(this->handle);
				}}
			} };

		s_context_menu shared_menu{
			ContextEntityType::SHARED,
			0,
			{}, {
				{"EXPLODE", [this] {
					rage::fvector3 pos = this->pointer->m_navigation->m_position;
					FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 1, 1000, 1, 0, 1, 0);
					}},
			}
		};

		std::unordered_map<ContextEntityType, s_context_menu> options = {
			{ContextEntityType::VEHICLE, vehicle_menu},
			{ContextEntityType::PLAYER, player_menu},
			{ContextEntityType::PED, ped_menu},
			{ContextEntityType::SHARED, shared_menu},
		};

		
	};

	inline context_menu_service* g_context_menu_service{};
}
