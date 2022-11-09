#include "gui/components/components.hpp"
#include "fiber_pool.hpp"

namespace big
{
	bool components::menu_item(const std::string_view text) {
		return ImGui::MenuItem(text.data());
	}

	void components::menu_item(const std::string_view text, std::function<void()> cb) {
		if (components::menu_item(text)) {
			g_fiber_pool->queue_job(cb);
		}
	}
}