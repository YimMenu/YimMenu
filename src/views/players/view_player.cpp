#include "core/data/language_codes.hpp"
#include "core/scr_globals.hpp"
#include "core/settings.hpp"
#include "natives.hpp"
#include "services/gui/gui_service.hpp"
#include "views/view.hpp"

#include <script/globals/GPBD_FM.hpp>
#include <script/globals/GPBD_FM_3.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

inline void ver_Space()
{
	ImGui::Dummy(ImVec2(0.0f, ImGui::GetTextLineHeight()));
}

big::player_ptr last_selected_player;

namespace big
{
	void view::view_player()
	{
		ImGui::Spacing();
		if (g_player_service->get_selected()->is_valid())
		{
			player_ptr current_player = g_player_service->get_selected();

			if (last_selected_player != current_player)
			{
				last_selected_player          = current_player;
				navigation_struct& player_tab = g_gui_service->get_navigation().at(tabs::PLAYER);

				strcpy(player_tab.name, current_player->get_name());
				strcat(player_tab.name, std::format(" ({})", std::to_string(current_player->id())).data());

				if (current_player->is_host())
					strcat(player_tab.name, " [HOST]");
				if (current_player->is_friend())
					strcat(player_tab.name, " [FRIEND]");
				if (current_player->is_modder)
					strcat(player_tab.name, " [MOD]");
			}

			if (current_player->id() == self::id)
				return;

			ImGui::BeginGroup();
			{
				ImGui::BeginGroup();
				{
					ImGui::Checkbox("Spectate", &g.player.spectating);
					ImGui::Spacing();

					components::sub_title("Info");
					components::options_modal(
					    "Extra Info",
					    [] {
						    ImGui::BeginGroup();

						    auto id = g_player_service->get_selected()->id();

						    if (id != -1)
						    {
							    auto& stats     = scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[id].PlayerStats;
							    auto& boss_goon = scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[id].BossGoon;

							    const auto money  = reinterpret_cast<uint64_t&>(stats.Money);
							    const auto wallet = reinterpret_cast<uint64_t&>(stats.WalletBalance);

							    if (boss_goon.Language >= 0 && boss_goon.Language < 13)
								    ImGui::Text("Language: %s", languages[boss_goon.Language].name);

							    ImGui::Text("Money In Wallet: %llu", wallet);
							    ImGui::Text("Money In Bank: %llu", money - wallet);
							    ImGui::Text("Total Money: %llu", money);
							    ImGui::Text("Rank: %d (RP %d)", stats.Rank, stats.RP);
							    ImGui::Text("K/D Ratio: %f", stats.KdRatio);
							    ImGui::Text("Kills On Players: %d", stats.KillsOnPlayers);
							    ImGui::Text("Deaths By Players: %d", stats.DeathsByPlayers);
						    }
						    ImGui::EndGroup();

						    ImGui::Separator();

						    ImGui::Checkbox("Block Explosions", &g_player_service->get_selected()->block_explosions);
						    ImGui::Checkbox("Block Clone Creates", &g_player_service->get_selected()->block_clone_create);
						    ImGui::Checkbox("Block Clone Syncs", &g_player_service->get_selected()->block_clone_sync);
						    ImGui::Checkbox("Block Network Events", &g_player_service->get_selected()->block_net_events);
						    ImGui::Checkbox("Log Clones", &g_player_service->get_selected()->log_clones);
					    },
					    false);
					ImGui::SameLine();
					components::button("SC Profile", [] {
						uint64_t gamerHandle[13];
						NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_player_service->get_selected()->id(), (Any*)&gamerHandle, 13);
						NETWORK::NETWORK_SHOW_PROFILE_UI((Any*)&gamerHandle);
					});
				}
				ImGui::EndGroup();
			}
			ImGui::EndGroup();

			ImGui::SameLine(0, 2.0f * ImGui::GetTextLineHeight());

			ImGui::BeginGroup();
			{
				ImGui::BeginGroup();
				{
					components::sub_title("Teleport");

					components::player_command_button<"playertp">(g_player_service->get_selected());
					ImGui::SameLine();
					components::player_command_button<"playervehtp">(g_player_service->get_selected());
					ImGui::SameLine();
					components::player_command_button<"bring">(g_player_service->get_selected());
				}
				ImGui::EndGroup();
				ver_Space();
				ImGui::BeginGroup();
				{
					components::sub_title("Misc");

					components::player_command_button<"copyoutfit">(g_player_service->get_selected());
					ImGui::SameLine();
					components::player_command_button<"clearwanted">(g_player_service->get_selected());

					ImGui::Spacing();

					components::player_command_button<"joinceo">(g_player_service->get_selected());

					ImGui::Spacing();

					components::player_command_button<"givehealth">(g_player_service->get_selected());
					ImGui::SameLine();
					components::player_command_button<"givearmor">(g_player_service->get_selected());
					ImGui::SameLine();
					components::player_command_button<"giveammo">(g_player_service->get_selected());
				}
				ImGui::EndGroup();
				ver_Space();
				ImGui::BeginGroup();
				{
					components::sub_title("Kick");

					if (g_player_service->get_self()->is_host())
						components::player_command_button<"hostkick">(g_player_service->get_selected());
					else
					{
						components::player_command_button<"shkick">(g_player_service->get_selected());
						ver_Space();
						components::player_command_button<"nfkick">(g_player_service->get_selected());
						components::player_command_button<"endkick">(g_player_service->get_selected());
						components::player_command_button<"desync">(g_player_service->get_selected());
					}
				}
				ImGui::EndGroup();
				ver_Space();
				ImGui::BeginGroup();
				{
					components::sub_title("Toxic");

					components::player_command_button<"kill">(g_player_service->get_selected(), {});
				}
				ImGui::EndGroup();
			}
			ImGui::EndGroup();
		}
	}
}