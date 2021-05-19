#include "tabs.hpp"
#include "imgui.h"

namespace big
{
	void tab_main::tab_self()
	{
		if (ImGui::BeginTabItem("Self"))
		{
			ImGui::Text("Yeet");
			//ImGui::Checkbox("No Clip", nullptr);

			ImGui::EndTabItem();
		}
	}
}