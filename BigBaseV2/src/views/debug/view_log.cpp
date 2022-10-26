#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "logger.hpp"

namespace big
{
	static ImVec4 get_color(const LEVELS level)
	{
		switch (level.value)
		{
		case g3::kDebugValue:
			return ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
		case g3::kInfoValue:
			return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		case g3::kWarningValue:
			return ImVec4(1.0f, 0.7f, 0.0f, 1.0f);
		}
		return g3::internal::wasFatal(level) ? ImVec4(1.0f, 0.4f, 0.4f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	static size_t iLastLogCount = 0;
	void view::log()
	{
		if (ImGui::Begin("Log"))
		{
			auto msgs = g_log->get_messages();

			for (size_t i = 0; i < msgs.size(); i++)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, get_color(msgs[i].level));
				ImGui::TextUnformatted(msgs[i].m_message.c_str());
				ImGui::PopStyleColor();
			}

			if (iLastLogCount != msgs.size())
			{
				iLastLogCount = msgs.size();
				ImGui::SetScrollHereY(1.f);
			}
			ImGui::End();
		}
	}
}
