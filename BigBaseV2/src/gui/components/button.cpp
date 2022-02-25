#include "gui/components/components.hpp"
#include "fiber_pool.hpp"

namespace big
{
	bool components::button(const char* text) {
		return ImGui::Button(text);
	}

	void components::button(const char* text, std::function<void()> cb) {
		if (components::button(text)) {
			g_fiber_pool->queue_job(cb);
		}
	}
}