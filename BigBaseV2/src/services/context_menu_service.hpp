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
	private:
		static double distance_to_middle_of_screen(const rage::vector2& screen_pos);

	public:
		context_menu_service();
		~context_menu_service();

		context_menu_service(const context_menu_service&) = delete;
		context_menu_service(context_menu_service&&) noexcept = delete;
		context_menu_service& operator=(const context_menu_service&) = delete;
		context_menu_service& operator=(context_menu_service&&) noexcept = delete;

		bool enabled = false;
		s_context_menu* get_context_menu();
		void get_entity_closest_to_screen_center();
		void load_shared();

		static void context_menu();

		Entity m_handle;
		rage::fwEntity* m_pointer;

		s_context_menu vehicle_menu{
			ContextEntityType::VEHICLE,
			0,{}, {
			{"KILL ENGINE", [this] {
					if (entity::take_control_of(m_handle))
					{
						VEHICLE::SET_VEHICLE_ENGINE_HEALTH(m_handle, 0.f);
						VEHICLE::SET_VEHICLE_ENGINE_ON(m_handle, false, true, false);
					}
				}},
			{"DELETE", [this] {
					if (entity::take_control_of(m_handle))
					{
						entity::delete_entity(m_handle);
					}
				}},
			{ "TP INTO", [this] {
				teleport::into_vehicle(m_handle);
				}}
		} };

		s_context_menu ped_menu{
			ContextEntityType::PED,
			0,{}, {}};

		s_context_menu object_menu{
			ContextEntityType::OBJECT,
			0,{}, {}};

		s_context_menu player_menu{
			ContextEntityType::PLAYER,
			0,{}, {
				{"STEAL IDENTITY", [this]
				{
					ped::steal_identity(m_handle);
				}}
			} };

		s_context_menu shared_menu{
			ContextEntityType::SHARED,
			0,
			{}, {
				{"EXPLODE", [this] {
					rage::fvector3 pos = m_pointer->m_navigation->m_position;
					FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 1, 1000, 1, 0, 1, 0);
					}},
				{"TP TO", [this] {
					rage::fvector3 pos = m_pointer->m_navigation->m_position;
					teleport::to_coords({ pos.x, pos.y, pos.z });
					}},
			}
		};

		std::unordered_map<ContextEntityType, s_context_menu> options = {
			{ContextEntityType::VEHICLE, vehicle_menu},
			{ContextEntityType::PLAYER, player_menu},
			{ContextEntityType::PED, ped_menu},
			{ContextEntityType::SHARED, shared_menu},
			{ContextEntityType::OBJECT, object_menu}
		};
	};

	inline context_menu_service* g_context_menu_service{};
}
