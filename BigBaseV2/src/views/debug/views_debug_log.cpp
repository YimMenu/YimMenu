#include "view_debug.hpp"

namespace big
{
	void debug::logs()
	{
		if (ImGui::BeginTabItem("Logs"))
		{
			ImGui::Checkbox("Log Metrics", &g->debug.logs.metric_logs);

			ImGui::EndTabItem();
		}
	}
}