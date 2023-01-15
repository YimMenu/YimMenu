#include "views/view.hpp"
#include "util/toxic.hpp"

namespace big
{
#ifdef CUSTOM_BUILD
	void view::player_crash()
	{
		if (ImGui::TreeNode("Crash"))
		{
			components::player_command_button<"netmsgcrash">(g_player_service->get_selected());

			ImGui::TreePop();
		}
	}
#endif // CUSTOM_BUILD
}
