#include "fiber_pool.hpp"
#include "gui/components/components.hpp"
#include "natives.hpp"

namespace big
{
	void components::input_text(const std::string_view label, char* buf, size_t buf_size, ImGuiInputTextFlags_ flag, std::function<void()> cb)
	{
		if (ImGui::InputText(label.data(), buf, buf_size, flag))
			if (cb)
				g_fiber_pool->queue_job(std::move(cb));

		if (ImGui::IsItemActive())
			g_fiber_pool->queue_job([] {
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			});
	}
}