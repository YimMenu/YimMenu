#include "fiber_pool.hpp"
#include "gui/components/components.hpp"
#include "natives.hpp"

namespace big
{
	void components::input_text_with_hint(const std::string_view label, const std::string_view hint, char* buf, size_t buf_size, ImGuiInputTextFlags_ flag, std::function<void()> cb)
	{
		if (ImGui::InputTextWithHint(label.data(), hint.data(), buf, buf_size, flag))
			if (cb)
				g_fiber_pool->queue_job(std::move(cb));

		if (ImGui::IsItemActive())
			g_fiber_pool->queue_job([] {
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			});
	}
}