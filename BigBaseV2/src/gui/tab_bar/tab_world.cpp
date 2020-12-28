#include "tab_bar.hpp"

namespace big
{
	static int clock[3];

	void tabbar::render_world()
	{
		if (ImGui::BeginTabItem("World"))
		{
			ImGui::Text("Set Local Time");
			if (ImGui::InputInt3(": H:M:s", clock))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					CLOCK::SET_CLOCK_TIME(clock[0], clock[1], clock[3]);
				}QUEUE_JOB_END_CLAUSE
			}

			//ImGui::Text("Set Weather:");
			//MISC::SET_OVERRIDE_WEATHER();

			ImGui::EndTabItem();
		}
	}
}