#include "components.hpp"
#include "fiber_pool.hpp"

namespace big
{
	bool components::combo(const std::string_view label, int* current_item, const char* const buf[], int buf_size, std::function<void()> cb) {
		bool value_changed = ImGui::Combo(label.data(), current_item, buf, buf_size);
		if (value_changed)
			if (cb)
				g_fiber_pool->queue_job(cb);
		return value_changed;
	}
}