#include "gui/tab_bar.hpp"
#include "features/functions.hpp"
#include "pointers.hpp"
#include "script_global.hpp"

namespace big
{
	const char* weatherTypes[] = {
		"Sunny",
		"Clear",
		"Clouds",
		"Smog",
		"Fog",
		"Overcast",
		"Rain",
		"Thunder",
		"Clearing",
		"Neatral (weird)",
		"Snow",
		"Blizzard",
		"Light Snow",
		"Christmas",
		"Halloween"
	};

	void tabbar::render_online()
	{
		if (ImGui::BeginTabItem("Online"))
		{
			if (ImGui::TreeNode("Self"))
			{
				if (ImGui::Checkbox("Disable Chat Censoring", g_settings.options["disable_chat_censoring"].get<bool*>()))
					g_settings.save();

				if (ImGui::Checkbox("Off-Radar", g_settings.options["off_radar"].get<bool*>()))
					g_settings.save();

				if (ImGui::Checkbox("Player Join Message", g_settings.options["join_message"].get<bool*>()))
					g_settings.save();

				ImGui::TreePop();
			}
			ImGui::Separator();

			if (ImGui::TreeNode("Money"))
			{
				ImGui::Text("Instructions:\n\nTake a vehicle from the street.\nGo in LSC and put a tracker on it.\nOpen the sell submenu but don't confirm it.\nOpen this menu and click one of the below buttons.");

				if (ImGui::Button("Set Car Sell Value at 5 million"))
				{
					func::set_car_sell_value((int)5e6);
				}

				if (ImGui::Button("Set Car Sell Value at 25 million"))
				{
					func::set_car_sell_value((int)25e6);
				}

				ImGui::TreePop();
			}
			ImGui::Separator();

			if (ImGui::TreeNode("Spoofing"))
			{
				auto& spoof = g_settings.options["spoofing"];

				if (ImGui::Checkbox("Spoof Name", spoof["name"]["enabled"].get<bool*>()))
					g_settings.save();

				std::string* sName = spoof["name"]["value"].get<std::string*>();
				char name[20];
				strcpy(name, sName->c_str());
				if (ImGui::InputText("###input_name", name, sizeof(name)))
				{
					spoof["name"]["value"] = std::string(name);

					g_settings.save();
				}

				ImGui::Separator();

				if (ImGui::Checkbox("Spoof Online Rank", spoof["rank"]["enabled"].get<bool*>()))
					g_settings.save();

				ImGui::Text("Rank:");
				if (ImGui::InputInt("##rank", (PINT)spoof["rank"]["value"].get<int64_t*>(), 1, 50))
					g_settings.save();

				ImGui::Separator();

				if (ImGui::Checkbox("Spoof IP Address", spoof["ip_address"]["enabled"].get<bool*>()))
					g_settings.save();

				ImGui::Text("IP Address:");
				int ip_address[4];
				ip_address[0] = spoof["ip_address"]["address"]["byte0"];
				ip_address[1] = spoof["ip_address"]["address"]["byte1"];
				ip_address[2] = spoof["ip_address"]["address"]["byte2"];
				ip_address[3] = spoof["ip_address"]["address"]["byte3"];
				if (ImGui::SliderInt4("###ip_address_spoof", ip_address, 0, 255))
				{
					spoof["ip_address"]["address"]["byte0"] = ip_address[0];
					spoof["ip_address"]["address"]["byte1"] = ip_address[1];
					spoof["ip_address"]["address"]["byte2"] = ip_address[2];
					spoof["ip_address"]["address"]["byte3"] = ip_address[3];

					g_settings.save();
				}

				ImGui::Separator();

				if (ImGui::Checkbox("Spoof Rockstar ID", spoof["rockstar_id"]["enabled"].get<bool*>()))
					g_settings.save();

				ImGui::Text("Rockstar ID:");
				if (ImGui::InputScalar("###rockstar_id_spoof", ImGuiDataType_U64, (PUINT64)spoof["rockstar_id"]["value"].get<uint64_t*>()))
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

				ImGui::Text("Weather:");
				if (ImGui::BeginCombo("##weather", weatherTypes[g_temp.weather_type]))
				{
					for (uint8_t i = 0; i < IM_ARRAYSIZE(weatherTypes); i++)
					{
						bool is_selected = (g_temp.weather_type == i);
						if (ImGui::Selectable(weatherTypes[i], is_selected))
						{
							g_temp.weather_type = i;

							QUEUE_JOB_BEGIN_CLAUSE(= )
							{
								g_pointers->m_set_session_weather(1, i, 76, 0);
							}QUEUE_JOB_END_CLAUSE
						}
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}