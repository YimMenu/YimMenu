#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/ped.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "core/data/animations.hpp"

namespace big
{
	void view::animation()
	{
		static bool flag_repeat = false;
		static bool flag_stop_last_frame = false;
		static bool flag_upperbody = false;
		static bool flag_enable_player_control = false;
		static bool flag_cancelable = false;

		components::sub_title("Animation List");

		if (ImGui::Button("Stop Animation", { 500,0 }))
		{
			g_fiber_pool->queue_job([] {TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped); });
		}

		static char search[256];
		ImGui::SetNextItemWidth(500);
		components::input_text_with_hint("Animation Name", "Search", search, sizeof(search), ImGuiInputTextFlags_None);

		ImGui::ListBoxHeader("##Animation Box Header", { 500,static_cast<float>(*g_pointers->m_resolution_x * 0.2) });
		{
			std::string lower_search = search;
			std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);
			for (auto& item : animations)
			{
				std::string display_name = item.second;
				std::string lower_display_name = display_name;
				std::transform(lower_display_name.begin(), lower_display_name.end(), lower_display_name.begin(), ::tolower);
				if (lower_display_name.find(lower_search) != std::string::npos)
				{
					components::selectable(std::format("{}##{}: {}", display_name, item.first, item.second), false, [&item] {
						int flag = ANIM_FLAG_NORMAL;
						if (flag_repeat) flag |= ANIM_FLAG_REPEAT;
						if (flag_stop_last_frame) flag |= ANIM_FLAG_STOP_LAST_FRAME;
						if (flag_upperbody) flag |= ANIM_FLAG_UPPERBODY;
						if (flag_enable_player_control) flag |= ANIM_FLAG_ENABLE_PLAYER_CONTROL;
						if (flag_cancelable) flag |= ANIM_FLAG_CANCELABLE;
						ped::play_animation(self::ped, item.first.c_str(), item.second.c_str(), flag);
					});
				}
			}
		}
		ImGui::ListBoxFooter();

		ImGui::Separator();

		components::sub_title("Flag");
		ImGui::Checkbox("Repeat", &flag_repeat);
		ImGui::Checkbox("Stop Last Frame", &flag_stop_last_frame);
		ImGui::Checkbox("Upper Body", &flag_upperbody);
		ImGui::Checkbox("Enable Player Control", &flag_enable_player_control);
		ImGui::Checkbox("Cancelable", &flag_cancelable);
	}
}