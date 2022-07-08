#include "views/view.hpp"
#include "pointers.hpp"
#include "services/gui/gui_service.hpp"

namespace big
{
	void view::active_view() {
		if (g_gui_service->get_selected()->func == nullptr) return;

		if (ImGui::Begin("main", nullptr, window_flags))
		{
			components::sub_title(g_gui_service->get_selected()->name);
			g_gui_service->get_selected()->func();
		}
	}
}
