#include "view_debug.hpp"

namespace big
{
	void debug::logs()
	{
		if (ImGui::BeginTabItem("Logs"))
		{
			ImGui::Checkbox("Log Metrics", &g->debug.logs.metric_logs);

			ImGui::Checkbox("Native Script Hooks", &g->debug.logs.script_hook_logs);

			ImGui::EndTabItem();
		}
	}
}