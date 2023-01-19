#include "gui/components/components.hpp"
#include "natives.hpp"
#include "util/system.hpp"
#include "util/misc.hpp"
#include "view_debug.hpp"
#include "network/Network.hpp"
#include "script.hpp"
#include "gta/joaat.hpp"
#include "script_global.hpp"
#include "gta_util.hpp"

namespace big
{
	void debug::misc()
	{
		if (ImGui::BeginTabItem("Misc"))
		{
			if (components::button("MOV QWORD"))
			{
				*static_cast<uint64_t*>(nullptr) = 0;
				uint64_t i = *static_cast<uint64_t*>(nullptr);
            }

			if (components::button("MOV 0xdead"))
			{
				*((unsigned int*)0) = 0xDEAD;
			}

			if (components::button("Dump entrypoints"))
			{
				system::dump_entry_points();
			}

			components::button("Network Bail", []
			{
				NETWORK::NETWORK_BAIL(16, 0, 0);
			});

			components::button("Remove from Bad Sport", []
			{
				STATS::STAT_SET_FLOAT(RAGE_JOAAT("mpply_overall_badsport"), 0.0f, TRUE);
				STATS::STAT_SET_BOOL(RAGE_JOAAT("mpply_was_i_bad_sport"), FALSE, TRUE);
			});

			ImGui::EndTabItem();
		}
	}
}