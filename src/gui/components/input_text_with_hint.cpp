#include "fiber_pool.hpp"
#include "gui/components/components.hpp"
#include "misc/cpp/imgui_stdlib.h"
#include "natives.hpp"

namespace big
{
	bool components::input_text_with_hint(const std::string_view label, const std::string_view hint, char* buf, size_t buf_size, int flag, std::function<void()> cb)
	{
		bool returned = false;
		if (returned = ImGui::InputTextWithHint(label.data(), hint.data(), buf, buf_size, flag); returned && cb)
			g_fiber_pool->queue_job(std::move(cb));

		if (ImGui::IsItemActive())
			g.self.hud.typing = TYPING_TICKS;
		return returned;
	}

	bool components::input_text_with_hint(const std::string_view label, const std::string_view hint, std::string& buf, int flag, std::function<void()> cb, ImGuiInputTextCallback callback)
	{
		bool returned = false;
		if (returned = ImGui::InputTextWithHint(label.data(), hint.data(), &buf, flag, callback); returned && cb)
			g_fiber_pool->queue_job(std::move(cb));

		if (ImGui::IsItemActive())
			g.self.hud.typing = TYPING_TICKS;
		return returned;
	}
}