#include "view_debug.hpp"

namespace big
{
	void debug::locals()
	{
		if (ImGui::BeginTabItem("Locals"))
		{

			ImGui::EndTabItem();
		}
	}
}