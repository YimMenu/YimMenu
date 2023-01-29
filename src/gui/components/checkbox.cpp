#include "components.hpp"
#include "fiber_pool.hpp"

namespace big
{
	bool components::checkbox(const std::string_view label, bool* v, std::function<void()> cb) {
		bool pressed = ImGui::Checkbox(label.data(), v);
		if (pressed)
			if (cb)
				g_fiber_pool->queue_job(cb);
		return pressed;
	}
}