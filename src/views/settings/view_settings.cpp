#include "views/view.hpp"

namespace big
{
	void view::settings()
	{
		ImGui::SeparatorText("SETTINGS_MISC"_T.data());
		ImGui::Checkbox("SETTINGS_MISC_DEV_DLC"_T.data(), &g.settings.dev_dlc);

		if (ImGui::Button("Reset Settings"))
		{
			g.write_default_config();
			g.load();
		}
	}
}