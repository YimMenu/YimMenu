#include "backend/commands/player/toxic/ceo_kick.hpp"
#include "backend/commands/player/toxic/explode_player.hpp"
#include "backend/commands/player/toxic/force_into_mission.hpp"
#include "backend/commands/player/toxic/give_all_weapons.hpp"
#include "backend/commands/player/toxic/kick_from_interior.hpp"
#include "backend/commands/player/toxic/kick_from_vehicle.hpp"
#include "backend/commands/player/toxic/kill_player.hpp"
#include "backend/commands/player/toxic/ragdoll_player.hpp"
#include "backend/commands/player/toxic/remove_all_weapons.hpp"
#include "backend/commands/player/toxic/send_fake_ban_message.hpp"
#include "backend/commands/player/toxic/send_sext.hpp"
#include "backend/commands/player/toxic/send_to_apartment.hpp"
#include "backend/commands/player/toxic/send_to_interior.hpp"
#include "backend/commands/player/toxic/send_to_island.hpp"
#include "backend/commands/player/toxic/send_to_warehouse.hpp"
#include "backend/commands/player/toxic/set_wanted_level.hpp"
#include "backend/commands/player/toxic/show_transaction_error.hpp"
#include "backend/commands/player/toxic/start_script.hpp"
#include "backend/commands/player/toxic/trigger_ceo_raid.hpp"
#include "backend/commands/player/toxic/turn_into_beast.hpp"
#include "core/data/apartment_names.hpp"
#include "core/data/warehouse_names.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "views/view.hpp"

namespace big
{
	void view::player_toxic()
	{
		if (ImGui::TreeNode("TOXIC"_T.data()))
		{
			components::player_command_button(&cmd::g_kill_player);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_explode_player);

			components::player_command_button(&cmd::g_ceo_kick);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_kick_from_vehicle);

			components::player_command_button(&cmd::g_ragdoll_player);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_kick_from_interior);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_turn_into_beast);

			components::player_command_button(&cmd::g_force_into_mission);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_show_transaction_error);

			components::player_command_button(&cmd::g_trigger_ceo_raid);
			ImGui::SameLine();
			components::button("Trigger MC Raid", [] {
				toxic::start_activity(g_player_service->get_selected(), eActivityType::BikerDefend);
			});
			ImGui::SameLine();
			components::button("Trigger Bunker Raid", [] {
				toxic::start_activity(g_player_service->get_selected(), eActivityType::GunrunningDefend);
			});

			components::player_command_button(&cmd::g_send_sext);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_send_fake_ban_message);

			static int wanted_level;
			ImGui::SliderInt("WANTED_LVL"_T.data(), &wanted_level, 0, 5);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_set_wanted_level, g_player_service->get_selected(), {(uint64_t)wanted_level}, "Set");

			components::small_text("TELEPORTS"_T);

			if (ImGui::BeginCombo("##apartment", apartment_names[g.session.send_to_apartment_idx]))
			{
				for (int i = 1; i < apartment_names.size(); i++)
				{
					if (ImGui::Selectable(apartment_names[i], i == g.session.send_to_apartment_idx))
					{
						g.session.send_to_apartment_idx = i;
					}

					if (i == g.session.send_to_apartment_idx)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			ImGui::SameLine();

			components::player_command_button(&cmd::g_send_to_apartment,
			    g_player_service->get_selected(),
			    {(uint64_t)g.session.send_to_apartment_idx});

			if (ImGui::BeginCombo("##warehouse", warehouse_names[g.session.send_to_warehouse_idx]))
			{
				for (int i = 1; i < warehouse_names.size(); i++)
				{
					if (ImGui::Selectable(warehouse_names[i], i == g.session.send_to_warehouse_idx))
					{
						g.session.send_to_warehouse_idx = i;
					}

					if (i == g.session.send_to_warehouse_idx)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			ImGui::SameLine();

			components::player_command_button(&cmd::g_send_to_warehouse,
			    g_player_service->get_selected(),
			    {(uint64_t)g.session.send_to_warehouse_idx});

			components::button("TP_TO_DARTS"_T, [] {
				toxic::start_activity(g_player_service->get_selected(), eActivityType::Darts);
			});
			ImGui::SameLine();
			components::button("TP_TO_FLIGHT_SCHOOL"_T, [] {
				toxic::start_activity(g_player_service->get_selected(), eActivityType::PilotSchool);
			});
			ImGui::SameLine();
			components::button("TP_TO_MAP_CENTER"_T, [] {
				toxic::start_activity(g_player_service->get_selected(), eActivityType::ArmWresling);
			});

			components::button("TP_TO_SKYDIVE"_T, [] {
				toxic::start_activity(g_player_service->get_selected(), eActivityType::Skydive);
			});
			ImGui::SameLine();
			components::player_command_button(&cmd::g_send_to_island);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_send_to_interior, g_player_service->get_selected(), {81}, "TP To MOC");

			components::player_command_button(&cmd::g_send_to_interior, g_player_service->get_selected(), {123}, "TP To Casino");
			ImGui::SameLine();
			components::player_command_button(&cmd::g_send_to_interior, g_player_service->get_selected(), {124}, "TP To Penthouse");
			ImGui::SameLine();
			components::player_command_button(&cmd::g_send_to_interior, g_player_service->get_selected(), {128}, "TP To Arcade");

			components::player_command_button(&cmd::g_send_to_interior, g_player_service->get_selected(), {146}, "TP To Music Locker");
			ImGui::SameLine();
			components::player_command_button(&cmd::g_send_to_interior, g_player_service->get_selected(), {148}, "TP To Record A Studios");
			ImGui::SameLine();
			components::player_command_button(&cmd::g_send_to_interior, g_player_service->get_selected(), {149}, "TP To Custom Auto Shop");

			components::player_command_button(&cmd::g_send_to_interior, g_player_service->get_selected(), {155}, "TP To Agency");
			ImGui::SameLine();
			components::player_command_button(&cmd::g_send_to_interior, g_player_service->get_selected(), {160}, "TP To Freakshop");
			ImGui::SameLine();
			components::player_command_button(&cmd::g_send_to_interior, g_player_service->get_selected(), {161}, "TP To Multi Floor Garage");
			ImGui::SameLine();

			components::player_command_button(&cmd::g_give_all_weapons);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_remove_all_weapons);

			components::player_command_button(&cmd::g_start_tutorial);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_start_golf);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_start_flight_school);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_start_darts);

			components::player_command_button(&cmd::g_start_badlands);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_start_space_monkey);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_start_wizards_ruin);

			components::player_command_button(&cmd::g_start_qub3d);
			ImGui::SameLine();
			components::player_command_button(&cmd::g_start_camhedz);

			components::small_text("WARP_TIME"_T);

			components::button("PLUS_1_MINUTE"_T, [] {
				toxic::warp_time_forward(g_player_service->get_selected(), 60 * 1000);
			});
			ImGui::SameLine();
			components::button("PLUS_5_MINUTES"_T, [] {
				toxic::warp_time_forward(g_player_service->get_selected(), 5 * 60 * 1000);
			});
			ImGui::SameLine();
			components::button("PLUS_48_MINUTES"_T, [] {
				toxic::warp_time_forward(g_player_service->get_selected(), 48 * 60 * 1000);
			});
			ImGui::SameLine();
			components::button("PLUS_96_MINUTES"_T, [] {
				toxic::warp_time_forward(g_player_service->get_selected(), 96 * 60 * 1000);
			});
			ImGui::SameLine();
			components::button("PLUS_200_MINUTES"_T, [] {
				toxic::warp_time_forward(g_player_service->get_selected(), 200 * 60 * 1000);
			});
			ImGui::SameLine();
			components::button("STOP_TIME"_T, [] {
				toxic::set_time(g_player_service->get_selected(), INT_MAX - 3000);
			});
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("PLAYER_TOXIC_NO_WAY_BACK"_T.data());

			ImGui::Checkbox("KILL_LOOP"_T.data(), &g_player_service->get_selected()->kill_loop);
			ImGui::SameLine();
			ImGui::Checkbox("EXPLOSION_LOOP"_T.data(), &g_player_service->get_selected()->explosion_loop);
			ImGui::SameLine();
			ImGui::Checkbox("FREEZE_LOOP"_T.data(), &g_player_service->get_selected()->freeze_loop);

			ImGui::Checkbox("RAGDOLL_LOOP"_T.data(), &g_player_service->get_selected()->ragdoll_loop);
			ImGui::SameLine();
			ImGui::Checkbox("ROT_CAM_LOOP"_T.data(), &g_player_service->get_selected()->rotate_cam_loop);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("PLAYER_TOXIC_BRING_PLAYER_OUT_GOD"_T.data());

			ImGui::TreePop();
		}
	}
}
