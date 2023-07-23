#include "core/data/command_access_levels.hpp"
#include "core/data/language_codes.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "services/player_database/player_database_service.hpp"
#include "views/view.hpp"

#include <network/netConnection.hpp>
#include <script/globals/GPBD_FM.hpp>
#include <script/globals/GPBD_FM_3.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	const char* get_nat_type_str(int type)
	{
		switch (type)
		{
		case 1: return "Open";
		case 2: return "Moderate";
		case 3: return "Strict";
		}

		return "Unknown";
	}

	const char* get_connection_type_str(int type)
	{
		switch (type)
		{
		case 1: return "Direct";
		case 2: return "Relay";
		case 3: return "Peer Relay";
		}

		return "Unknown";
	}

	void view::player_info()
	{
		ImGui::BeginGroup();
		components::sub_title("Info");

		if (ImGui::BeginListBox("##infobox", get_listbox_dimensions()))
		{
			uint32_t ped_damage_bits = 0;
			uint32_t ped_task_flag   = 0;
			uint32_t ped_health      = 0;
			uint32_t ped_maxhealth   = 0;
			uint32_t veh_damage_bits = 0;
			std::string mode_str     = "";

			if (CPed* ped = g_player_service->get_selected()->get_ped(); ped != nullptr)
			{
				ped_damage_bits = ped->m_damage_bits;
				ped_task_flag   = ped->m_ped_task_flag;
				ped_health      = ped->m_health;
				ped_maxhealth   = ped->m_maxhealth;
			}

			components::options_modal(
			    "Extra Info",
			    [ped_health, ped_maxhealth] {
				    ImGui::BeginGroup();

				    auto id = g_player_service->get_selected()->id();

				    if (id != -1)
				    {
					    auto& stats     = scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[id].PlayerStats;
					    auto& boss_goon = scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[id].BossGoon;

					    const auto money  = reinterpret_cast<uint64_t&>(stats.Money);
					    const auto wallet = reinterpret_cast<uint64_t&>(stats.WalletBalance);

					    if (boss_goon.Language >= 0 && boss_goon.Language < 13)
						    ImGui::Text("PLAYER_INFO_LANGUAGE"_T.data(), languages[boss_goon.Language].name);

					    ImGui::Text("PLAYER_INFO_CEO_NAME"_T.data(), boss_goon.GangName);
					    ImGui::Text("PLAYER_INFO_MC_NAME"_T.data(), boss_goon.ClubhouseName);
					    ImGui::Text("PLAYER_INFO_WALLET"_T.data(), wallet);
					    ImGui::Text("PLAYER_INFO_BANK"_T.data(), money - wallet);
					    ImGui::Text("PLAYER_INFO_TOTAL_MONEY"_T.data(), money);
					    ImGui::Text("PLAYER_INFO_RANK"_T.data(), stats.Rank, stats.RP);
					    ImGui::Text("Health: %d (MaxHealth: %d)", ped_health, ped_maxhealth); // TODO: translate
					    ImGui::Text("PLAYER_INFO_KD"_T.data(), stats.KdRatio);
					    ImGui::Text("PLAYER_INFO_KILLS"_T.data(), stats.KillsOnPlayers);
					    ImGui::Text("PLAYER_INFO_DEATHS"_T.data(), stats.DeathsByPlayers);
					    ImGui::Text("PLAYER_INFO_PROSTITUTES"_T.data(), stats.ProstitutesFrequented);
					    ImGui::Text("PLAYER_INFO_LAP_DANCES"_T.data(), stats.LapDancesBought);
					    ImGui::Text("PLAYER_INFO_MISSIONS_CREATED"_T.data(), stats.MissionsCreated);
					    ImGui::Text("PLAYER_INFO_METLDOWN_COMPLETE"_T.data(),
					        scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[id].MeltdownComplete ? "YES"_T.data() :
					                                                                              "NO"_T.data()); // curious to see if anyone has actually played singleplayer
				    }

				    ImGui::EndGroup();

				    ImGui::SameLine();

				    ImGui::BeginGroup();

				    ImGui::Text("NAT Type: %s", get_nat_type_str(g_player_service->get_selected()->get_net_data()->m_nat_type));

				    if (auto peer = g_player_service->get_selected()->get_connection_peer())
				    {
					    ImGui::Text("Connection Type: %s", get_connection_type_str(peer->m_peer_address.m_connection_type));

					    if (peer->m_peer_address.m_connection_type == 2)
					    {
						    auto ip = peer->m_relay_address.m_relay_address;
						    ImGui::Text("Relay IP: %d.%d.%d.%d", ip.m_field1, ip.m_field2, ip.m_field3, ip.m_field4);
					    }
					    else if (peer->m_peer_address.m_connection_type == 3)
					    {
						    auto ip = peer->m_peer_address.m_relay_address;
						    ImGui::Text("Peer Relay IP: %d.%d.%d.%d", ip.m_field1, ip.m_field2, ip.m_field3, ip.m_field4);
					    }

					    ImGui::Text("Num Messages Sent: %d", peer->m_num_messages_batched);
					    ImGui::Text("Num Reliables Sent: %d", peer->m_num_reliable_messages_batched);
					    ImGui::Text("Num Reliables Resent: %d", peer->m_num_resent_reliable_messages_batched);
					    ImGui::Text("Num Encryption Attempts: %d", peer->m_num_encryption_attempts);
				    }

				    ImGui::EndGroup();

				    ImGui::Separator();

				    ImGui::Checkbox("Block Explosions", &g_player_service->get_selected()->block_explosions);
				    ImGui::Checkbox("Block Clone Creates", &g_player_service->get_selected()->block_clone_create);
				    ImGui::Checkbox("Block Clone Syncs", &g_player_service->get_selected()->block_clone_sync);
				    ImGui::Checkbox("Block Network Events", &g_player_service->get_selected()->block_net_events);
				    ImGui::Checkbox("Log Clones", &g_player_service->get_selected()->log_clones);

				    ImGui::Separator();

				    if (ImGui::BeginCombo("CHAT_COMMAND_PERMISSIONS"_T.data(),
				            COMMAND_ACCESS_LEVELS[g_player_service->get_selected()->command_access_level.value_or(
				                g.session.chat_command_default_access_level)]))
				    {
					    for (const auto& [type, name] : COMMAND_ACCESS_LEVELS)
					    {
						    if (ImGui::Selectable(name,
						            type == g_player_service->get_selected()->command_access_level.value_or(g.session.chat_command_default_access_level)))
						    {
							    g.session.chat_command_default_access_level = type;
							    g_player_database_service->get_or_create_player(g_player_service->get_selected())->command_access_level = type;
							    g_player_database_service->save();
						    }

						    if (type == g_player_service->get_selected()->command_access_level.value_or(g.session.chat_command_default_access_level))
						    {
							    ImGui::SetItemDefaultFocus();
						    }
					    }

					    ImGui::EndCombo();
				    }
			    },
			    false,
			    "Extra Info");

			ImGui::SameLine();

			if (ImGui::SmallButton("PLAYER_INFO_ADD_TO_DB"_T.data()))
			{
				g_player_database_service->get_or_create_player(g_player_service->get_selected());
			}

			ImGui::SameLine();

			if (ImGui::SmallButton("SC Profile"))
				g_fiber_pool->queue_job([] {
					uint64_t gamerHandle[13];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_player_service->get_selected()->id(), (Any*)&gamerHandle, 13);
					NETWORK::NETWORK_SHOW_PROFILE_UI((Any*)&gamerHandle);
				});

			if (CPlayerInfo* player_info = g_player_service->get_selected()->get_player_info(); player_info != nullptr)
			{
				ImGui::Text("PLAYER_INFO_WANTED_LEVEL"_T.data(), player_info->m_wanted_level);
			}

			if (ped_damage_bits & (uint32_t)eEntityProofs::GOD)
			{
				mode_str = "PLAYER_INFO_GOD"_T;
			}
			else
			{
				if (ped_damage_bits & (uint32_t)eEntityProofs::BULLET)
				{
					mode_str += "PLAYER_INFO_BULLET"_T;
				}
				if (ped_damage_bits & (uint32_t)eEntityProofs::EXPLOSION)
				{
					mode_str += "PLAYER_INFO_EXPLOSION"_T;
				}
				if (ped_health > 328 || ped_maxhealth > 328 && !(uint32_t)eEntityProofs::EXPLOSION && !(uint32_t)eEntityProofs::BULLET)
				{
					mode_str += "Unnatural Health";
				}
			}

			if (mode_str.empty())
			{
				mode_str = "NO"_T;
			}

			ImGui::Text("PLAYER_INFO_PROOFS"_T.data(), mode_str.c_str());

			mode_str = "";

			if (auto vehicle = g_player_service->get_selected()->get_current_vehicle(); vehicle != nullptr)
			{
				veh_damage_bits = vehicle->m_damage_bits;
			}

			if (ped_task_flag & (uint8_t)ePedTask::TASK_DRIVING)
			{
				if (veh_damage_bits & (uint32_t)eEntityProofs::GOD)
				{
					mode_str = "PLAYER_INFO_GOD"_T;
				}
				else
				{
					if (veh_damage_bits & (uint32_t)eEntityProofs::COLLISION)
					{
						mode_str += "PLAYER_INFO_COLLISION"_T;
					}
					if (veh_damage_bits & (uint32_t)eEntityProofs::EXPLOSION)
					{
						mode_str += "PLAYER_INFO_EXPLOSION"_T;
					}
				}

				if (mode_str.empty())
				{
					mode_str = "NO"_T;
				}
			}
			else
			{
				mode_str = "PLAYER_INFO_NO_VEHICLE"_T;
			}

			ImGui::Text("PLAYER_INFO_VEHICLE_PROOFS"_T.data(), mode_str.c_str());

			if (auto net_player_data = g_player_service->get_selected()->get_net_data())
			{
				ImGui::Text("PLAYER_INFO_RID"_T.data(), net_player_data->m_gamer_handle.m_rockstar_id);

				ImGui::SameLine();

				ImGui::PushID("##rid");
				if (ImGui::SmallButton("COPY"_T.data()))
					ImGui::SetClipboardText(std::to_string(net_player_data->m_gamer_handle.m_rockstar_id).data());
				ImGui::PopID();

				auto ip   = g_player_service->get_selected()->get_ip_address();
				auto port = g_player_service->get_selected()->get_port();

				if (ip)
				{
					ImGui::Text("PLAYER_INFO_IP"_T.data(),
					    ip.value().m_field1,
					    ip.value().m_field2,
					    ip.value().m_field3,
					    ip.value().m_field4,
					    port);

					ImGui::SameLine();

					// clang-format off
					ImGui::PushID("##ip");
					if (ImGui::SmallButton("COPY"_T.data()))
						ImGui::SetClipboardText(std::format("{}.{}.{}.{}:{}",
						    ip.value().m_field1,
						    ip.value().m_field2,
						    ip.value().m_field3,
						    ip.value().m_field4,
						    port).data());
					ImGui::PopID();
					// clang-format on
				}
				else
				{
					if (net_player_data->m_force_relays)
						ImGui::Text("IP Address: Hidden");
					else
						ImGui::Text("IP Address: Unknown");

					auto cxn_type = g_player_service->get_selected()->get_connection_peer() ?
					    g_player_service->get_selected()->get_connection_peer()->m_peer_address.m_connection_type :
					    0;

					if (g.protections.force_relay_connections && ImGui::IsItemHovered())
						ImGui::SetTooltip("IP addresses cannot be seen when Force Relay Connections is enabled");
					else if (cxn_type == 2 && ImGui::IsItemHovered())
						ImGui::SetTooltip("Cannot retrieve IP address since this player is connected through dedicated servers");
					else if (cxn_type == 3 && ImGui::IsItemHovered())
						ImGui::SetTooltip("Cannot retrieve IP address since this player is connected through another player");
				}
			}

			ImGui::EndListBox();
		}
		ImGui::EndGroup();
	}
}
