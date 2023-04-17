#include "components.hpp"
#include "fiber_pool.hpp"
#include "services/script_patcher/script_patcher_service.hpp"

namespace big
{
	bool components::script_patch_checkbox(const std::string_view text, bool* option, const std::string_view tooltip)
	{
		bool ret = ImGui::Checkbox(text.data(), option);
		if (ret)
		{
			g_fiber_pool->queue_job([] {
				g_script_patcher_service->update();
			});
		}

		if (!tooltip.empty())
		{
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(tooltip.data());
		}

		return ret;
	}
}