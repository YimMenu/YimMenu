#include "gui.hpp"
#include "services/context_menu/context_menu_service.hpp"
#include "view.hpp"

namespace big
{
	static void draw_model_bounding_box(ImDrawList* draw_list, const model_bounding_box_screen_space& m_model_bounding_box_screen_space)
	{
		const auto& box   = g_context_menu_service->m_model_bounding_box_screen_space;
		const auto& color = g.context_menu.bounding_box_color;

		draw_list->AddLine(box.edge1, box.edge2, color);
		draw_list->AddLine(box.edge1, box.edge4, color);
		draw_list->AddLine(box.edge2, box.edge3, color);
		draw_list->AddLine(box.edge3, box.edge4, color);

		draw_list->AddLine(box.edge5, box.edge6, color);
		draw_list->AddLine(box.edge5, box.edge8, color);
		draw_list->AddLine(box.edge6, box.edge7, color);
		draw_list->AddLine(box.edge7, box.edge8, color);

		draw_list->AddLine(box.edge1, box.edge7, color);
		draw_list->AddLine(box.edge2, box.edge8, color);
		draw_list->AddLine(box.edge3, box.edge5, color);
		draw_list->AddLine(box.edge4, box.edge6, color);
	}

	void view::context_menu()
	{
		if (const auto draw_list = ImGui::GetBackgroundDrawList(); draw_list && !g_gui->is_open())
		{
			if (g_context_menu_service->enabled && g_context_menu_service->m_pointer
			    && g_context_menu_service->m_pointer->m_navigation)
			{
				float context_screen_x;
				float context_screen_y;

				auto& context_target_pos = *g_context_menu_service->m_pointer->m_navigation->get_position();

				const auto context_target_distance = math::calculate_distance_from_game_cam(context_target_pos);
				const auto context_target_multplr = context_target_distance > g.esp.global_render_distance[1] ? -1.f : 6.17757f / context_target_distance;

				if (g_pointers->m_gta.m_get_screen_coords_for_world_coords(context_target_pos.data, &context_screen_x, &context_screen_y))
				{
					const auto cm = g_context_menu_service->get_context_menu();
					if (cm == nullptr)
						return;

					const auto cm_start_x = static_cast<float>(*g_pointers->m_gta.m_resolution_x) * context_screen_x + (67.5f * context_target_multplr);
					const auto cm_start_y = static_cast<float>(*g_pointers->m_gta.m_resolution_y) * context_screen_y - (175.f * context_target_multplr);

					const auto cm_col = ImGui::ColorConvertFloat4ToU32({0.549f, 0.639f, 0.710f, 0.3f});

					draw_list->AddRectFilled({cm_start_x - 2.f, cm_start_y},
					    {cm_start_x + 2.f + cm->menu_size.x, cm_start_y + cm->menu_size.y},
					    cm_col,
					    5.f);

					for (uint32_t i = 0; i < cm->options.size(); i++)
					{
						const auto co = cm->options.at(i);
						draw_list->AddText({cm_start_x + 7.f, cm_start_y + (20.f * static_cast<float>(i)) + 5.f},
						    cm->current_option == i ? g.context_menu.selected_option_color : ImGui::ColorConvertFloat4ToU32({1.f, 1.f, 1.f, 1.f}),
						    co.name.c_str());
					}

					if (g.context_menu.bounding_box_enabled)
						draw_model_bounding_box(draw_list, g_context_menu_service->m_model_bounding_box_screen_space);
				}
			}
		}
	}
}
