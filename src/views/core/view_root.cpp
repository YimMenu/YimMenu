#include "views/view.hpp"
#include "core/settings.hpp"

namespace big
{
	void view::root()
	{
		view::heading();
		view::navigation();
		view::players();
		view::active_view();

		if (g.window.demo) // It is not the YimMenu way.
			ImGui::ShowDemoWindow(&g.window.demo);
	}
}
