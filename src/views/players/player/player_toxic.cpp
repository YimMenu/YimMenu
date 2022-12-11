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
			components::button("Kill Player", []
			{
				toxic::kill_player(g_player_service->get_selected(), g_player_service->get_self());
			});

			components::button("CEO Kick", [] { toxic::ceo_kick(g_player_service->get_selected()); });
			ImGui::SameLine();
			components::button("CEO Ban", [] { toxic::ceo_ban(g_player_service->get_selected()); });

			components::button("Kick From Vehicle", [] { toxic::kick_player_from_vehicle(g_player_service->get_selected()); });
			ImGui::SameLine();
			components::button("Ragdoll Player", [] { toxic::ragdoll_player(g_player_service->get_selected()); });

			components::button("Kick From Interior", [] { toxic::kick_player_from_interior(g_player_service->get_selected()); });
			components::button("Turn Into Animal", [] { toxic::turn_player_into_animal(g_player_service->get_selected()); });
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Turns player into a random animal");
			ImGui::SameLine();
			components::button("Turn Into Beast", [] { toxic::turn_player_into_beast(g_player_service->get_selected()); });

			static int wanted_level;
			ImGui::SliderInt("Wanted Level", &wanted_level, 0, 5);
			ImGui::SameLine();
			components::button("Set", [] { toxic::set_wanted_level(g_player_service->get_selected(), wanted_level); });

			components::small_text("Teleports");

			if (ImGui::BeginCombo("##apartment", apartment_names[g->session.send_to_apartment_idx]))
			{
				for (int i = 1; i < apartment_names.size(); i++)
				{
					if (ImGui::Selectable(apartment_names[i], i == g->session.send_to_apartment_idx))
					{
						g->session.send_to_apartment_idx = i;
					}

					if (i == g->session.send_to_apartment_idx)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			ImGui::SameLine();

			components::button("TP To Apartment", [] { toxic::send_player_to_apartment(g_player_service->get_selected(), g->session.send_to_apartment_idx); });

			if (ImGui::BeginCombo("##warehouse", warehouse_names[g->session.send_to_warehouse_idx]))
			{
				for (int i = 1; i < warehouse_names.size(); i++)
				{
					if (ImGui::Selectable(warehouse_names[i], i == g->session.send_to_warehouse_idx))
					{
						g->session.send_to_warehouse_idx = i;
					}

					if (i == g->session.send_to_warehouse_idx)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			ImGui::SameLine();

			components::button("TP To Warehouse", [] { toxic::send_player_to_warehouse(g_player_service->get_selected(), g->session.send_to_warehouse_idx); });

			components::button("TP To Darts", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::Darts); });
			ImGui::SameLine();
			components::button("TP To Flight School", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::PilotSchool); });
			ImGui::SameLine();
			components::button("TP To Map Center", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::ArmWresling); });

			components::button("TP To Skydive", [] { toxic::start_activity(g_player_service->get_selected(), eActivityType::Skydive); });
			ImGui::SameLine();
			components::button("TP To Cayo Perico", [] { toxic::send_player_to_island(g_player_service->get_selected()); });
			ImGui::SameLine();
			components::button("TP To MOC", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 81); });

			components::button("TP To Casino", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 123); });
			ImGui::SameLine();
			components::button("TP To Penthouse", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 124); });
			ImGui::SameLine();
			components::button("TP To Arcade", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 128); });

			components::button("TP To Music Locker", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 146); });
			ImGui::SameLine();
			components::button("TP To Record A Studios", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 148); });
			ImGui::SameLine();
			components::button("TP To Custom Auto Shop", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 149); });

			components::button("TP To Agency", [] { toxic::send_player_to_interior(g_player_service->get_selected(), 155); });

			components::button("Give All Weapons", [] { toxic::give_all_weapons(g_player_service->get_selected()); });
			ImGui::SameLine();
			components::button("Remove All Weapons", [] { toxic::remove_all_weapons(g_player_service->get_selected()); });

			ImGui::TreePop();
		}
	}
}