#include "gui/components/components.hpp"
#include "natives.hpp"
#include "util/system.hpp"
#include "view_debug.hpp"

namespace big
{
	void debug::misc()
	{
		if (ImGui::BeginTabItem("Misc"))
		{
			if (components::button("Dump entrypoints"))
			{
				system::dump_entry_points();
			}

			components::button("Network Bail", []
			{
				NETWORK::NETWORK_BAIL(16, 0, 0);
			});

			if (g_local_player && g_local_player->m_player_info)
			{
				ImGui::InputScalar("Rockstar ID", ImGuiDataType_S64, &g_local_player->m_player_info->m_net_player_data.m_gamer_handle_2.m_rockstar_id, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
			}

			ImGui::EndTabItem();
		}
	}
}