#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/local_player.hpp"
#include "util/misc.hpp"
#include "util/heist.hpp"
#include "util/teleport.hpp"
#include "util/scripts.hpp"
#include "pointers.hpp"

namespace big
{
	static int cph_radio_button_index = 0;
	static int h4_playthrough_status = 0;
	static int h4cnf_approach = 0;
	static int h4cnf_bs_entr = 0;
	static int h4cnf_target = 0;
	static int h4_progress = 0;
	static int h4loot_cash_v = 0;
	static int h4loot_weed_v = 0;
	static int h4loot_coke_v = 0;
	static int h4loot_gold_v = 0;
	static int h4loot_paint_v = 0;
	static int h4loot_cash_i = 0;
	static int h4loot_weed_i = 0;
	static int h4loot_coke_i = 0;
	static int h4loot_gold_i = 0;
	static int h4loot_cash_i_scoped = 0;
	static int h4loot_weed_i_scoped = 0;
	static int h4loot_coke_i_scoped = 0;
	static int h4loot_gold_i_scoped = 0;
	static int h4loot_cash_c = 0;
	static int h4loot_weed_c = 0;
	static int h4loot_coke_c = 0;
	static int h4loot_gold_c = 0;
	static int h4loot_cash_c_scoped = 0;
	static int h4loot_weed_c_scoped = 0;
	static int h4loot_coke_c_scoped = 0;
	static int h4loot_gold_c_scoped = 0;
	static int h4loot_paint = 0;
	static int h4loot_paint_scoped = 0;
	static int h4cnf_grappel = 0;
	static int h4cnf_uniform = 0;
	static int h4cnf_boltcut = 0;
	static int h4cnf_trojan = 0;
	static int h4cnf_bs_gen = 0;
	static int h4cnf_weapons = 0;
	static int h4_missions = 0;
	static int h4cnf_bs_abil = 0;
	static void tab_item_cayo_perico_heist()
	{
		if (ImGui::BeginTabItem("Cayo Perico Heist"))
		{
			ImGui::Text("Reward Limit: 255K + 10K");

			enum Mode
			{
				PREP,
				TUNABLE,
				TELEPORT,
				MISC
			};

			ImGui::RadioButton("Prep", &cph_radio_button_index, PREP); ImGui::SameLine();
			ImGui::RadioButton("Tunable", &cph_radio_button_index, TUNABLE); ImGui::SameLine();
			ImGui::RadioButton("Teleport", &cph_radio_button_index, TELEPORT); ImGui::SameLine();
			ImGui::RadioButton("Misc", &cph_radio_button_index, MISC);

			switch (cph_radio_button_index)
			{
			case PREP:
			{
				ImGui::Text("Make sure to pay 25K to open the heist before editing");
				ImGui::Text("If the panel doesn't change, please re-enter the kosatka interior");
				ImGui::Text(std::format("Complete island heist times: {}", h4_playthrough_status).c_str());

				if (ImGui::TreeNode("Infiltration Points"))
				{
					ImGui::BeginGroup();

					static bool airstrip = false;
					airstrip = misc::has_bit_set(&h4cnf_approach, 0);
					components::checkbox("Airstrip##infiltration_points", &airstrip, [] { airstrip ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 0) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 0); });

					static bool halo_jump = false;
					halo_jump = misc::has_bit_set(&h4cnf_approach, 1);
					components::checkbox("Halo Jump##infiltration_points", &halo_jump, [] { halo_jump ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 1) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 1); });

					static bool west_beach = false;
					west_beach = misc::has_bit_set(&h4cnf_approach, 2);
					components::checkbox("West Beach##infiltration_points", &west_beach, [] { west_beach ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 2) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 2); });

					static bool main_dock = false;
					main_dock = misc::has_bit_set(&h4cnf_approach, 3);
					components::checkbox("Main Dock##infiltration_points", &main_dock, [] { main_dock ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 3) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 3); });

					ImGui::EndGroup(); ImGui::SameLine();
					ImGui::BeginGroup();

					static bool north_dock = false;
					north_dock = misc::has_bit_set(&h4cnf_approach, 4);
					components::checkbox("North Dock##infiltration_points", &north_dock, [] { north_dock ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 4) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 4); });

					static bool north_drop_zone = false;
					north_drop_zone = misc::has_bit_set(&h4cnf_approach, 5);
					components::checkbox("North Drop Zone##infiltration_points", &north_drop_zone, [] { north_drop_zone ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 5) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 5); });

					static bool south_drop_zone = false;
					south_drop_zone = misc::has_bit_set(&h4cnf_approach, 6);
					components::checkbox("South Drop Zone##infiltration_points", &south_drop_zone, [] { south_drop_zone ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 6) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 6); });

					static bool drainage_tunnel = false;
					drainage_tunnel = misc::has_bit_set(&h4cnf_approach, 7);
					components::checkbox("Drainage Tunnel##infiltration_points", &drainage_tunnel, [] { drainage_tunnel ? local_player::stat_set_bits("$MPX_H4CNF_APPROACH", 7) : local_player::stat_clear_bits("$MPX_H4CNF_APPROACH", 7); });

					ImGui::EndGroup();
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Compound Entry Points"))
				{
					ImGui::BeginGroup();

					static bool main_gate = false;
					main_gate = misc::has_bit_set(&h4cnf_bs_entr, 0);
					components::checkbox("Main Gate##compound_entry_points", &main_gate, [] { main_gate ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 0) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 0); });

					static bool north_wall = false;
					north_wall = misc::has_bit_set(&h4cnf_bs_entr, 1);
					components::checkbox("North Wall##compound_entry_points", &north_wall, [] { north_wall ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 1) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 1); });

					static bool north_gate = false;
					north_gate = misc::has_bit_set(&h4cnf_bs_entr, 2);
					components::checkbox("North Gate##compound_entry_points", &north_gate, [] { north_gate ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 2) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 2); });

					ImGui::EndGroup(); ImGui::SameLine();
					ImGui::BeginGroup();

					static bool south_wall = false;
					south_wall = misc::has_bit_set(&h4cnf_bs_entr, 3);
					components::checkbox("South Wall##compound_entry_points", &south_wall, [] { south_wall ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 3) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 3); });

					static bool south_gate = false;
					south_gate = misc::has_bit_set(&h4cnf_bs_entr, 4);
					components::checkbox("South Gate##compound_entry_points", &south_gate, [] { south_gate ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 4) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 4); });

					static bool drainage_tunnel = false;
					drainage_tunnel = misc::has_bit_set(&h4cnf_bs_entr, 5);
					components::checkbox("Drainage Tunnel##compound_entry_points", &drainage_tunnel, [] { drainage_tunnel ? local_player::stat_set_bits("$MPX_H4CNF_BS_ENTR", 5) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ENTR", 5); });

					ImGui::EndGroup();
					ImGui::TreePop();
				}

				static bool hard_mode = false;
				hard_mode = misc::has_bit_set(&h4_progress, 12);
				components::checkbox("Hard Mode", &hard_mode, [] { hard_mode ? local_player::stat_set_bits("$MPX_H4_PROGRESS", 12) : local_player::stat_clear_bits("$MPX_H4_PROGRESS", 12); });

				if (ImGui::TreeNode("Secondary Targets"))
				{
					if (ImGui::InputInt("Cash Value##secondary_targets", &h4loot_cash_v, 0))
						g_fiber_pool->queue_job([] { local_player::stat_set_int("$MPX_H4LOOT_CASH_V", h4loot_cash_v); });
					if (ImGui::InputInt("Weed Value##secondary_targets", &h4loot_weed_v, 0))
						g_fiber_pool->queue_job([] { local_player::stat_set_int("$MPX_H4LOOT_WEED_V", h4loot_weed_v); });
					if (ImGui::InputInt("Coke Value##secondary_targets", &h4loot_coke_v, 0))
						g_fiber_pool->queue_job([] { local_player::stat_set_int("$MPX_H4LOOT_COKE_V", h4loot_coke_v); });
					if (ImGui::InputInt("Gold Value##secondary_targets", &h4loot_gold_v, 0))
						g_fiber_pool->queue_job([] { local_player::stat_set_int("$MPX_H4LOOT_GOLD_V", h4loot_gold_v); });
					if (ImGui::InputInt("Paint Value##secondary_targets", &h4loot_paint_v, 0))
						g_fiber_pool->queue_job([] { local_player::stat_set_int("$MPX_H4LOOT_PAINT_V", h4loot_paint_v); });

					ImGui::Separator();

					static const char* secondary_targets[] = { "None", "Cash", "Weed", "Coke", "Gold" };

					ImGui::Text("Real Island Secondary Targets"); ImGui::SameLine();
					components::button("Clear##real_island_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_I", 0);
					}); ImGui::SameLine();
					components::button("All Cash##real_island_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_I", 16777215);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_I", 0);
					}); ImGui::SameLine();
					components::button("All Weed##real_island_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_I", 16777215);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_I", 0);
					}); ImGui::SameLine();
					components::button("All Coke##real_island_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_I", 16777215);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_I", 0);
					}); ImGui::SameLine();
					components::button("All Gold##real_island_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_I", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_I", 16777215);
					});

					for (int i = 0; i < 24; i++)
					{
						int index = 0;
						if (misc::has_bit_set(&h4loot_cash_i, i))
							index = 1;
						if (misc::has_bit_set(&h4loot_weed_i, i))
							index = 2;
						if (misc::has_bit_set(&h4loot_coke_i, i))
							index = 3;
						if (misc::has_bit_set(&h4loot_gold_i, i))
							index = 4;
						components::button(std::format("{}##{} real_island_secondary_targets", secondary_targets[index], i), [i, index]
						{
							switch ((index + 1) % 5)
							{
							case 0:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I", i);
							}
							break;
							case 1:
							{
								local_player::stat_set_bits("$MPX_H4LOOT_CASH_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I", i);
							}
							break;
							case 2:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I", i);
								local_player::stat_set_bits("$MPX_H4LOOT_WEED_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I", i);
							}
							break;
							case 3:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I", i);
								local_player::stat_set_bits("$MPX_H4LOOT_COKE_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I", i);
							}
							break;
							case 4:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I", i);
								local_player::stat_set_bits("$MPX_H4LOOT_GOLD_I", i);
							}
							break;
							}
						});
						if ((i + 1) % 8)
							ImGui::SameLine();
					}

					ImGui::Separator();

					ImGui::Text("Scoped Island Secondary Targets"); ImGui::SameLine();
					components::button("Clear##scoped_island_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_I_SCOPED", 0);
					}); ImGui::SameLine();
					components::button("All Cash##scoped_island_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_I_SCOPED", 16777215);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_I_SCOPED", 0);
					}); ImGui::SameLine();
					components::button("All Weed##scoped_island_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_I_SCOPED", 16777215);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_I_SCOPED", 0);
					}); ImGui::SameLine();
					components::button("All Coke##scoped_island_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_I_SCOPED", 16777215);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_I_SCOPED", 0);
					}); ImGui::SameLine();
					components::button("All Gold##scoped_island_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_I_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_I_SCOPED", 16777215);
					});

					for (int i = 0; i < 24; i++)
					{
						int index = 0;
						if (misc::has_bit_set(&h4loot_cash_i_scoped, i))
							index = 1;
						if (misc::has_bit_set(&h4loot_weed_i_scoped, i))
							index = 2;
						if (misc::has_bit_set(&h4loot_coke_i_scoped, i))
							index = 3;
						if (misc::has_bit_set(&h4loot_gold_i_scoped, i))
							index = 4;
						components::button(std::format("{}##{} scoped_island_secondary_targets", secondary_targets[index], i), [i, index]
						{
							switch ((index + 1) % 5)
							{
							case 0:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I_SCOPED", i);
							}
							break;
							case 1:
							{
								local_player::stat_set_bits("$MPX_H4LOOT_CASH_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I_SCOPED", i);
							}
							break;
							case 2:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I_SCOPED", i);
								local_player::stat_set_bits("$MPX_H4LOOT_WEED_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I_SCOPED", i);
							}
							break;
							case 3:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I_SCOPED", i);
								local_player::stat_set_bits("$MPX_H4LOOT_COKE_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_I_SCOPED", i);
							}
							break;
							case 4:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_I_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_I_SCOPED", i);
								local_player::stat_set_bits("$MPX_H4LOOT_GOLD_I_SCOPED", i);
							}
							break;
							}
						});
						if ((i + 1) % 8)
							ImGui::SameLine();
					}

					ImGui::Separator();

					ImGui::Text("Real Compound Secondary Targets"); ImGui::SameLine();
					components::button("Clear##real_compound_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_C", 0);
					}); ImGui::SameLine();
					components::button("All Cash##real_compound_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_C", 255);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_C", 0);
					}); ImGui::SameLine();
					components::button("All Weed##real_compound_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_C", 255);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_C", 0);
					}); ImGui::SameLine();
					components::button("All Coke##real_compound_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_C", 255);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_C", 0);
					}); ImGui::SameLine();
					components::button("All Gold##real_compound_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_C", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_C", 255);
					});

					for (int i = 0; i < 8; i++)
					{
						int index = 0;
						if (misc::has_bit_set(&h4loot_cash_c, i))
							index = 1;
						if (misc::has_bit_set(&h4loot_weed_c, i))
							index = 2;
						if (misc::has_bit_set(&h4loot_coke_c, i))
							index = 3;
						if (misc::has_bit_set(&h4loot_gold_c, i))
							index = 4;
						components::button(std::format("{}##{} real_compound_secondary_targets", secondary_targets[index], i), [i, index]
						{
							switch ((index + 1) % 5)
							{
							case 0:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C", i);
							}
							break;
							case 1:
							{
								local_player::stat_set_bits("$MPX_H4LOOT_CASH_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C", i);
							}
							break;
							case 2:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C", i);
								local_player::stat_set_bits("$MPX_H4LOOT_WEED_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C", i);
							}
							break;
							case 3:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C", i);
								local_player::stat_set_bits("$MPX_H4LOOT_COKE_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C", i);
							}
							break;
							case 4:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C", i);
								local_player::stat_set_bits("$MPX_H4LOOT_GOLD_C", i);
							}
							break;
							}
						});
						if ((i + 1) % 8)
							ImGui::SameLine();
					}

					ImGui::Separator();

					ImGui::Text("Scoped Compound Secondary Targets"); ImGui::SameLine();
					components::button("Clear##scoped_compound_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_C_SCOPED", 0);
					}); ImGui::SameLine();
					components::button("All Cash##scoped_compound_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_C_SCOPED", 255);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_C_SCOPED", 0);
					}); ImGui::SameLine();
					components::button("All Weed##scoped_compound_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_C_SCOPED", 255);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_C_SCOPED", 0);
					}); ImGui::SameLine();
					components::button("All Coke##scoped_compound_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_C_SCOPED", 255);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_C_SCOPED", 0);
					}); ImGui::SameLine();
					components::button("All Gold##scoped_compound_secondary_targets", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_CASH_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_WEED_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_COKE_C_SCOPED", 0);
						local_player::stat_set_int("$MPX_H4LOOT_GOLD_C_SCOPED", 255);
					});

					for (int i = 0; i < 8; i++)
					{
						int index = 0;
						if (misc::has_bit_set(&h4loot_cash_c_scoped, i))
							index = 1;
						if (misc::has_bit_set(&h4loot_weed_c_scoped, i))
							index = 2;
						if (misc::has_bit_set(&h4loot_coke_c_scoped, i))
							index = 3;
						if (misc::has_bit_set(&h4loot_gold_c_scoped, i))
							index = 4;
						components::button(std::format("{}##{} scoped_compound_secondary_targets", secondary_targets[index], i), [i, index]
						{
							switch ((index + 1) % 5)
							{
							case 0:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C_SCOPED", i);
							}
							break;
							case 1:
							{
								local_player::stat_set_bits("$MPX_H4LOOT_CASH_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C_SCOPED", i);
							}
							break;
							case 2:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C_SCOPED", i);
								local_player::stat_set_bits("$MPX_H4LOOT_WEED_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C_SCOPED", i);
							}
							break;
							case 3:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C_SCOPED", i);
								local_player::stat_set_bits("$MPX_H4LOOT_COKE_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_GOLD_C_SCOPED", i);
							}
							break;
							case 4:
							{
								local_player::stat_clear_bits("$MPX_H4LOOT_CASH_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_WEED_C_SCOPED", i);
								local_player::stat_clear_bits("$MPX_H4LOOT_COKE_C_SCOPED", i);
								local_player::stat_set_bits("$MPX_H4LOOT_GOLD_C_SCOPED", i);
							}
							break;
							}
						});
						if ((i + 1) % 8)
							ImGui::SameLine();
					}

					ImGui::Separator();

					ImGui::Text("Real Paintings"); ImGui::SameLine();
					components::button("Clear##real_paintings", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_PAINT", 0);
					}); ImGui::SameLine();
					components::button("All Paint##real_paintings", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_PAINT", 127);
					});

					for (int i = 0; i < 7; i++)
					{
						components::button(std::format("{}##{} real_paintings", misc::has_bit_set(&h4loot_paint, i) ? "Paint" : "None", i), [i] { !misc::has_bit_set(&h4loot_paint, i) ? local_player::stat_set_bits("$MPX_H4LOOT_PAINT", i) : local_player::stat_clear_bits("$MPX_H4LOOT_PAINT", i); });
						if ((i + 1) % 7)
							ImGui::SameLine();
					}

					ImGui::Separator();

					ImGui::Text("Scoped Paintings"); ImGui::SameLine();
					components::button("Clear##scoped_paintings", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_PAINT_SCOPED", 0);
					}); ImGui::SameLine();
					components::button("All Paint##scoped_paintings", []
					{
						local_player::stat_set_int("$MPX_H4LOOT_PAINT_SCOPED", 127);
					});

					for (int i = 0; i < 7; i++)
					{
						components::button(std::format("{}##{} scoped_paintings", misc::has_bit_set(&h4loot_paint_scoped, i) ? "Paint" : "None", i), [i] { !misc::has_bit_set(&h4loot_paint_scoped, i) ? local_player::stat_set_bits("$MPX_H4LOOT_PAINT_SCOPED", i) : local_player::stat_clear_bits("$MPX_H4LOOT_PAINT_SCOPED", i); });
						if ((i + 1) % 7)
							ImGui::SameLine();
					}

					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Points Of Interest"))
				{
					ImGui::Text("Grappling Equipment Positions (Max = 4)");

					for (int i = 0; i < 16; i++)
					{
						components::button(std::format("{}##{} grappling_equipment_positions", misc::has_bit_set(&h4cnf_grappel, i) ? "Grappel" : "None", i), [i] { !misc::has_bit_set(&h4cnf_grappel, i) ? local_player::stat_set_bits("$MPX_H4CNF_GRAPPEL", i) : local_player::stat_clear_bits("$MPX_H4CNF_GRAPPEL", i); });
						if ((i + 1) % 8)
							ImGui::SameLine();
					}

					static bool grappling_equipment1 = false;
					grappling_equipment1 = misc::has_bit_set(&h4cnf_bs_gen, 0);
					components::checkbox("Grappling Equipment 1", &grappling_equipment1, [] { grappling_equipment1 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 0) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 0); });

					static bool grappling_equipment2 = false;
					grappling_equipment2 = misc::has_bit_set(&h4cnf_bs_gen, 1);
					components::checkbox("Grappling Equipment 2", &grappling_equipment2, [] { grappling_equipment2 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 1) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 1); });

					static bool grappling_equipment3 = false;
					grappling_equipment3 = misc::has_bit_set(&h4cnf_bs_gen, 2);
					components::checkbox("Grappling Equipment 3", &grappling_equipment3, [] { grappling_equipment3 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 2) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 2); });

					static bool grappling_equipment4 = false;
					grappling_equipment4 = misc::has_bit_set(&h4cnf_bs_gen, 3);
					components::checkbox("Grappling Equipment 4", &grappling_equipment4, [] { grappling_equipment4 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 3) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 3); });

					ImGui::Separator();

					ImGui::Text("Guard Clothing Positions (Max = 4)");
					for (int i = 0; i < 16; i++)
					{
						components::button(std::format("{}##{} guard_clothing_positions", misc::has_bit_set(&h4cnf_uniform, i) ? "Uniform" : "None", i), [i] { !misc::has_bit_set(&h4cnf_uniform, i) ? local_player::stat_set_bits("$MPX_H4CNF_UNIFORM", i) : local_player::stat_clear_bits("$MPX_H4CNF_UNIFORM", i); });
						if ((i + 1) % 8)
							ImGui::SameLine();
					}

					static bool guard_clothing1 = false;
					guard_clothing1 = misc::has_bit_set(&h4cnf_bs_gen, 4);
					components::checkbox("Guard Clothing 1", &guard_clothing1, [] { guard_clothing1 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 4) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 4); });

					static bool guard_clothing2 = false;
					guard_clothing2 = misc::has_bit_set(&h4cnf_bs_gen, 5);
					components::checkbox("Guard Clothing 2", &guard_clothing2, [] { guard_clothing2 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 5) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 5); });

					static bool guard_clothing3 = false;
					guard_clothing3 = misc::has_bit_set(&h4cnf_bs_gen, 6);
					components::checkbox("Guard Clothing 3", &guard_clothing3, [] { guard_clothing3 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 6) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 6); });

					static bool guard_clothing4 = false;
					guard_clothing4 = misc::has_bit_set(&h4cnf_bs_gen, 7);
					components::checkbox("Guard Clothing 4", &guard_clothing4, [] { guard_clothing4 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 7) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 7); });

					ImGui::Separator();

					ImGui::Text("Bolt Cutters Positions");

					for (int i = 0; i < 16; i++)
					{
						components::button(std::format("{}##{} bolt_cutters_positions", misc::has_bit_set(&h4cnf_boltcut, i) ? "Boltcut" : "None", i), [i] { !misc::has_bit_set(&h4cnf_boltcut, i) ? local_player::stat_set_bits("$MPX_H4CNF_BOLTCUT", i) : local_player::stat_clear_bits("$MPX_H4CNF_BOLTCUT", i); });
						if ((i + 1) % 8)
							ImGui::SameLine();
					}

					static bool bolt_cutters1 = false;
					bolt_cutters1 = misc::has_bit_set(&h4cnf_bs_gen, 8);
					components::checkbox("Bolt Cutters 1", &bolt_cutters1, [] { bolt_cutters1 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 8) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 8); });

					static bool bolt_cutters2 = false;
					bolt_cutters2 = misc::has_bit_set(&h4cnf_bs_gen, 9);
					components::checkbox("Bolt Cutters 2", &bolt_cutters2, [] { bolt_cutters2 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 9) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 9); });

					static bool bolt_cutters3 = false;
					bolt_cutters3 = misc::has_bit_set(&h4cnf_bs_gen, 10);
					components::checkbox("Bolt Cutters 3", &bolt_cutters3, [] { bolt_cutters3 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 10) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 10); });

					static bool bolt_cutters4 = false;
					bolt_cutters4 = misc::has_bit_set(&h4cnf_bs_gen, 11);
					components::checkbox("Bolt Cutters 4", &bolt_cutters4, [] { bolt_cutters4 ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 11) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 11); });

					ImGui::Separator();

					static const char* supply_truck_positions[] = { "None", "Airstrip", "North Dock", "Main Dock - East", "Main Dock - West", "Compound Main Gate" };
					components::combo("Supply Truck Position", &h4cnf_trojan, supply_truck_positions, IM_ARRAYSIZE(supply_truck_positions), [] { local_player::stat_set_int("$MPX_H4CNF_TROJAN", h4cnf_trojan); });

					static bool supply_truck = false;
					supply_truck = misc::has_bit_set(&h4cnf_bs_gen, 15);
					components::checkbox("Supply Truck", &supply_truck, [] { supply_truck ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 15) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 15); });

					ImGui::Separator();

					static bool cutting_power = false;
					cutting_power = misc::has_bit_set(&h4cnf_bs_gen, 13);
					components::checkbox("Cutting Power", &cutting_power, [] { cutting_power ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 13) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 13); });

					static bool power_station = false;
					power_station = misc::has_bit_set(&h4cnf_bs_gen, 14);
					components::checkbox("Power Station", &power_station, [] { power_station ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 14) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 14); });

					static bool control_tower = false;
					control_tower = misc::has_bit_set(&h4cnf_bs_gen, 16);
					components::checkbox("Control Tower", &control_tower, [] { control_tower ? local_player::stat_set_bits("$MPX_H4CNF_BS_GEN", 16) : local_player::stat_clear_bits("$MPX_H4CNF_BS_GEN", 16); });

					ImGui::TreePop();
				}

				static const char* targets[] = { "Sinsimito Tequila", "Ruby Necklace", "Bearer Bonds", "Pink Diamond", "Maorazo Files", "Panther Statue" };
				components::combo("Selected Target", &h4cnf_target, targets, IM_ARRAYSIZE(targets), [] { local_player::stat_set_int("$MPX_H4CNF_TARGET", h4cnf_target); });

				static const char* weapons[] = { "None", "Aggressoh", "Conspirator", "Crack Shot", "Saboteur", "Marksman" };
				components::combo("Selected Weapon", &h4cnf_weapons, weapons, IM_ARRAYSIZE(weapons), [] { local_player::stat_set_int("$MPX_H4CNF_WEAPONS", h4cnf_weapons); });

				static bool scoped_target = false;
				scoped_target = misc::has_bit_set(&h4_missions, 0);
				components::checkbox("Scoped Target", &scoped_target, [] { scoped_target ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 0) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 0); });

				static bool submarine_kosatka = false;
				submarine_kosatka = misc::has_bit_set(&h4_missions, 1);
				components::checkbox("Approach Vehicles - Submarine: Kosatka", &submarine_kosatka, [] { submarine_kosatka ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 1) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 1); });

				static bool plane_alkonost = false;
				plane_alkonost = misc::has_bits_set(&h4_missions, 2, 7);
				components::checkbox("Approach Vehicles - Plane: Alkonost", &plane_alkonost, [] { plane_alkonost ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 2, 7) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 2, 7); });

				static bool plane_velum = false;
				plane_velum = misc::has_bit_set(&h4_missions, 3);
				components::checkbox("Approach Vehicles - Plane: Velum", &plane_velum, [] { plane_velum ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 3) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 3); });

				static bool helicopter_stealth_annihilator = false;
				helicopter_stealth_annihilator = misc::has_bits_set(&h4_missions, 4, 7);
				components::checkbox("Approach Vehicles - Helicopter: Stealth Annihilator", &helicopter_stealth_annihilator, [] { helicopter_stealth_annihilator ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 4, 7) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 4, 7); });

				static bool boat_patrol_boat = false;
				boat_patrol_boat = misc::has_bit_set(&h4_missions, 5);
				components::checkbox("Approach Vehicles - Boat: Patrol Boat", &boat_patrol_boat, [] { boat_patrol_boat ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 5) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 5); });

				static bool boat_longfin = false;
				boat_longfin = misc::has_bit_set(&h4_missions, 6);
				components::checkbox("Approach Vehicles - Boat: Longfin", &boat_longfin, [] { boat_longfin ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 6) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 6); });

				static bool demolition_charges = false;
				demolition_charges = misc::has_bit_set(&h4_missions, 8);
				components::checkbox("Equipment - Demolition Charges", &demolition_charges, [] { demolition_charges ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 8) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 8); });

				static bool plasma_cutter = false;
				plasma_cutter = misc::has_bit_set(&h4_missions, 9);
				components::checkbox("Equipment - Plasma Cutter", &plasma_cutter, [] { plasma_cutter ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 9) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 9); });

				static bool fingerprint_cloner = false;
				fingerprint_cloner = misc::has_bit_set(&h4_missions, 10);
				components::checkbox("Equipment - Fingerprint Cloner", &fingerprint_cloner, [] { fingerprint_cloner ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 10) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 10); });

				static bool cutting_torch = false;
				cutting_torch = misc::has_bit_set(&h4_missions, 11);
				components::checkbox("Equipment - Cutting Torch", &cutting_torch, [] { cutting_torch ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 11) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 11); });

				static bool weapon_loadout = false;
				weapon_loadout = misc::has_bit_set(&h4_missions, 12);
				components::checkbox("Weapon Loadout", &weapon_loadout, [] { weapon_loadout ? local_player::stat_set_bits("$MPX_H4_MISSIONS", 12) : local_player::stat_clear_bits("$MPX_H4_MISSIONS", 12); });

				static bool disruption_weapons = false;
				disruption_weapons = misc::has_bit_set(&h4_missions, 13);
				components::checkbox("Disruption - Weapons", &disruption_weapons, [] { disruption_weapons ? (local_player::stat_set_bits("$MPX_H4_MISSIONS", 13), local_player::stat_set_int("$MPX_H4CNF_WEP_DISRP", 3)) : (local_player::stat_clear_bits("$MPX_H4_MISSIONS", 13), local_player::stat_set_int("$MPX_H4CNF_WEP_DISRP", 0)); });

				static bool disruption_armor = false;
				disruption_armor = misc::has_bit_set(&h4_missions, 14);
				components::checkbox("Disruption - Armor", &disruption_armor, [] { disruption_armor ? (local_player::stat_set_bits("$MPX_H4_MISSIONS", 14), local_player::stat_set_int("$MPX_H4CNF_ARM_DISRP", 3)) : (local_player::stat_clear_bits("$MPX_H4_MISSIONS", 14), local_player::stat_set_int("$MPX_H4CNF_ARM_DISRP", 0)); });

				static bool disruption_air_support = false;
				disruption_air_support = misc::has_bit_set(&h4_missions, 15);
				components::checkbox("Disruption - Air Support", &disruption_air_support, [] { disruption_air_support ? (local_player::stat_set_bits("$MPX_H4_MISSIONS", 15), local_player::stat_set_int("$MPX_H4CNF_HEL_DISRP", 3)) : (local_player::stat_clear_bits("$MPX_H4_MISSIONS", 15), local_player::stat_set_int("$MPX_H4CNF_HEL_DISRP", 0)); });

				if (ImGui::TreeNode("Hire Support Crew"))
				{
					static bool airstrike = false;
					airstrike = misc::has_bit_set(&h4cnf_bs_abil, 0);
					components::checkbox("Airstrike", &airstrike, [] { airstrike ? local_player::stat_set_bits("$MPX_H4CNF_BS_ABIL", 0) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ABIL", 0); });

					static bool sniper = false;
					sniper = misc::has_bit_set(&h4cnf_bs_abil, 1);
					components::checkbox("Sniper", &sniper, [] { sniper ? local_player::stat_set_bits("$MPX_H4CNF_BS_ABIL", 1) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ABIL", 1); });

					static bool helicopter_backup = false;
					helicopter_backup = misc::has_bit_set(&h4cnf_bs_abil, 2);
					components::checkbox("Helicopter Backup", &helicopter_backup, [] { helicopter_backup ? local_player::stat_set_bits("$MPX_H4CNF_BS_ABIL", 2) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ABIL", 2); });

					static bool recon_drone = false;
					recon_drone = misc::has_bit_set(&h4cnf_bs_abil, 3);
					components::checkbox("Recon Drone", &recon_drone, [] { recon_drone ? local_player::stat_set_bits("$MPX_H4CNF_BS_ABIL", 3) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ABIL", 3); });

					static bool supply_drop = false;
					supply_drop = misc::has_bit_set(&h4cnf_bs_abil, 4);
					components::checkbox("Supply Drop", &supply_drop, [] { supply_drop ? local_player::stat_set_bits("$MPX_H4CNF_BS_ABIL", 4) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ABIL", 4); });

					static bool weapon_stash = false;
					weapon_stash = misc::has_bit_set(&h4cnf_bs_abil, 5);
					components::checkbox("Weapon Stash", &weapon_stash, [] { weapon_stash ? local_player::stat_set_bits("$MPX_H4CNF_BS_ABIL", 5) : local_player::stat_clear_bits("$MPX_H4CNF_BS_ABIL", 5); });

					ImGui::TreePop();
				}
			}
			break;
			case TUNABLE:
			{
				if (*g_pointers->m_script_globals)
				{
					ImGui::InputInt("Crew Cut 1", script_global(heist::cayo::crew_cut + 0).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 2", script_global(heist::cayo::crew_cut + 1).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 3", script_global(heist::cayo::crew_cut + 2).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 4", script_global(heist::cayo::crew_cut + 3).as<int*>(), 0);

					ImGui::Separator();

					ImGui::InputInt("Bag Size", script_global(heist::cayo::bag_size).as<int*>(), 0);

					ImGui::Separator();

					ImGui::InputFloat("Fencing Fee", script_global(heist::cayo::fencing_fee).as<float*>());
					ImGui::InputFloat("Pavel Fee", script_global(heist::cayo::pavel_fee).as<float*>());

					ImGui::Separator();

					ImGui::InputFloat("Multiplier Normal", script_global(heist::cayo::multiplier_normal).as<float*>());
					ImGui::InputFloat("Multiplier Hard", script_global(heist::cayo::multiplier_hard).as<float*>());

					ImGui::Separator();

					static const char* targets[] = { "Sinsimito Tequila", "Ruby Necklace", "Bearer Bonds", "Pink Diamond", "Maorazo Files", "Panther Statue" };
					for (int i = 0; i < 6; i++)
						ImGui::InputInt(std::format("{} Value", targets[i]).c_str(), script_global(heist::cayo::target_value + i).as<int*>(), 0);
				}
				else
				{
					ImGui::Text("Waiting for the game to initialize");
				}
			}
			break;
			case TELEPORT:
			{
				ImGui::BeginGroup();
				components::button("Compound Main Gate - Outside", [] { teleport::to_coords({ 4974.012207, -5704.004883, 19.88697624 }); });
				components::button("Compound Main Gate - Inside", [] { teleport::to_coords({ 4991.293457, -5718.394043, 19.88019753 }); });
				components::button("Keycard", [] { teleport::to_coords({ 5013.088379, -5756.17627, 28.90014458 }); });
				ImGui::EndGroup(); ImGui::SameLine();
				ImGui::BeginGroup();
				components::button("Target - 1", [] { teleport::to_coords({ 5006.895508, -5755.962891, 15.48677349 }); });
				components::button("Target - 2", [] { teleport::to_coords({ 5009.144531, -5753.708496, 15.47878361 }); });
				components::button("Drainage Tunnel", [] { teleport::to_coords({ 5043.570801, -5815.153809, -11.01900005 }); });
				components::button("Escape Cayo Perico", [] { teleport::to_coords({ 4796.765625, -6281.083008, -75.83087921 }); });
				ImGui::EndGroup();
			}
			break;
			case MISC:
			{
				if (auto thread = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")); thread)
				{
					scripts::force_host(RAGE_JOAAT("fm_mission_controller_2020"));
					ImGui::InputInt("Take", script_local(thread, heist::cayo::take).as<int*>(), 0);
					ImGui::InputInt("Team Lives", script_local(thread, heist::cayo::team_lives).as<int*>(), 0);
				}
				components::button("Instant Heist Passed", [] { heist::cayo::instant_heist_passed(); });
				components::button("Hack Fingerprint", [] { heist::cayo::hack_fingerprint(); });
				components::button("Plasma Cutter Instant Cut", [] { heist::cayo::plasma_cutter_instant_cut(); });
				components::button("Grate Instant Cut", [] { heist::cayo::grate_instant_cut(); });
			}
			break;
			}

			ImGui::EndTabItem();
		}
	}

	static int dch_radio_button_index = 0;
	static int cas_heist_flow = 0; 
	static int h3opt_target = 0;
	static int h3opt_bitset1 = 0;
	static int h3opt_approach = 0;
	static int h3_last_approach = 0;
	static int h3_hard_approach = 0;
	static int h3opt_crewweap = 0;
	static int h3opt_crewdriver = 0;
	static int h3opt_crewhacker = 0;
	static int h3opt_vehs = 0;
	static int h3opt_weaps = 0;
	static int h3opt_bitset0 = 0;
	static int h3opt_keylevels = 0;
	static void tab_item_diamond_casino_heist()
	{
		if (ImGui::BeginTabItem("Diamond Casino Heist"))
		{
			ImGui::Text("Reward Limit: 361.9K + 10K");

			enum Mode
			{
				PREP,
				TUNABLE,
				TELEPORT,
				MISC
			};

			ImGui::RadioButton("Prep", &dch_radio_button_index, PREP); ImGui::SameLine();
			ImGui::RadioButton("Tunable", &dch_radio_button_index, TUNABLE); ImGui::SameLine();
			ImGui::RadioButton("Teleport", &dch_radio_button_index, TELEPORT); ImGui::SameLine();
			ImGui::RadioButton("Misc", &dch_radio_button_index, MISC);

			switch (dch_radio_button_index)
			{
			case PREP:
			{
				ImGui::Text("Make sure you have arcade set up and pay 25K to open the heist before editing");
				ImGui::Text("If the panel doesn't change, please re-enter the arcade interior");

				static bool unlocked_patrick_mcreary = false;
				unlocked_patrick_mcreary = misc::has_bit_set(&cas_heist_flow, 9);
				components::checkbox("Unlocked Patrick McReary", &unlocked_patrick_mcreary, [] { unlocked_patrick_mcreary ? local_player::stat_set_bits("$MPX_CAS_HEIST_FLOW", 9) : local_player::stat_clear_bits("$MPX_CAS_HEIST_FLOW", 9); });
				
				static bool unlocked_avi_schwartzman = false;
				unlocked_avi_schwartzman = misc::has_bit_set(&cas_heist_flow, 15);
				components::checkbox("Unlocked Avi Schwartzman", &unlocked_avi_schwartzman, [] { unlocked_avi_schwartzman ? local_player::stat_set_bits("$MPX_CAS_HEIST_FLOW", 15) : local_player::stat_clear_bits("$MPX_CAS_HEIST_FLOW", 15); });

				ImGui::BeginGroup();
				components::button("Unlock All Access Points", [] { local_player::stat_set_bits("$MPX_H3OPT_ACCESSPOINTS", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10); });
				components::button("Unlock All POI", [] { local_player::stat_set_bits("$MPX_H3OPT_POI", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9); });
				ImGui::EndGroup(); ImGui::SameLine();
				ImGui::BeginGroup();
				components::button("Reset All Access Points", [] { local_player::stat_clear_bits("$MPX_H3OPT_ACCESSPOINTS", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10); });
				components::button("Reset All POI", [] { local_player::stat_clear_bits("$MPX_H3OPT_POI", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9); });
				ImGui::EndGroup();

				static const char* targets[] = {"Cash", "Gold", "Artwork", "Diamonds"};
				components::combo("Selected Target", &h3opt_target, targets, IM_ARRAYSIZE(targets), [] { local_player::stat_set_int("$MPX_H3OPT_TARGET", h3opt_target); });

				static bool scope_out_vault_contents = false;
				scope_out_vault_contents = misc::has_bit_set(&h3opt_bitset1, 0);
				components::checkbox("Scope Out Vault Contents", &scope_out_vault_contents, [] { scope_out_vault_contents ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 0) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 0); });

				static const char* approaches[] = { "None", "Silent & Sneaky", "The Big Con", "Aggressive" };
				components::combo("Selected Approach", &h3opt_approach, approaches, IM_ARRAYSIZE(approaches), [] { local_player::stat_set_int("$MPX_H3OPT_APPROACH", h3opt_approach); });
				components::combo("Selected Last Approach", &h3_last_approach, approaches, IM_ARRAYSIZE(approaches), [] { local_player::stat_set_int("$MPX_H3_LAST_APPROACH", h3_last_approach); });
				components::combo("Selected Hard Approach", &h3_hard_approach, approaches, IM_ARRAYSIZE(approaches), [] { local_player::stat_set_int("$MPX_H3_HARD_APPROACH", h3_hard_approach); });

				static const char* gunmen[] = { "None", "Karl Abolaji 5%", "Gustavo Mota 9%", "Charlie Reed 7%", "Chester McCoy 10%", "Patrick McReary 8%", "Unknown 0%" };
				components::combo("Selected Gunman", &h3opt_crewweap, gunmen, IM_ARRAYSIZE(gunmen), [] { local_player::stat_set_int("$MPX_H3OPT_CREWWEAP", h3opt_crewweap); });
				
				static const char* drivers[] = { "None", "Karim Denz 5%", "Taliana Martinez 7%", "Eddie Toh 9%", "Zach Nelson 6%", "Chester McCoy 10%", "Unknown 0%" };
				components::combo("Selected Driver", &h3opt_crewdriver, drivers, IM_ARRAYSIZE(drivers), [] { local_player::stat_set_int("$MPX_H3OPT_CREWDRIVER", h3opt_crewdriver); });

				static const char* hackers[] = { "None", "Rickie Lukens 3%", "Christian Feltz 7%", "Yohan Blair 5%", "Avi Schwartzman 10%", "Paige Harris 9%", "Unknown 0%" };
				components::combo("Selected Hacker", &h3opt_crewhacker, hackers, IM_ARRAYSIZE(hackers), [] { local_player::stat_set_int("$MPX_H3OPT_CREWHACKER", h3opt_crewhacker); });

				static const char* karl_abolaji_weapons[] = { "Micro SMG", "Machine Pistol" };
				static const char* gustavo_mota_weapons[] = { "Rifle", "Shotgun" };
				static const char* charlie_reed_weapons[] = { "SMG", "Shotgun" };
				static const char* chester_mccoy_weapons[] = { "Mk II Shotgun", "Mk II Rifle" };
				static const char* patrick_mcreary_weapons[] = { "Combat PDW", "Rifle" };
				switch (h3opt_crewweap)
				{
				case 1: { components::combo("Selected Unmarked Weapon", &h3opt_weaps, karl_abolaji_weapons, IM_ARRAYSIZE(karl_abolaji_weapons), [] { local_player::stat_set_int("$MPX_H3OPT_WEAPS", h3opt_weaps); }); } break;
				case 2: { components::combo("Selected Unmarked Weapon", &h3opt_weaps, gustavo_mota_weapons, IM_ARRAYSIZE(gustavo_mota_weapons), [] { local_player::stat_set_int("$MPX_H3OPT_WEAPS", h3opt_weaps); }); } break;
				case 3: { components::combo("Selected Unmarked Weapon", &h3opt_weaps, charlie_reed_weapons, IM_ARRAYSIZE(charlie_reed_weapons), [] { local_player::stat_set_int("$MPX_H3OPT_WEAPS", h3opt_weaps); }); } break;
				case 4: { components::combo("Selected Unmarked Weapon", &h3opt_weaps, chester_mccoy_weapons, IM_ARRAYSIZE(chester_mccoy_weapons), [] { local_player::stat_set_int("$MPX_H3OPT_WEAPS", h3opt_weaps); }); } break;
				case 5: { components::combo("Selected Unmarked Weapon", &h3opt_weaps, patrick_mcreary_weapons, IM_ARRAYSIZE(patrick_mcreary_weapons), [] { local_player::stat_set_int("$MPX_H3OPT_WEAPS", h3opt_weaps); }); } break;
				}

				static const char* karim_denz_vehicles[] = { "Issi Classic", "Asbo", "Kanjo", "Sentinel Classic" };
				static const char* taliana_martinez_vehicles[] = { "Retinue Mk II", "Drift Yosemite", "Sugoi", "Jugular" };
				static const char* eddie_toh_vehicles[] = { "Sultan Classic", "Gauntlet Classic", "Ellie", "Komoda" };
				static const char* zach_nelson_vehicles[] = { "Manchez", "Stryder", "Defiler", "Lectro" };
				static const char* chester_mccoy_vehicles[] = { "Zhaba", "Vagrant", "Outlaw", "Everon" };
				switch (h3opt_crewdriver)
				{
				case 1: { components::combo("Selected Getaway Vehicle", &h3opt_vehs, karim_denz_vehicles, IM_ARRAYSIZE(karim_denz_vehicles), [] { local_player::stat_set_int("$MPX_H3OPT_VEHS", h3opt_vehs); }); } break;
				case 2: { components::combo("Selected Getaway Vehicle", &h3opt_vehs, taliana_martinez_vehicles, IM_ARRAYSIZE(taliana_martinez_vehicles), [] { local_player::stat_set_int("$MPX_H3OPT_VEHS", h3opt_vehs); }); } break;
				case 3: { components::combo("Selected Getaway Vehicle", &h3opt_vehs, eddie_toh_vehicles, IM_ARRAYSIZE(eddie_toh_vehicles), [] { local_player::stat_set_int("$MPX_H3OPT_VEHS", h3opt_vehs); }); } break;
				case 4: { components::combo("Selected Getaway Vehicle", &h3opt_vehs, zach_nelson_vehicles, IM_ARRAYSIZE(zach_nelson_vehicles), [] { local_player::stat_set_int("$MPX_H3OPT_VEHS", h3opt_vehs); }); } break;
				case 5: { components::combo("Selected Getaway Vehicle", &h3opt_vehs, chester_mccoy_vehicles, IM_ARRAYSIZE(chester_mccoy_vehicles), [] { local_player::stat_set_int("$MPX_H3OPT_VEHS", h3opt_vehs); }); } break;
				}

				static const char* key_levels[] = { "None", "Level 1", "Level 2" };
				components::combo("Selected Key Level", &h3opt_keylevels, key_levels, IM_ARRAYSIZE(key_levels), [] { local_player::stat_set_int("$MPX_H3OPT_KEYLEVELS", h3opt_keylevels); });
				
				ImGui::BeginGroup();

				static bool vault_keycards = false;
				vault_keycards = misc::has_bit_set(&h3opt_bitset1, 1);
				components::checkbox("Vault Keycards", &vault_keycards, [] { vault_keycards ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 1) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 1); });
				
				static bool unmarked_weapons = false;
				unmarked_weapons = misc::has_bit_set(&h3opt_bitset1, 2);
				components::checkbox("Unmarked Weapons", &unmarked_weapons, [] { unmarked_weapons ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 2) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 2); });
				
				static bool getaway_vehicles = false;
				getaway_vehicles = misc::has_bit_set(&h3opt_bitset1, 3);
				components::checkbox("Getaway Vehicles", &getaway_vehicles, [] { getaway_vehicles ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 3) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 3); });
				
				static bool hacking_device = false;
				hacking_device = misc::has_bit_set(&h3opt_bitset1, 4);
				components::checkbox("Hacking Device", &hacking_device, [] { hacking_device ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 4) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 4); });
				
				static bool nano_drone = false;
				nano_drone = misc::has_bit_set(&h3opt_bitset1, 5);
				components::checkbox("Nano Drone - Silent & Sneaky", &nano_drone, [] { nano_drone ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 5) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 5); });
				
				static bool vault_laser = false;
				vault_laser = misc::has_bit_set(&h3opt_bitset1, 6);
				components::checkbox("Vault Laser - Silent & Sneaky", &vault_laser, [] { vault_laser ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 6) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 6); });
				
				static bool vault_drills = false;
				vault_drills = misc::has_bit_set(&h3opt_bitset1, 7);
				components::checkbox("Vault Drills - The Big Con", &vault_drills, [] { vault_drills ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 7) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 7); });
				
				static bool vault_explosives = false;
				vault_explosives = misc::has_bit_set(&h3opt_bitset1, 8);
				components::checkbox("Vault Explosives - Aggressive", &vault_explosives, [] { vault_explosives ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 8) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 8); });
				
				static bool thermal_charges = false;
				thermal_charges = misc::has_bit_set(&h3opt_bitset1, 9);
				components::checkbox("Thermal Charges - Aggressive", &thermal_charges, [] { thermal_charges ? local_player::stat_set_bits("$MPX_H3OPT_BITSET1", 9) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET1", 9); });
				
				ImGui::EndGroup(); ImGui::SameLine();
				ImGui::BeginGroup();

				static bool patrol_routes = false;
				patrol_routes = misc::has_bit_set(&h3opt_bitset0, 1);
				components::checkbox("Patrol Routes", &patrol_routes, [] { patrol_routes ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 1) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 1); });
				
				static bool duggan_shipments = false;
				duggan_shipments = misc::has_bit_set(&h3opt_bitset0, 2);
				components::checkbox("Duggan Shipments", &duggan_shipments, [] { duggan_shipments ? (local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 2), local_player::stat_set_int("$MPX_H3OPT_DISRUPTSHIP", 3)) : (local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 2), local_player::stat_set_int("$MPX_H3OPT_DISRUPTSHIP", 0)); });
				
				static bool infiltration_suits = false;
				infiltration_suits = misc::has_bit_set(&h3opt_bitset0, 3);
				components::checkbox("Infiltration Suits - Silent & Sneaky", &infiltration_suits, [] { infiltration_suits ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 3) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 3); });
				
				static bool power_drills = false;
				power_drills = misc::has_bit_set(&h3opt_bitset0, 4);
				components::checkbox("Power Drills", &power_drills, [] { power_drills ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 4) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 4); });
				
				static bool emp_device = false;
				emp_device = misc::has_bit_set(&h3opt_bitset0, 5);
				components::checkbox("Emp Device - Silent & Sneaky", &emp_device, [] { emp_device ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 5) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 5); });
				
				static bool decoy_gunman = false;
				decoy_gunman = misc::has_bit_set(&h3opt_bitset0, 6);
				components::checkbox("Decoy Gunman", &decoy_gunman, [] { decoy_gunman ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 6) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 6); });
				
				static bool clean_vehicle = false;
				clean_vehicle = misc::has_bit_set(&h3opt_bitset0, 7);
				components::checkbox("Clean Vehicle", &clean_vehicle, [] { clean_vehicle ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 7) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 7); });
				
				static bool bugstars_gear = false;
				bugstars_gear = misc::has_bits_set(&h3opt_bitset0, 8, 9);
				components::checkbox("Entry Disguise - Bugstars Gear - The Big Con", &bugstars_gear, [] { bugstars_gear ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 8, 9) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 8, 9); });
				
				static bool maintenance_gear = false;
				maintenance_gear = misc::has_bits_set(&h3opt_bitset0, 10, 11);
				components::checkbox("Entry Disguise - Maintenance Gear - The Big Con", &maintenance_gear, [] { maintenance_gear ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 10, 11) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 10, 11); });
				
				static bool gruppe_sechs_gear = false;
				gruppe_sechs_gear = misc::has_bits_set(&h3opt_bitset0, 12, 13);
				components::checkbox("Entry Disguise - Gruppe Sechs Gear - The Big Con", &gruppe_sechs_gear, [] { gruppe_sechs_gear ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 12, 13) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 12, 13); });
				
				static bool after_party = false;
				after_party = misc::has_bits_set(&h3opt_bitset0, 14, 15);
				components::checkbox("Entry Disguise - After Party - The Big Con", &after_party, [] { after_party ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 14, 15) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 14, 15); });
				
				static bool noose_gear = false;
				noose_gear = misc::has_bit_set(&h3opt_bitset0, 16);
				components::checkbox("Exit Disguise - Noose Gear - The Big Con", &noose_gear, [] { noose_gear ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 16) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 16); });
				
				static bool firefighter_gear = false;
				firefighter_gear = misc::has_bit_set(&h3opt_bitset0, 17);
				components::checkbox("Exit Disguise - Firefighter Gear - The Big Con", &firefighter_gear, [] { firefighter_gear ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 17) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 17); });
				
				static bool tunnel_boring_machine = false;
				tunnel_boring_machine = misc::has_bit_set(&h3opt_bitset0, 19);
				components::checkbox("Tunnel Boring Machine - Aggressive", &tunnel_boring_machine, [] { tunnel_boring_machine ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 19) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 19); });
				
				static bool reinforced_armor = false;
				reinforced_armor = misc::has_bit_set(&h3opt_bitset0, 20);
				components::checkbox("Reinforced Armor - Aggressive", &reinforced_armor, [] { reinforced_armor ? local_player::stat_set_bits("$MPX_H3OPT_BITSET0", 20) : local_player::stat_clear_bits("$MPX_H3OPT_BITSET0", 20); });
				
				ImGui::EndGroup();
			}
				break;
			case TUNABLE:
			{
				if (*g_pointers->m_script_globals)
				{
					ImGui::InputInt("Crew Cut 1", script_global(heist::casino::crew_cut + 0).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 2", script_global(heist::casino::crew_cut + 1).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 3", script_global(heist::casino::crew_cut + 2).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 4", script_global(heist::casino::crew_cut + 3).as<int*>(), 0);

					ImGui::Separator();

					ImGui::InputFloat("Multiplier Normal", script_global(heist::casino::multiplier_normal).as<float*>());
					ImGui::InputFloat("Multiplier Hard", script_global(heist::casino::multiplier_hard).as<float*>());
					ImGui::InputFloat("Buyer Multiplier Easy", script_global(heist::casino::buyer_multiplier_easy).as<float*>());
					ImGui::InputFloat("Buyer Multiplier Normal", script_global(heist::casino::buyer_multiplier_normal).as<float*>());
					ImGui::InputFloat("Buyer Multiplier Hard", script_global(heist::casino::buyer_multiplier_hard).as<float*>());

					ImGui::Separator();

					ImGui::InputInt("Lester Cut", script_global(heist::casino::lester_cut).as<int*>(), 0);

					ImGui::Separator();

					static const char* targets[] = { "Cash", "Gold", "Artwork", "Diamonds" };
					for (int i = 0; i < IM_ARRAYSIZE(targets); i++)
						ImGui::InputInt(std::format("{} Value", targets[i]).c_str(), script_global(heist::casino::target_value + i).as<int*>(), 0);

					ImGui::Separator();

					static const char* ais[] = { "Karl Abolaji", "Gustavo Mota", "Charlie Reed", "Chester McCoy", "Patrick McReary", "Karim Denz", "Taliana Martinez", "Eddie Toh", "Zach Nelson", "Chester McCoy", "Rickie Lukens", "Christian Feltz", "Yohan Blair", "Avi Schwartzman", "Paige Harris" };
					for (int i = 0; i < IM_ARRAYSIZE(ais); i++)
						ImGui::InputInt(std::format("{} Cut", ais[i]).c_str(), script_global(heist::casino::ai_cut + i).as<int*>(), 0);
				}
				else
				{
					ImGui::Text("Waiting for the game to initialize");
				}
			}
				break;
			case TELEPORT:
			{
				ImGui::BeginGroup();
				components::button("Staff Lobby", [] { teleport::to_coords({ 2548.080566, -271.7148438, -58.72298813 }); });
				components::button("Basement", [] { teleport::to_coords({ 2526.33374, -279.2503357, -70.64446259 }); });
				components::button("Keypads", [] { teleport::to_coords({ 2468.846436, -279.2178955, -70.69423676 }); });
				ImGui::EndGroup(); ImGui::SameLine();
				ImGui::BeginGroup();
				components::button("Mantrap", [] { teleport::to_coords({ 2423.513916 , -258.9893799 , -70.80651093 }); });
				components::button("Vault Door - Outside", [] { teleport::to_coords({ 2497.277588, -239.3405457, -70.73901367 }); });
				components::button("Vault Door - Inside", [] { teleport::to_coords({ 2510.670898, -239.0809784, -70.73706818 }); });
				ImGui::EndGroup();
			}
				break;
			case MISC:
			{
				if (auto thread = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller")); thread)
				{
					scripts::force_host(RAGE_JOAAT("fm_mission_controller"));
					ImGui::InputInt("Take", script_local(thread, heist::casino::take).as<int*>(), 0);
					ImGui::InputInt("Team Lives", script_local(thread, heist::casino::team_lives).as<int*>(), 0);
				}
				components::button("Instant Heist Passed", [] { heist::casino::instant_heist_passed(); });
				components::button("Hack Fingerprint", [] { heist::casino::hack_fingerprint(); });
				components::button("Hack Keypad", [] { heist::casino::hack_keypad(); });
				components::button("Break Vault Door", [] { heist::casino::break_vault_door(); });
			}
				break;
			}

			ImGui::EndTabItem();
		}
	}

	static int dh_radio_button_index = 0;
	static void tab_item_doomsday_heist()
	{
		if (ImGui::BeginTabItem("Doomsday Heist"))
		{
			enum Mode
			{
				PREP,
				TUNABLE
			};

			ImGui::RadioButton("Prep", &dh_radio_button_index, PREP); ImGui::SameLine();
			ImGui::RadioButton("Tunable", &dh_radio_button_index, TUNABLE);

			switch (dh_radio_button_index)
			{
			case PREP:
			{
				components::button("Start Heist Finale - The Data Breaches", [] //https://www.unknowncheats.me/forum/3011256-post1.html
				{
					local_player::stat_set_int("$MPX_GANGOPS_FLOW_MISSION_PROG", 503);
					local_player::stat_set_int("$MPX_GANGOPS_HEIST_STATUS", 229383);
					local_player::stat_set_int("$MPX_GANGOPS_FLOW_NOTIFICATIONS", 1557);
				});
				components::button("Start Heist Finale - The Bogdan Problem", [] 
				{
					local_player::stat_set_int("$MPX_GANGOPS_FLOW_MISSION_PROG", 240);
					local_player::stat_set_int("$MPX_GANGOPS_HEIST_STATUS", 229378);
					local_player::stat_set_int("$MPX_GANGOPS_FLOW_NOTIFICATIONS", 1557);
				});
				components::button("Start Heist Finale - The Doomsday Scenario", [] 
				{
					local_player::stat_set_int("$MPX_GANGOPS_FLOW_MISSION_PROG", 16368);
					local_player::stat_set_int("$MPX_GANGOPS_HEIST_STATUS", 229380);
					local_player::stat_set_int("$MPX_GANGOPS_FLOW_NOTIFICATIONS", 1557);
				});
			}
				break;
			case TUNABLE:
			{
				if (*g_pointers->m_script_globals)
				{
					ImGui::InputInt("Crew Cut 1", script_global(heist::doomsday::crew_cut + 0).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 2", script_global(heist::doomsday::crew_cut + 1).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 3", script_global(heist::doomsday::crew_cut + 2).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 4", script_global(heist::doomsday::crew_cut + 3).as<int*>(), 0);

					ImGui::Separator();

					static const char* heists[] = { "The Data Breaches", "The Bogdan Problem", "The Doomsday Scenario" };
					for (int i = 0; i < IM_ARRAYSIZE(heists); i++)
						ImGui::InputInt(std::format("{} Reward", heists[i]).c_str(), script_global(heist::doomsday::target_value + i).as<int*>(), 0);

					ImGui::Separator();

					ImGui::InputFloat("Multiplier Normal", script_global(heist::doomsday::multiplier_normal).as<float*>());
					ImGui::InputFloat("Multiplier Hard", script_global(heist::doomsday::multiplier_hard).as<float*>());
				}
				else
				{
					ImGui::Text("Waiting for the game to initialize");
				}
			}
				break;
			}

			ImGui::EndTabItem();
		}
	}

	static int ah_radio_button_index = 0;
	static int heist_planning_stage = 0;
	static void tab_item_apart_heist()
	{
		if (ImGui::BeginTabItem("Apartment Heist"))
		{
			ImGui::Text("Reward Limit: 15M");

			enum Mode
			{
				PREP,
				TUNABLE
			};

			ImGui::RadioButton("Prep", &ah_radio_button_index, PREP); ImGui::SameLine();
			ImGui::RadioButton("Tunable", &ah_radio_button_index, TUNABLE);

			switch (ah_radio_button_index)
			{
			case PREP:
			{
				components::button("Unlock All Heists", [] //https://www.unknowncheats.me/forum/2399940-post513.html
				{
					local_player::stat_set_bool("MPPLY_AWD_COMPLET_HEIST_1STPER", true);
					local_player::stat_set_bool("MPPLY_AWD_COMPLET_HEIST_MEM", true);
					local_player::stat_set_bool("MPPLY_AWD_FLEECA_FIN", true);
					local_player::stat_set_bool("MPPLY_AWD_PRISON_FIN", true);
					local_player::stat_set_bool("MPPLY_AWD_HUMANE_FIN", true);
					local_player::stat_set_bool("MPPLY_AWD_SERIESA_FIN", true);
					local_player::stat_set_bool("MPPLY_AWD_PACIFIC_FIN", true);
					local_player::stat_set_bool("MPPLY_AWD_HST_ORDER", true);
					local_player::stat_set_bool("MPPLY_AWD_HST_SAME_TEAM", true);
					local_player::stat_set_bool("MPPLY_AWD_HST_ULT_CHAL", true);
					local_player::stat_set_int("MPPLY_HEIST_ACH_TRACKER ", -1);
				});

				ImGui::Text("Edit after paying 25K to start the heist");

				static bool prep1 = false;
				prep1 = misc::has_bit_set(&heist_planning_stage, 0 * 3);
				components::checkbox("Prep 1", &prep1, [] { prep1 ? local_player::stat_set_bits("$MPX_HEIST_PLANNING_STAGE", 0 * 3) : local_player::stat_clear_bits("$MPX_HEIST_PLANNING_STAGE", 0 * 3); });

				static bool prep2 = false;
				prep2 = misc::has_bit_set(&heist_planning_stage, 1 * 3);
				components::checkbox("Prep 2", &prep2, [] { prep2 ? local_player::stat_set_bits("$MPX_HEIST_PLANNING_STAGE", 1 * 3) : local_player::stat_clear_bits("$MPX_HEIST_PLANNING_STAGE", 1 * 3); });

				static bool prep3 = false;
				prep3 = misc::has_bit_set(&heist_planning_stage, 2 * 3);
				components::checkbox("Prep 3", &prep3, [] { prep3 ? local_player::stat_set_bits("$MPX_HEIST_PLANNING_STAGE", 2 * 3) : local_player::stat_clear_bits("$MPX_HEIST_PLANNING_STAGE", 2 * 3); });

				static bool prep4 = false;
				prep4 = misc::has_bit_set(&heist_planning_stage, 3 * 3);
				components::checkbox("Prep 4", &prep4, [] { prep4 ? local_player::stat_set_bits("$MPX_HEIST_PLANNING_STAGE", 3 * 3) : local_player::stat_clear_bits("$MPX_HEIST_PLANNING_STAGE", 3 * 3); });

				static bool prep5 = false;
				prep5 = misc::has_bit_set(&heist_planning_stage, 4 * 3);
				components::checkbox("Prep 5", &prep5, [] { prep5 ? local_player::stat_set_bits("$MPX_HEIST_PLANNING_STAGE", 4 * 3) : local_player::stat_clear_bits("$MPX_HEIST_PLANNING_STAGE", 4 * 3); });
			}
				break;
			case TUNABLE:
			{
				if (*g_pointers->m_script_globals)
				{
					ImGui::InputInt("Crew Cut 1", script_global(heist::apart::crew_cut + 0).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 2", script_global(heist::apart::crew_cut + 1).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 3", script_global(heist::apart::crew_cut + 2).as<int*>(), 0);
					ImGui::InputInt("Crew Cut 4", script_global(heist::apart::crew_cut + 3).as<int*>(), 0);

					ImGui::Separator();

					static const char* heists[] = { "The Fleeca Job", "The Prison Break", "The Humane Labs Raid", "Series A Funding", "The Pacific Standard" };
					for (int i = 0; i < IM_ARRAYSIZE(heists); i++)
						ImGui::InputInt(std::format("{} Reward", heists[i]).c_str(), script_global(heist::apart::target_value + i).as<int*>(), 0);

					ImGui::Separator();

					ImGui::InputFloat("Multiplier Easy", script_global(heist::apart::multiplier_easy).as<float*>());
					ImGui::InputFloat("Multiplier Normal", script_global(heist::apart::multiplier_normal).as<float*>());
					ImGui::InputFloat("Multiplier Hard", script_global(heist::apart::multiplier_hard).as<float*>());
				}
				else
				{
					ImGui::Text("Waiting for the game to initialize");
				}
			}
				break;
			}

			ImGui::EndTabItem();
		}
	}

	static int asc_radio_button_index = 0;
	static int tuner_current = 0;
	static int tuner_gen_bs = 0;
	static void tab_item_auto_shop_contracts()
	{
		if (ImGui::BeginTabItem("Auto Shop Contracts"))
		{
			enum Mode
			{
				PREP,
				TUNABLE
			};

			ImGui::RadioButton("Prep", &asc_radio_button_index, PREP); ImGui::SameLine();
			ImGui::RadioButton("Tunable", &asc_radio_button_index, TUNABLE);

			switch (asc_radio_button_index)
			{
			case PREP:
			{
				static const char* contracts[] = { "The Union Depository Contract", "The Superdollar Deal", "The Bank Contract", "The E.C.U Job", "The Prison Contract", "The Agency Deal", "The Lost Contract", "The Data Contract" };
				components::combo("Selected Contract", &tuner_current, contracts, IM_ARRAYSIZE(contracts), [] { local_player::stat_set_int("$MPX_TUNER_CURRENT", tuner_current); });

				static bool prep1 = false;
				prep1 = misc::has_bit_set(&tuner_gen_bs, 2);
				components::checkbox("Prep 1", &prep1, [] { prep1 ? local_player::stat_set_bits("$MPX_TUNER_GEN_BS", 2) : local_player::stat_clear_bits("$MPX_TUNER_GEN_BS", 2); });

				static bool prep2 = false;
				prep2 = misc::has_bit_set(&tuner_gen_bs, 3);
				components::checkbox("Prep 2", &prep2, [] { prep2 ? local_player::stat_set_bits("$MPX_TUNER_GEN_BS", 3) : local_player::stat_clear_bits("$MPX_TUNER_GEN_BS", 3); });
			}
				break;
			case TUNABLE:
			{
				if (*g_pointers->m_script_globals)
				{
					static const char* contracts[] = { "The Union Depository Contract", "The Superdollar Deal", "The Bank Contract", "The E.C.U Job", "The Prison Contract", "The Agency Deal", "The Lost Contract", "The Data Contract" };
					for (int i = 0; i < IM_ARRAYSIZE(contracts); i++)
						ImGui::InputInt(std::format("{} Reward", contracts[i]).c_str(), script_global(heist::auto_shop_contracts::contract_reward + i).as<int*>(), 0);
				}
				else
				{
					ImGui::Text("Waiting for the game to initialize");
				}
			}
				break;
			}

			ImGui::EndTabItem();
		}
	}

	static int avc_radio_button_index = 0;
	static int fixer_general_bs = 0;
	static int fixer_story_bs = 0;
	static void tab_item_agency_vip_contract()
	{
		if (ImGui::BeginTabItem("Agency Vip Contract"))
		{
			enum Mode
			{
				PREP,
				TUNABLE
			};

			ImGui::RadioButton("Prep", &avc_radio_button_index, PREP); ImGui::SameLine();
			ImGui::RadioButton("Tunable", &avc_radio_button_index, TUNABLE);

			switch (avc_radio_button_index)
			{
			case PREP:
			{
				static bool archive = false;
				archive = misc::has_bit_set(&fixer_general_bs, 2);
				components::checkbox("Archive", &archive, [] { archive ? local_player::stat_set_bits("$MPX_FIXER_GENERAL_BS", 2) : local_player::stat_clear_bits("$MPX_FIXER_GENERAL_BS", 2); });

				ImGui::Separator();

				static bool the_meet = false;
				the_meet = misc::has_bit_set(&fixer_story_bs, 0);
				components::checkbox("The Meet", &the_meet, [] { the_meet ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 0) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 0); });

				static bool data_recovery = false;
				data_recovery = misc::has_bit_set(&fixer_story_bs, 1);
				components::checkbox("Data Recovery", &data_recovery, [] { data_recovery ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 1) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 1); });

				static bool the_nightclub = false;
				the_nightclub = misc::has_bit_set(&fixer_story_bs, 2);
				components::checkbox("Nightlife Leak - The Nightclub", &the_nightclub, [] { the_nightclub ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 2) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 2); });

				static bool the_marina = false;
				the_marina = misc::has_bit_set(&fixer_story_bs, 3);
				components::checkbox("Nightlife Leak - The Marina", &the_marina, [] { the_marina ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 3) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 3); });

				static bool nightlife_leak = false;
				nightlife_leak = misc::has_bit_set(&fixer_story_bs, 4);
				components::checkbox("Nightlife Leak", &nightlife_leak, [] { nightlife_leak ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 4) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 4); });

				static bool the_country_club = false;
				the_country_club = misc::has_bit_set(&fixer_story_bs, 5);
				components::checkbox("High Society Leak - The Country Club", &the_country_club, [] { the_country_club ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 5) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 5); });

				static bool guest_life = false;
				guest_life = misc::has_bit_set(&fixer_story_bs, 6);
				components::checkbox("High Society Leak - Guest List", &guest_life, [] { guest_life ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 6) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 6); });

				static bool high_society_leak = false;
				high_society_leak = misc::has_bit_set(&fixer_story_bs, 7);
				components::checkbox("High Society Leak", &high_society_leak, [] { high_society_leak ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 7) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 7); });

				static bool davis = false;
				davis = misc::has_bit_set(&fixer_story_bs, 8);
				components::checkbox("South Central Leak - Davis", &davis, [] { davis ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 8) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 8); });

				static bool the_ballas = false;
				the_ballas = misc::has_bit_set(&fixer_story_bs, 9);
				components::checkbox("South Central Leak - The Ballas", &the_ballas, [] { the_ballas ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 9) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 9); });

				static bool south_central_leak = false;
				south_central_leak = misc::has_bit_set(&fixer_story_bs, 10);
				components::checkbox("South Central Leak", &south_central_leak, [] { south_central_leak ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 10) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 10); });

				static bool studio_time = false;
				studio_time = misc::has_bit_set(&fixer_story_bs, 11);
				components::checkbox("Studio Time", &studio_time, [] { studio_time ? local_player::stat_set_bits("$MPX_FIXER_STORY_BS", 11) : local_player::stat_clear_bits("$MPX_FIXER_STORY_BS", 11); });
			}
				break;
			case TUNABLE:
			{
				if (*g_pointers->m_script_globals)
				{
					ImGui::InputInt("Don't Fuck With Dre Reward", script_global(heist::agency_vip_contract::contract_reward).as<int*>(), 0);
				}
				else
				{
					ImGui::Text("Waiting for the game to initialize");
				}
			}
				break;
			}

			ImGui::EndTabItem();
		}
	}

	void view::heist_editor()
	{
		g_fiber_pool->queue_job([] 
		{
			h4_playthrough_status = local_player::stat_get_int("$MPX_H4_PLAYTHROUGH_STATUS");
			h4cnf_approach = local_player::stat_get_int("$MPX_H4CNF_APPROACH");
			h4cnf_bs_entr = local_player::stat_get_int("$MPX_H4CNF_BS_ENTR");
			h4cnf_target = local_player::stat_get_int("$MPX_H4CNF_TARGET");
			h4_progress = local_player::stat_get_int("$MPX_H4_PROGRESS");
			h4loot_cash_v = local_player::stat_get_int("$MPX_H4LOOT_CASH_V");
			h4loot_weed_v = local_player::stat_get_int("$MPX_H4LOOT_WEED_V");
			h4loot_coke_v = local_player::stat_get_int("$MPX_H4LOOT_COKE_V");
			h4loot_gold_v = local_player::stat_get_int("$MPX_H4LOOT_GOLD_V");
			h4loot_paint_v = local_player::stat_get_int("$MPX_H4LOOT_PAINT_V");
			h4loot_cash_i = local_player::stat_get_int("$MPX_H4LOOT_CASH_I");
			h4loot_weed_i = local_player::stat_get_int("$MPX_H4LOOT_WEED_I");
			h4loot_coke_i = local_player::stat_get_int("$MPX_H4LOOT_COKE_I");
			h4loot_gold_i = local_player::stat_get_int("$MPX_H4LOOT_GOLD_I");
			h4loot_cash_i_scoped = local_player::stat_get_int("$MPX_H4LOOT_CASH_I_SCOPED");
			h4loot_weed_i_scoped = local_player::stat_get_int("$MPX_H4LOOT_WEED_I_SCOPED");
			h4loot_coke_i_scoped = local_player::stat_get_int("$MPX_H4LOOT_COKE_I_SCOPED");
			h4loot_gold_i_scoped = local_player::stat_get_int("$MPX_H4LOOT_GOLD_I_SCOPED");
			h4loot_cash_c = local_player::stat_get_int("$MPX_H4LOOT_CASH_C");
			h4loot_weed_c = local_player::stat_get_int("$MPX_H4LOOT_WEED_C");
			h4loot_coke_c = local_player::stat_get_int("$MPX_H4LOOT_COKE_C");
			h4loot_gold_c = local_player::stat_get_int("$MPX_H4LOOT_GOLD_C");
			h4loot_cash_c_scoped = local_player::stat_get_int("$MPX_H4LOOT_CASH_C_SCOPED");
			h4loot_weed_c_scoped = local_player::stat_get_int("$MPX_H4LOOT_WEED_C_SCOPED");
			h4loot_coke_c_scoped = local_player::stat_get_int("$MPX_H4LOOT_COKE_C_SCOPED");
			h4loot_gold_c_scoped = local_player::stat_get_int("$MPX_H4LOOT_GOLD_C_SCOPED");
			h4loot_paint = local_player::stat_get_int("$MPX_H4LOOT_PAINT");
			h4loot_paint_scoped = local_player::stat_get_int("$MPX_H4LOOT_PAINT_SCOPED");
			h4cnf_grappel = local_player::stat_get_int("$MPX_H4CNF_GRAPPEL");
			h4cnf_uniform = local_player::stat_get_int("$MPX_H4CNF_UNIFORM");
			h4cnf_boltcut = local_player::stat_get_int("$MPX_H4CNF_BOLTCUT");
			h4cnf_trojan = local_player::stat_get_int("$MPX_H4CNF_TROJAN");
			h4cnf_bs_gen = local_player::stat_get_int("$MPX_H4CNF_BS_GEN");
			h4cnf_weapons = local_player::stat_get_int("$MPX_H4CNF_WEAPONS");
			h4_missions = local_player::stat_get_int("$MPX_H4_MISSIONS");
			h4cnf_bs_abil = local_player::stat_get_int("$MPX_H4CNF_BS_ABIL");

			cas_heist_flow = local_player::stat_get_int("$MPX_CAS_HEIST_FLOW");
			h3opt_target = local_player::stat_get_int("$MPX_H3OPT_TARGET");
			h3opt_bitset1 = local_player::stat_get_int("$MPX_H3OPT_BITSET1");
			h3opt_approach = local_player::stat_get_int("$MPX_H3OPT_APPROACH");
			h3_last_approach = local_player::stat_get_int("$MPX_H3_LAST_APPROACH");
			h3_hard_approach = local_player::stat_get_int("$MPX_H3_HARD_APPROACH");
			h3opt_crewweap = local_player::stat_get_int("$MPX_H3OPT_CREWWEAP");
			h3opt_crewdriver = local_player::stat_get_int("$MPX_H3OPT_CREWDRIVER");
			h3opt_crewhacker = local_player::stat_get_int("$MPX_H3OPT_CREWHACKER");
			h3opt_vehs = local_player::stat_get_int("$MPX_H3OPT_VEHS");
			h3opt_weaps = local_player::stat_get_int("$MPX_H3OPT_WEAPS");
			h3opt_bitset0 = local_player::stat_get_int("$MPX_H3OPT_BITSET0");
			h3opt_keylevels = local_player::stat_get_int("$MPX_H3OPT_KEYLEVELS");

			heist_planning_stage = local_player::stat_get_int("$MPX_HEIST_PLANNING_STAGE");

			tuner_current = local_player::stat_get_int("$MPX_TUNER_CURRENT");
			tuner_gen_bs = local_player::stat_get_int("$MPX_TUNER_GEN_BS");

			fixer_general_bs = local_player::stat_get_int("$MPX_FIXER_GENERAL_BS");
			fixer_story_bs = local_player::stat_get_int("$MPX_FIXER_STORY_BS");
		});

		if (ImGui::BeginTabBar("##heist_editor_tab_bar"))
		{
			tab_item_cayo_perico_heist();
			tab_item_diamond_casino_heist();
			tab_item_doomsday_heist();
			tab_item_apart_heist();
			tab_item_auto_shop_contracts();
			tab_item_agency_vip_contract();
			ImGui::EndTabBar();
		}
	}
}