#pragma once
#include "backend/command.hpp"
#include "backend/player_command.hpp"
#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/notifications/notification_service.hpp"
#include "services/ped_animations/ped_animations_service.hpp"
#include "services/vehicle/persist_car_service.hpp"
#include "util/entity.hpp"
#include "util/ped.hpp"
#include "util/teleport.hpp"

#include <imgui.h>

namespace big
{
	struct context_option
	{
		std::string name;
		std::function<void()> command;
	};

	struct s_context_menu
	{
		ContextEntityType type;
		int current_option = 0;
		ImVec2 menu_size   = {};
		std::vector<context_option> options;
	};

	struct model_bounding_box_screen_space
	{
		ImVec2 edge1, edge2, edge3, edge4;
		ImVec2 edge5, edge6, edge7, edge8;
	};

	class context_menu_service final
	{
	private:
		void fill_model_bounding_box_screen_space();
		static double distance_to_middle_of_screen(const rage::fvector2& screen_pos);

	public:
		context_menu_service();
		~context_menu_service();

		context_menu_service(const context_menu_service&)                = delete;
		context_menu_service(context_menu_service&&) noexcept            = delete;
		context_menu_service& operator=(const context_menu_service&)     = delete;
		context_menu_service& operator=(context_menu_service&&) noexcept = delete;

		bool enabled = false;
		s_context_menu* get_context_menu();
		void get_entity_closest_to_screen_center();
		void load_shared();

		static void disable_control_action_loop();
		static void context_menu();

		Entity m_handle;
		rage::fwEntity* m_pointer{};
		model_bounding_box_screen_space m_model_bounding_box_screen_space;

		s_context_menu vehicle_menu{ContextEntityType::VEHICLE,
		    0,
		    {},
		    {{"KILL ENGINE",
		         [this] {
			         if (entity::take_control_of(m_handle))
			         {
				         VEHICLE::SET_VEHICLE_ENGINE_HEALTH(m_handle, 0.f);
				         VEHICLE::SET_VEHICLE_ENGINE_ON(m_handle, false, true, false);
			         }
			         else
				         g_notification_service->push_warning("Toxic", "Failed to take control of vehicle.");
		         }},
		        {"HALT",
		            [this] {
			            if (entity::take_control_of(m_handle))
			            {
				            VEHICLE::BRING_VEHICLE_TO_HALT(m_handle, 1, 5, true);
			            }
			            else
				            g_notification_service->push_warning("Toxic", "Failed to take control of vehicle.");
		            }},
		        {"COPY VEHICLE",
		            [this] {
			            Vehicle v = persist_car_service::clone_ped_car(PLAYER::PLAYER_PED_ID(), m_handle);
			            script::get_current()->yield();
			            PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), v, -1);
		            }},
		        {"TP INTO", [this] {
			         teleport::into_vehicle(m_handle);
		         }}}};

		s_context_menu ped_menu{ContextEntityType::PED,
		    0,
		    {},
		    {{"DISARM",
		         [this] {
			         for (auto& [_, weapon] : g_gta_data_service->weapons())
				         WEAPON::REMOVE_WEAPON_FROM_PED(m_handle, weapon.m_hash);
		         }},
		        {"KILL",
		            [this] {
			            ped::kill_ped(m_handle);
		            }},
		        {"ANIMATION",
		            [this] {
			            if (STREAMING::DOES_ANIM_DICT_EXIST(g_ped_animation_service.current_animation.dict.data()))
				            g_ped_animation_service.play_saved_ped_animation(g_ped_animation_service.current_animation, m_handle);
			            else
				            ped::ped_play_animation(m_handle, "mini@strip_club@private_dance@part1", "priv_dance_p1", 3.5f, -4.0f, -1, 1);
		            }},
		        {"RECRUIT",
		            [this] {
			            auto group_id = PED::GET_PED_GROUP_INDEX(self::ped);
			            if (!PED::IS_PED_GROUP_MEMBER(m_handle, group_id))
			            {
				            TASK::CLEAR_PED_TASKS(m_handle);
				            PED::SET_PED_AS_GROUP_MEMBER(m_handle, group_id);
				            PED::SET_PED_RELATIONSHIP_GROUP_HASH(m_handle, PED::GET_PED_RELATIONSHIP_GROUP_HASH(self::ped));
				            PED::SET_PED_NEVER_LEAVES_GROUP(m_handle, true);
				            PED::SET_CAN_ATTACK_FRIENDLY(m_handle, 0, 1);
				            PED::SET_PED_COMBAT_ABILITY(m_handle, 2);
				            PED::SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(m_handle, group_id, true);
				            PED::SET_PED_FLEE_ATTRIBUTES(m_handle, 512 | 1024 | 2048 | 16384 | 131072 | 262144, true);
			            }
			            else
			            {
				            TASK::CLEAR_PED_TASKS(m_handle);
				            PED::REMOVE_PED_FROM_GROUP(m_handle);
			            }
		            }}


		    }};

		s_context_menu object_menu{ContextEntityType::OBJECT, 0, {}, {}};

		s_context_menu player_menu{ContextEntityType::PLAYER,
		    0,
		    {},
		    {{"SET SELECTED",
		         [this] {
			         g_player_service->set_selected(ped::get_player_from_ped(m_handle));
		         }},
		        {"STEAL OUTFIT", [this] {
			         ped::steal_outfit(m_handle);
		         }}}};

		s_context_menu shared_menu{ContextEntityType::SHARED,
		    0,
		    {},
		    {{"COPY HASH",
		         [this] {
			         ImGui::SetClipboardText(std::format("0x{:08X}", (rage::joaat_t)m_pointer->m_model_info->m_hash).c_str());
			         g_notification_service->push("Context Menu",
			             std::format("Copy hash 0x{:08X}", (rage::joaat_t)m_pointer->m_model_info->m_hash).c_str());
		         }},
		        {"TP TO",
		            [this] {
			            rage::fvector3 pos = *m_pointer->m_navigation->get_position();
			            teleport::to_coords({pos.x, pos.y, pos.z});
		            }},
		        {"Delete", [this] {
			         if (entity::take_control_of(m_handle))
			         {
				         entity::delete_entity(m_handle);
			         }
		         }}}};

		std::unordered_map<ContextEntityType, s_context_menu> options = {{ContextEntityType::VEHICLE, vehicle_menu}, {ContextEntityType::PLAYER, player_menu}, {ContextEntityType::PED, ped_menu}, {ContextEntityType::SHARED, shared_menu}, {ContextEntityType::OBJECT, object_menu}};
	};

	inline context_menu_service* g_context_menu_service{};
}
