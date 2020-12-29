#include "tab_bar.hpp"
#include "pointers.hpp"
#include "script_global.hpp"

namespace big
{
	void tabbar::render_online()
	{
		if (ImGui::BeginTabItem("Online"))
		{
			if (ImGui::TreeNode("Self"))
			{
				if (ImGui::Checkbox("Off-Radar", g_settings.options["off_radar"].get<bool*>()))
					g_settings.save();

				ImGui::SameLine();

				if (ImGui::Checkbox("Reveal Players", g_settings.options["reveal_players"].get<bool*>()))
					g_settings.save();

				if (ImGui::Checkbox("Player Join Message", g_settings.options["join_message"].get<bool*>()))
					g_settings.save();

				ImGui::TreePop();
			}
			ImGui::Separator();

			if (ImGui::TreeNode("Money"))
			{
				ImGui::Text("Instructions:\n\nTake a vehicle from the street.\nGo in LSC and put a tracker on it.\nOpen the sell submenu but don't confirm it.\nOpen this menu and click one of the below buttons.");

				if (ImGui::Button("Set Car Sell Value at 25 million"))
				{
					features::functions::set_car_sell_value((int)25e6);
				}

				if (ImGui::Button("Set Car Sell Value at INT_MAX (2.1 billion)"))
				{
					features::functions::set_car_sell_value(INT_MAX);
				}

				if (ImGui::Button("Reset Vehicle Sell Stats"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						features::functions::reset_vehicle_sell_stats();
					}QUEUE_JOB_END_CLAUSE
				}

				ImGui::TreePop();
			}
			ImGui::Separator();

			if (ImGui::TreeNode("Spoofing"))
			{
				if (ImGui::Checkbox("Spoof Online Rank", g_settings.options["spoof_rank"].get<bool*>()))
					g_settings.save();

				ImGui::Text("Rank:");
				if (ImGui::InputInt("##rank", (PINT)g_settings.options["rank"].get<int64_t*>(), 1, 50))
					g_settings.save();

				ImGui::TreePop();
			}
			ImGui::Separator();

			if (ImGui::TreeNode("World"))
			{
				ImGui::Text("Time: ");
				ImGui::SliderInt("Hour:", &g_temp.time.hour, 0, 23);
				ImGui::SliderInt("Minutes:", &g_temp.time.minutes, 0, 59);
				if (ImGui::Button("Apply"))
				{
					QUEUE_JOB_BEGIN_CLAUSE(= )
					{
						NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g_temp.time.hour, g_temp.time.minutes, 0);

						g_pointers->m_sync_local_time(1, 0);
					}QUEUE_JOB_END_CLAUSE
				}

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}