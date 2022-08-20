#include "views/view.hpp"
#include "pointers.hpp"
#include "services/gui/gui_service.hpp"

namespace big
{
	void view::active_view() {
		if (g_gui_service->get_selected()->func == nullptr) return;

		if (ImGui::Begin("main", nullptr, window_flags))
		{
			components::title(g_gui_service->get_selected()->name);
			ImGui::Separator();
			g_gui_service->get_selected()->func();
		}
	}
}
