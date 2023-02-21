#include "view_debug.hpp"

namespace big
{
	void debug::locals()
	{
		if (ImGui::BeginTabItem("DEBUG_TAB_LOCALS"_T.data()))
		{
			ImGui::EndTabItem();
		}
	}
}