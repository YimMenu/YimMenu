#include "views/view.hpp"

namespace big
{
	void view::settings()
	{
		components::sub_title("SETTINGS_MISC"_T);
		ImGui::Checkbox("SETTINGS_MISC_DEV_DLC"_T.data(), &g.settings.dev_dlc);
	}
}