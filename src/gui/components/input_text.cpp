#include "core/data/hud.hpp"
#include "fiber_pool.hpp"
#include "gui/components/components.hpp"
#include "misc/cpp/imgui_stdlib.h"
#include "natives.hpp"

namespace big
{
	bool components::input_text(const std::string_view label, char* buf, size_t buf_size, ImGuiInputTextFlags_ flag, std::function<void()> cb)
	{
		bool retval = false;
		if (ImGui::InputText(label.data(), buf, buf_size, flag))
		{
			if (cb)
				g_fiber_pool->queue_job(std::move(cb));
			retval = true;
		}

		if (ImGui::IsItemActive())
			g_hud.typing = TYPING_TICKS;

		return retval;
	}

	bool components::input_text(const std::string_view label, std::string& buf, ImGuiInputTextFlags_ flag, std::function<void()> cb)
	{
		bool retval = false;
		if (ImGui::InputText(label.data(), &buf, flag))
		{
			if (cb)
				g_fiber_pool->queue_job(std::move(cb));
			retval = true;
		}

		if (ImGui::IsItemActive())
			g_hud.typing = TYPING_TICKS;

		return retval;
	}
}