#include "gui/window.hpp"
#include "gui/window/main/tabs.hpp"
#include "imgui.h"
#include "renderer.hpp"
#include "logger.hpp"

namespace big
{
	static size_t iLastLogCount = 0;
	void window::log()
	{
		ImGui::SetNextWindowSize({ 500, 250 }, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos({ 50, 50 }, ImGuiCond_FirstUseEver);
		if (g.window.log && ImGui::Begin("Log"))
		{
			ImGui::PushFont(g_renderer->m_monospace_font);

			std::lock_guard lock(g_logger->m_mutex);
			auto msgs = g_logger->get_messages();

			for (size_t i = 0; i < msgs.second; i++)
			{
				ImGui::TextUnformatted(msgs.first[i].get());
			}

			if (iLastLogCount != msgs.second)
			{
				iLastLogCount = msgs.second;
				ImGui::SetScrollHereY(1.f);
			}

			ImGui::PopFont();

			ImGui::End();
		}
	}
}