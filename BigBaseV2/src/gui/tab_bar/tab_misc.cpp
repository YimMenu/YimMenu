#include "tab_bar.hpp"

namespace big
{
	void tabbar::render_misc()
	{
		if (ImGui::BeginTabItem("Misc"))
		{
			if (ImGui::Checkbox("Player Join Message", g_settings.options["join_message"].get<bool*>()))
				g_settings.save();

			ImGui::Separator();

			if (ImGui::Button("Unlock Achievements"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					features::stats::unlock_achievements();
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Unlock All Stats"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					features::stats::unlock_all();
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}