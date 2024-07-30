#include "services/custom_teleport/custom_teleport_service.hpp"
#include "util/math.hpp"
#include "util/teleport.hpp"
#include "util/blip.hpp"
#include "views/view.hpp"

namespace big
{
	telelocation get_location_player_is_closest_to()
	{
		if (!g_local_player || !g_local_player->m_navigation || g_custom_teleport_service.all_saved_locations.empty())
			return {};

		Vector3 transformed_vector = Vector3(g_local_player->m_navigation->get_position()->x,
		    g_local_player->m_navigation->get_position()->y,
		    g_local_player->m_navigation->get_position()->z);

		float distance = 500;
		telelocation closest_location{};
		//saved_locations_filtered_list can be used to get a joint list of all categories when the filter is empty.
		for (auto& loc : g_custom_teleport_service.saved_locations_filtered_list())
		{
			float new_distance = math::distance_between_vectors(transformed_vector, {loc.x, loc.y, loc.z});

			if (new_distance < distance)
				closest_location = loc, distance = new_distance;
		}

		return closest_location;
	}

	float get_distance_to_telelocation(telelocation t)
	{
		return math::distance_between_vectors(Vector3(t.x,t.y,t.z), Vector3(g_local_player->m_navigation->get_position()->x,
		    g_local_player->m_navigation->get_position()->y,
		    g_local_player->m_navigation->get_position()->z));
	}

	void view::custom_teleport()
	{
		ImGui::BeginGroup();
		static std::string new_location_name{};
		static std::string category = "Default";
		static telelocation deletion_telelocation;
		static std::string filter{};

		if (!std::string(deletion_telelocation.name).empty())
			ImGui::OpenPopup("##deletelocation");

		if (ImGui::BeginPopupModal("##deletelocation", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text("VIEW_SELF_ANIMATIONS_ARE_YOU_SURE_DELETE"_T.data(), deletion_telelocation.name);

			ImGui::Spacing();

			if (ImGui::Button("YES"_T.data()))
			{
				g_custom_teleport_service.delete_saved_location(category, deletion_telelocation.name);
				deletion_telelocation.name = "";
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("NO"_T.data()))
			{
				deletion_telelocation.name = "";
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::PushItemWidth(300);
		components::input_text_with_hint("VIEW_SELF_ANIMATIONS_CATEGORY"_T, "VIEW_SELF_ANIMATIONS_CATEGORY_DESC"_T, category);
		components::input_text_with_hint("VIEW_SELF_CUSTOM_TELEPORT_LOCATION"_T, "VIEW_SELF_CUSTOM_TELEPORT_LOCATION_DESC"_T, new_location_name);
		ImGui::PopItemWidth();

		components::button("VIEW_SELF_CUSTOM_TELEPORT_SAVE_CURRENT_LOCATION"_T, [] {
			if (new_location_name.empty())
			{
				g_notification_service.push_warning("GUI_TAB_CUSTOM_TELEPORT"_T.data(), "VIEW_SELF_CUSTOM_TELEPORT_INVALID_NAME"_T.data());
			}
			else if (g_custom_teleport_service.get_saved_location_by_name(new_location_name))
			{
				g_notification_service.push_warning("GUI_TAB_CUSTOM_TELEPORT"_T.data(), std::vformat("VIEW_SELF_CUSTOM_TELEPORT_LOCATION_ALREADY_EXISTS"_T, std::make_format_args(new_location_name)));
			}
			else
			{
				telelocation teleport_location;
				Entity teleport_entity = self::ped;
				if (self::veh != 0)
					teleport_entity = self::veh;
				auto coords                  = ENTITY::GET_ENTITY_COORDS(teleport_entity, TRUE);
				teleport_location.name       = new_location_name;
				teleport_location.x          = coords.x;
				teleport_location.y          = coords.y;
				teleport_location.z          = coords.z;
				teleport_location.yaw        = ENTITY::GET_ENTITY_HEADING(teleport_entity);
				teleport_location.pitch      = CAM::GET_GAMEPLAY_CAM_RELATIVE_PITCH();
				teleport_location.roll       = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();
				g_custom_teleport_service.save_new_location(category, teleport_location);
			}
		});
		ImGui::SameLine();
		components::button("VIEW_SELF_CUSTOM_TELEPORT_SAVE_BLIP"_T, [] {
			if (new_location_name.empty())
			{
				g_notification_service.push_warning("GUI_TAB_CUSTOM_TELEPORT"_T.data(), "VIEW_SELF_CUSTOM_TELEPORT_INVALID_NAME"_T.data());
			}
			else if (g_custom_teleport_service.get_saved_location_by_name(new_location_name))
			{
				g_notification_service.push_warning("GUI_TAB_CUSTOM_TELEPORT"_T.data(), std::vformat("VIEW_SELF_CUSTOM_TELEPORT_LOCATION_ALREADY_EXISTS"_T, std::make_format_args(new_location_name)));
			}
			else if (!*g_pointers->m_gta.m_is_session_started)
			{
				g_notification_service.push_warning("GUI_TAB_CUSTOM_TELEPORT"_T.data(), "TELEPORT_NOT_ONLINE"_T.data());
				return;
			}
			else
			{
				telelocation teleport_location;
				auto blip = blip::get_selected_blip();
				if (blip == nullptr)
				{
					g_notification_service.push_warning("GUI_TAB_CUSTOM_TELEPORT"_T.data(), "VIEW_SELF_CUSTOM_TELEPORT_INVALID_BLIP"_T.data());
					return;
				}
				teleport_location.name  = new_location_name;
				teleport_location.x     = blip->m_position.x;
				teleport_location.y     = blip->m_position.y;
				teleport_location.z     = blip->m_position.z;
				teleport_location.yaw   = blip->m_rotation;
				teleport_location.pitch = 0.0f;
				teleport_location.roll  = 0.0f;
				g_custom_teleport_service.save_new_location(category, teleport_location);
			}
		});

		ImGui::Separator();

		components::small_text("VIEW_SELF_CUSTOM_TELEPORT_DOUBLE_CLICK_TO_TELEPORT"_T);
		components::small_text("VIEW_SELF_ANIMATIONS_DOUBLE_SHIFT_CLICK_TO_DELETE"_T);

		ImGui::Spacing();
		components::input_text_with_hint("##filter", "SEARCH"_T, filter);

		ImGui::BeginGroup();
		components::small_text("VIEW_SELF_ANIMATIONS_CATEGORIES"_T);
		if (ImGui::BeginListBox("##categories", {250, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.5)}))
		{
			for (auto& l : g_custom_teleport_service.all_saved_locations | std::ranges::views::keys)
			{
				if (ImGui::Selectable(l.data(), l == category))
				{
					category = l;
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		components::small_text("VIEW_SELF_CUSTOM_TELEPORT_LOCATIONS"_T);
		if (ImGui::BeginListBox("##telelocations", {250, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.5)}))
		{
			if (g_custom_teleport_service.all_saved_locations.find(category)
			    != g_custom_teleport_service.all_saved_locations.end())
			{
				std::vector<telelocation> current_list{};

				if (!filter.empty())
					current_list = g_custom_teleport_service.saved_locations_filtered_list(filter);
				else
					current_list = g_custom_teleport_service.all_saved_locations.at(category);

				for (const auto& l : current_list)
				{
					if (ImGui::Selectable(l.name.data(), l.name == get_location_player_is_closest_to().name, ImGuiSelectableFlags_AllowDoubleClick))
					{
						if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
						{
							deletion_telelocation = l;
						}
						else
						{
							if (ImGui::IsMouseDoubleClicked(0))
							{
								g_fiber_pool->queue_job([l] {
									teleport::teleport_player_to_coords(g_player_service->get_self(), {l.x, l.y, l.z}, {l.yaw, l.pitch, l.roll});
								});
							}
						}
					}
					if (ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						if (l.name.length() > 27)
							ImGui::Text(l.name.data());
						ImGui::Text(std::format("{}: {}", "VIEW_SELF_CUSTOM_TELEPORT_DISTANCE"_T, get_distance_to_telelocation(l)).c_str());
						ImGui::EndTooltip();
					}
				}
			}

			ImGui::EndListBox();
		}

		ImGui::EndGroup();

		ImGui::EndGroup();
	}
}
