#include "fiber_pool.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "thread_pool.hpp"
#include "util/system.hpp"
#include "views/view.hpp"

namespace big
{
	void view::debug_misc() 
	{
		components::button("Load MP Map", []
		{
				DLC::ON_ENTER_MP();
		});
		ImGui::SameLine();
		components::button("Load SP Map", []
		{
			DLC::ON_ENTER_SP();
		});

		ImGui::Checkbox("Log Metrics", &g->debug.logs.metric_logs);

		if (components::button("Dump entrypoints"))
		{
			system::dump_entry_points();
		}

		components::button("Network Bail", []
		{
			NETWORK::NETWORK_BAIL(16, 0, 0);
		});
	}
}