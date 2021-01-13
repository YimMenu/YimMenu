#include "tab_bar.hpp"

namespace big
{
	static const double min = 1, max = 5;

	void tabbar::render_weapons()
	{
		if (ImGui::BeginTabItem("Weapons"))
		{
			if (ImGui::TreeNode("Gravity Gun"))
			{
				if (ImGui::Checkbox("Gravity Gun", g_settings.options["gravity_gun"]["enabled"].get<bool*>()))
					g_settings.save();

				if (ImGui::SliderScalar("Multiplier", ImGuiDataType_Double, g_settings.options["gravity_gun"]["multiplier"].get<double*>(), &min, &max))
					g_settings.save();

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}