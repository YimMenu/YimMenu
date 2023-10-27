#include "core/data/language_codes.hpp"
#include "core/data/player.hpp"
#include "core/scr_globals.hpp"
#include "core/settings/protections.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/gui/gui_service.hpp"
#include "services/vehicle/persist_car_service.hpp"
#include "util/delete_entity.hpp"
#include "util/globals.hpp"
#include "views/view.hpp"

#include <network/netConnection.hpp>
#include <script/globals/GPBD_FM.hpp>
#include <script/globals/GPBD_FM_3.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

inline void ver_Space()
{
	ImGui::Dummy(ImVec2(0.0f, ImGui::GetTextLineHeight()));
}

namespace big
{
	static inline big::player_ptr last_selected_player;

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

			ImGui::BeginGroup();
			{
				ImGui::Checkbox("Spectate", &g_player.spectating);
				ImGui::Spacing();
				components::sub_title("Info");
				components::options_modal(
				    "Extra Info",
				    [current_player] {
					    ImGui::BeginGroup();
					    if (auto id = current_player->id(); id != -1)
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

						    ImGui::Spacing();
						    auto ip   = current_player->get_ip_address();
						    auto port = current_player->get_port();

						    if (ip)
						    {
							    ImGui::Text("IP Address: %d.%d.%d.%d:%d",
							        ip.value().m_field1,
							        ip.value().m_field2,
							        ip.value().m_field3,
							        ip.value().m_field4,
							        port);
							    ImGui::SameLine();
							    if (ImGui::SmallButton("copy##copyip"))
								    ImGui::SetClipboardText(std::format("{}.{}.{}.{}:{}",
								        ip.value().m_field1,
								        ip.value().m_field2,
								        ip.value().m_field3,
								        ip.value().m_field4,
								        port)
								                                .c_str());
						    }
						    else if (auto net_player_data = current_player->get_net_data())
						    {
							    ImGui::Text(net_player_data->m_force_relays ? "IP Address: Hidden" : "IP Address: Unknown");
							    if (g_protections.force_relay_connections)
								    ImGui::Text("Note - IP addresses cannot be seen when Force Relay Connections is enabled.");
							    else
							    {
								    auto conn_peer = current_player->get_connection_peer();
								    auto cxn_type  = conn_peer ? conn_peer->m_peer_address.m_connection_type : 0;

								    if (cxn_type == 2)
									    ImGui::Text("Cannot retrieve IP address since this player is connected through dedicated servers.");
								    else if (cxn_type == 3)
									    ImGui::Text("Cannot retrieve IP address since this player is connected through another player.");
							    }
						    }
					    }
					    ImGui::EndGroup();

					    ImGui::Separator();

					    ImGui::Checkbox("Block Explosions", &current_player->block_explosions);
					    ImGui::Checkbox("Block Clone Creates", &current_player->block_clone_create);
					    ImGui::Checkbox("Block Clone Syncs", &current_player->block_clone_sync);
					    ImGui::Checkbox("Block Network Events", &current_player->block_net_events);
					    ImGui::Checkbox("Log Clones", &current_player->log_clones);
				    },
				    false);
				ImGui::SameLine();
				components::button("SC Profile", [current_player] {
					uint64_t gamerHandle[13];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(current_player->id(), (Any*)&gamerHandle, 13);
					NETWORK::NETWORK_SHOW_PROFILE_UI((Any*)&gamerHandle);
				});
				ver_Space();
				if (components::button("Copy Name##copyname"))
					ImGui::SetClipboardText(current_player->get_name());
			}
			ImGui::EndGroup();

			if (current_player->id() == self::id)
				return;

			ImGui::SameLine(0, *g_pointers->m_gta.m_resolution_x * 0.4);

			ImGui::BeginGroup();
			{
				ImGui::BeginGroup();
				{
					components::sub_title("Teleport");

					components::player_command_button<"playertp">(current_player);
					ImGui::SameLine();
					components::player_command_button<"playervehtp">(current_player);
					ImGui::SameLine();
					components::player_command_button<"bring">(current_player);
				}
				ImGui::EndGroup();
				ver_Space();
				ImGui::BeginGroup();
				{
					components::sub_title("Misc");

					components::player_command_button<"clearwanted">(current_player);
					ImGui::SameLine();
					components::player_command_button<"joinceo">(current_player);

					ImGui::Spacing();

					components::player_command_button<"givehealth">(current_player);
					ImGui::SameLine();
					components::player_command_button<"givearmor">(current_player);
					ImGui::SameLine();
					components::player_command_button<"giveammo">(current_player);

					ImGui::Spacing();
					components::player_command_button<"copyoutfit">(current_player);
					ImGui::SameLine();
					components::button("Copy Vehicle", [current_player] {
						if (Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(current_player->id()), false); veh)
							persist_car_service::clone_ped_car(self::ped, veh);
					});
				}
				ImGui::EndGroup();
				ver_Space();
				ImGui::BeginGroup();
				{
					components::sub_title("Kick");

					if (g_player_service->get_self()->is_host())
						components::player_command_button<"hostkick">(current_player);
					else
					{
						components::player_command_button<"shkick">(current_player);
						ver_Space();
						components::player_command_button<"nfkick">(current_player);
						components::player_command_button<"endkick">(current_player);
					}

					if (!current_player->is_host())
						components::player_command_button<"desync">(current_player);
				}
				ImGui::EndGroup();
				ver_Space();
				ImGui::BeginGroup();
				{
					components::sub_title("Toxic");
					ImGui::BeginDisabled(globals::get_interior_from_player(current_player->id()) != 0);
					components::player_command_button<"kill">(current_player, {});
					ImGui::EndDisabled();

					components::player_command_button<"vehkick">(current_player, {});
					components::button("Delete Vehicle", [current_player] {
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(current_player->id()), false);
						entity::delete_entity(veh);
					});
					components::button("Empty Vehicle", [current_player] {
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(current_player->id()), false);
						if (veh && ENTITY::IS_ENTITY_A_VEHICLE(veh))
							vehicle::clear_all_peds(veh);
					});
				}
				ImGui::EndGroup();
			}
			ImGui::EndGroup();
		}
	}
}