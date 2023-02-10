#include "gui/components/components.hpp"
#include "fiber_pool.hpp"

namespace big
{
	bool components::button(const std::string_view text, const ImVec2& size_arg, const ImVec4& color_args) {
		bool status = false;
		ImGui::PushStyleColor(ImGuiCol_Button, color_args);
		if (ImGui::Button(text.data(), size_arg))
			status = true;
		else
			status = false;
		ImGui::PopStyleColor(1);
		return status;
	}

	void components::button(const std::string_view text, std::function<void()> cb, const ImVec2& size_arg, const ImVec4& color_args) {
		if (components::button(text, size_arg, color_args)) {
			g_fiber_pool->queue_job(cb);
		}
	}
}