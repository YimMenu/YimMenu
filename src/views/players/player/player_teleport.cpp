#include "core/data/apartment_names.hpp"
#include "core/data/warehouse_names.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void view::player_teleport()
	{
		ImGui::BeginGroup();

		components::sub_title("Teleport");

		if (ImGui::ListBoxHeader("##teleport", get_listbox_dimensions()))
		{
			components::player_command_button<"playertp">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"playervehtp">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"bring">(g_player_service->get_selected());
			components::button("Waypoint", [] {
				Vector3 location;
				if (blip::get_blip_location(location, (int)BlipIcons::Waypoint))
					entity::load_ground_at_3dcoord(location), teleport::teleport_player_to_coords(g_player_service->get_selected(), location);
			});

			components::options_modal(
			    "Interior Teleport",
			    [] {
				    components::player_command_button<"intkick">(g_player_service->get_selected(), {});
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

				    components::player_command_button<"apartmenttp">(g_player_service->get_selected(),
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

				    components::player_command_button<"warehousetp">(g_player_service->get_selected(),
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
				    components::player_command_button<"interiortp">(g_player_service->get_selected(), {81}, "TP To MOC");

				    components::player_command_button<"interiortp">(g_player_service->get_selected(), {123}, "TP To Casino");
				    ImGui::SameLine();
				    components::player_command_button<"interiortp">(g_player_service->get_selected(), {124}, "TP To Penthouse");
				    ImGui::SameLine();
				    components::player_command_button<"interiortp">(g_player_service->get_selected(), {128}, "TP To Arcade");

				    components::player_command_button<"interiortp">(g_player_service->get_selected(), {146}, "TP To Music Locker");
				    ImGui::SameLine();
				    components::player_command_button<"interiortp">(g_player_service->get_selected(), {148}, "TP To Record A Studios");
				    ImGui::SameLine();
				    components::player_command_button<"interiortp">(g_player_service->get_selected(), {149}, "TP To Custom Auto Shop");

				    components::player_command_button<"interiortp">(g_player_service->get_selected(), {155}, "TP To Agency");
				    ImGui::SameLine();
				    components::player_command_button<"interiortp">(g_player_service->get_selected(), {160}, "TP To Freakshop");
				    ImGui::SameLine();
				    components::player_command_button<"interiortp">(g_player_service->get_selected(), {161}, "TP To Multi Floor Garage");
			    },
			    false,
			    "Interior");

			static float new_location[3];
			static float current_location[3] = {
			    g_player_service->get_selected()->get_ped()->m_navigation->get_position()->x,
			    g_player_service->get_selected()->get_ped()->m_navigation->get_position()->y,
			    g_player_service->get_selected()->get_ped()->m_navigation->get_position()->z};

			components::small_text("Custom TP");
			ImGui::SetNextItemWidth(400);
			ImGui::InputFloat3("##customlocation", new_location);
			components::button("TP", [] {
				teleport::teleport_player_to_coords(g_player_service->get_selected(), {new_location[0], new_location[1], new_location[2]});
			});
			ImGui::SameLine();
			if (ImGui::Button("Get current"))
			{
				std::copy(std::begin(current_location), std::end(current_location), std::begin(new_location));
			}

			ImGui::ListBoxFooter();
		}
		ImGui::EndGroup();
	}
}
