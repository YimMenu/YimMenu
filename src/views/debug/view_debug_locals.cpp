#include "view_debug.hpp"
#include "gui/components/components.hpp"
#include "natives.hpp"

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