#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "core/data/apartment_names.hpp"
#include "core/data/warehouse_names.hpp"

namespace big
{
	void view::player_toxic()
	{
		if (ImGui::TreeNode("Toxic"))
		{
			components::player_command_button<"kill">(g_player_service->get_selected(), {});

			components::player_command_button<"ceokick">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"vehkick">(g_player_service->get_selected(), {});

			components::player_command_button<"ragdoll">(g_player_service->get_selected(), {});

			components::player_command_button<"intkick">(g_player_service->get_selected(), {});
			components::player_command_button<"beast">(g_player_service->get_selected(), {});

			static int wanted_level;
			ImGui::SliderInt("Wanted Level", &wanted_level, 0, 5);
			ImGui::SameLine();
			components::player_command_button<"wanted">(g_player_service->get_selected(), { (uint64_t)wanted_level }, "Set");

			components::small_text("Teleports");

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

			components::player_command_button<"apartmenttp">(g_player_service->get_selected(), { (uint64_t)g.session.send_to_apartment_idx });

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

			components::player_command_button<"warehousetp">(g_player_service->get_selected(), { (uint64_t)g.session.send_to_warehouse_idx });

			components::button("TP To Darts", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::Darts); });
			ImGui::SameLine();
			components::button("TP To Flight School", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::PilotSchool); });
			ImGui::SameLine();
			components::button("TP To Map Center", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::ArmWresling); });

			components::button("TP To Skydive", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::Skydive); });
			ImGui::SameLine();
			components::player_command_button<"cayotp">(g_player_service->get_selected(), { });
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), { 81 }, "TP To MOC");

			components::player_command_button<"interiortp">(g_player_service->get_selected(), { 123 }, "TP To Casino");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), { 124 }, "TP To Penthouse");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), { 128 }, "TP To Arcade");

			components::player_command_button<"interiortp">(g_player_service->get_selected(), { 146 }, "TP To Music Locker");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), { 148 }, "TP To Record A Studios");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), { 149 }, "TP To Custom Auto Shop");

			components::player_command_button<"interiortp">(g_player_service->get_selected(), { 155 }, "TP To Agency");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), { 160 }, "TP To Freakshop");
			ImGui::SameLine();
			components::player_command_button<"interiortp">(g_player_service->get_selected(), { 161 }, "TP To Multi Floor Garage");

			components::player_command_button<"giveweaps">(g_player_service->get_selected(), { });
			ImGui::SameLine();
			components::player_command_button<"remweaps">(g_player_service->get_selected(), { });

			components::small_text("Warp Time (requires session host)");

			components::button("+1 Minute", [] { toxic::warp_time_forward(g_player_service->get_selected(), 60 * 1000); });
			ImGui::SameLine();
			components::button("+5 Minutes", [] { toxic::warp_time_forward(g_player_service->get_selected(), 5 * 60 * 1000); });
			ImGui::SameLine();
			components::button("+48 Minutes", [] { toxic::warp_time_forward(g_player_service->get_selected(), 48 * 60 * 1000); });
			ImGui::SameLine();
			components::button("+96 Minutes", [] { toxic::warp_time_forward(g_player_service->get_selected(), 96 * 60 * 1000); });
			ImGui::SameLine();
			components::button("+200 Minutes", [] { toxic::warp_time_forward(g_player_service->get_selected(), 200 * 60 * 1000); });
			ImGui::SameLine();
			components::button("Stop Time", [] { toxic::set_time(g_player_service->get_selected(), INT_MAX - 3000); });
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("This cannot be reversed. Use with caution");

			ImGui::TreePop();
		}
	}
}