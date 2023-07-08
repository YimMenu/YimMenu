#include "util/teleport.hpp"
#include "services/custom_teleport/custom_teleport_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::custom_teleport()
	{
		ImGui::BeginGroup();
		static std::string new_location_name;
		static std::string category = "Default";
		static telelocation deletion_telelocation;
		static std::string filter{};

		if (!std::string(deletion_telelocation.name).empty())
			ImGui::OpenPopup("##deletelocation");

		if (ImGui::BeginPopupModal("##deletelocation"))
		{
			ImGui::Text("Are you sure you want to delete %s?", deletion_telelocation.name);

			if (ImGui::Button("Yes"))
			{
				g_custom_teleport_service.delete_saved_location(category, deletion_telelocation.name);
				deletion_telelocation.name = "";
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("No"))
			{
				deletion_telelocation.name = "";
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::PushItemWidth(300);
		components::input_text_with_hint("Category", "Category", &category);
		components::input_text_with_hint("Location name", "New location", &new_location_name);
		ImGui::PopItemWidth();

		components::button("Save current location", [] {
			g_custom_teleport_service.save_new_location(category, {new_location_name, self::pos.x, self::pos.y, self::pos.z});
		});

		ImGui::Separator();

		components::input_text_with_hint("##filter", "Search", &filter);

		ImGui::BeginGroup();
		components::small_text("Categories");
		if (ImGui::BeginListBox("##categories", {250, static_cast<float>(*g_pointers->m_gta.m_resolution_y - 188 - 38 * 4)}))
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
		components::small_text("Locations");
		if (ImGui::BeginListBox("##telelocations", {250, static_cast<float>(*g_pointers->m_gta.m_resolution_y - 188 - 38 * 4)}))
		{
			if (g_custom_teleport_service.all_saved_locations.find(category) != g_custom_teleport_service.all_saved_locations.end())
			{
				std::vector<telelocation> current_list{};

				if(!filter.empty())
					current_list = g_custom_teleport_service.saved_locations_filtered_list(filter);
				else
					current_list = g_custom_teleport_service.all_saved_locations.at(category);

				for (const auto& l : current_list)
				{
					if (ImGui::Selectable(l.name.data()))
					{
						if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
						{
							deletion_telelocation = l;
						}
						else
							g_fiber_pool->queue_job([l] {
								teleport::teleport_player_to_coords(g_player_service->get_self(), {l.x, l.y, l.z});
							});
					}
				}
			}

			ImGui::EndListBox();
		}

		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Shift click to delete");

		ImGui::EndGroup();

		ImGui::EndGroup();
	}
}
