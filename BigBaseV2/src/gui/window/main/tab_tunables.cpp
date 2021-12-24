#include "main_tabs.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "script_local.hpp"
#include "common.hpp"
#include "fiber_pool.hpp"
#include "gta/player.hpp"
#include "gta_util.hpp"

namespace big
{
	void notification1(const std::string& text)
	{
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::THEFEED_SET_NEXT_POST_BACKGROUND_COLOR_(184);
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const_cast<char*>(text.c_str()));
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}

	void notification_error1(const std::string& text)
	{
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::THEFEED_SET_NEXT_POST_BACKGROUND_COLOR_(6);
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const_cast<char*>(text.c_str()));
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}

	int character1() {
		//CurrentMPChar = 1312763
		return *script_global(1312763).as<int*>();
	}
	void tab_main::tab_tunables()
	{
		if (ImGui::BeginTabItem("Tunables"))
		{
			ImGui::Checkbox("Disable Phone", &g.tunables.disable_phone);
			ImGui::Checkbox("No Idle Kick", &g.tunables.no_idle_kick);


			if (ImGui::BeginMenu("Heist Helper")) {

				if (ImGui::BeginMenu("Casino Heist")) {

					if (ImGui::BeginMenu("Approach Type")) {

						if (ImGui::Button("1 - Stealth")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_APPROACH"), 1, TRUE);
									notification1("Approach Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_APPROACH"), 1, TRUE);
									notification1("Approach Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("2 - Trickery")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_APPROACH"), 2, TRUE);
									notification1("Approach Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_APPROACH"), 2, TRUE);
									notification1("Approach Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("3 - Loud")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_APPROACH"), 3, TRUE);
									notification1("Approach Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_APPROACH"), 3, TRUE);
									notification1("Approach Set!");
								}
								});
						}

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Heist Target")) {

						if (ImGui::Button("0 - Money")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_TARGET"), 0, TRUE);
									notification1("Target Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_TARGET"), 0, TRUE);
									notification1("Target Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("1 - Gold")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_TARGET"), 1, TRUE);
									notification1("Target Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_TARGET"), 1, TRUE);
									notification1("Target Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("2 - Art")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_TARGET"), 2, TRUE);
									notification1("Target Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_TARGET"), 2, TRUE);
									notification1("Target Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("3 - Diamond")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_TARGET"), 3, TRUE);
									notification1("Target Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_TARGET"), 3, TRUE);
									notification1("Target Set!");
								}
								});
						}

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Disrupt Ship")) {

						if (ImGui::Button("Level 0 (None)")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_DISRUPTSHIP"), 0, TRUE);
									notification1("Disrupt Ship Level Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_DISRUPTSHIP"), 0, TRUE);
									notification1("Disrupt Ship Level Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("Level 1")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_DISRUPTSHIP"), 1, TRUE);
									notification1("Disrupt Ship Level Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_DISRUPTSHIP"), 1, TRUE);
									notification1("Disrupt Ship Level Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("Level 2")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_DISRUPTSHIP"), 2, TRUE);
									notification1("Disrupt Ship Level Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_DISRUPTSHIP"), 2, TRUE);
									notification1("Disrupt Ship Level Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("Level 3")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_DISRUPTSHIP"), 3, TRUE);
									notification1("Disrupt Ship Level Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_DISRUPTSHIP"), 3, TRUE);
									notification1("Disrupt Ship Level Set!");
								}
								});
						}

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Access Keys Level")) {

						if (ImGui::Button("Level 0 (None)")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_KEYLEVELS"), 0, TRUE);
									notification1("Key Level Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_KEYLEVELS"), 0, TRUE);
									notification1("Key Level Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("Level 1")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_KEYLEVELS"), 1, TRUE);
									notification1("Key Level Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_KEYLEVELS"), 1, TRUE);
									notification1("Key Level Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("Level 2")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_KEYLEVELS"), 2, TRUE);
									notification1("Key Level Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_KEYLEVELS"), 2, TRUE);
									notification1("Key Level Set!");
								}
								});
						}

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Body Armor Levels")) {

						if (ImGui::Button("Level 0 (None)")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_BODYARMORLVL"), 0, TRUE);
									notification1("Body Armor Level Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_BODYARMORLVL"), 0, TRUE);
									notification1("Body Armor Level Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("Level 1")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_BODYARMORLVL"), 1, TRUE);
									notification1("Body Armor Level Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_BODYARMORLVL"), 1, TRUE);
									notification1("Body Armor Level Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("Level 2")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_BODYARMORLVL"), 2, TRUE);
									notification1("Body Armor Level Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_BODYARMORLVL"), 2, TRUE);
									notification1("Body Armor Level Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("Level 3")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_BODYARMORLVL"), 3, TRUE);
									notification1("Body Armor Level Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_BODYARMORLVL"), 3, TRUE);
									notification1("Body Armor Level Set!");
								}
								});
						}

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Weapon Crew Team")) {

						if (ImGui::Button("1 - Karl Abolaji")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWWEAP"), 1, TRUE);
									notification1("Weapon Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWWEAP"), 1, TRUE);
									notification1("Weapon Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("2 - Gustavo Motta")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWWEAP"), 2, TRUE);
									notification1("Weapon Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWWEAP"), 2, TRUE);
									notification1("Weapon Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("3 - Charlie Reed")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWWEAP"), 3, TRUE);
									notification1("Weapon Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWWEAP"), 3, TRUE);
									notification1("Weapon Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("4 - Chester McCoy")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWWEAP"), 4, TRUE);
									notification1("Weapon Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWWEAP"), 4, TRUE);
									notification1("Weapon Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("5 - Patrick McReary")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWWEAP"), 5, TRUE);
									notification1("Weapon Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWWEAP"), 5, TRUE);
									notification1("Weapon Crew Team Set!");
								}
								});
						}

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Driver Crew Team")) {

						if (ImGui::Button("1 - Karim Deniz")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWDRIVER"), 1, TRUE);
									notification1("Driver Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWDRIVER"), 1, TRUE);
									notification1("Driver Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("2 - Taliana Martinez")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWDRIVER"), 2, TRUE);
									notification1("Driver Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWDRIVER"), 2, TRUE);
									notification1("Driver Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("3 - Eddie Toh")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWDRIVER"), 3, TRUE);
									notification1("Driver Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWDRIVER"), 3, TRUE);
									notification1("Driver Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("4 - Zach Nelson")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWDRIVER"), 4, TRUE);
									notification1("Driver Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWDRIVER"), 4, TRUE);
									notification1("Driver Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("5 - Chester McCoy")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWDRIVER"), 5, TRUE);
									notification1("Driver Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWDRIVER"), 5, TRUE);
									notification1("Driver Crew Team Set!");
								}
								});
						}

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Hacker Crew Team")) {

						if (ImGui::Button("1 - Rickie Lukens")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWHACKER"), 1, TRUE);
									notification1("Hacker Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWHACKER"), 1, TRUE);
									notification1("Hacker Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("2 - Christian Feltz")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWHACKER"), 2, TRUE);
									notification1("Hacker Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWHACKER"), 2, TRUE);
									notification1("Hacker Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("3 - Yohan Blair")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWHACKER"), 3, TRUE);
									notification1("Hacker Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWHACKER"), 3, TRUE);
									notification1("Hacker Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("4 - Avi Schwartzman")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWHACKER"), 4, TRUE);
									notification1("Hacker Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWHACKER"), 4, TRUE);
									notification1("Hacker Crew Team Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("5 - Page Harris")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWHACKER"), 5, TRUE);
									notification1("Hacker Crew Team Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWHACKER"), 5, TRUE);
									notification1("Hacker Crew Team Set!");
								}
								});
						}

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Heist Vehicles")) {

						if (ImGui::Button("Kit #1")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_VEHS"), 0, TRUE);
									notification1("Vehicle Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_VEHS"), 0, TRUE);
									notification1("Vehicle Kit Set!");
								}
								});
						}

						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Includes: Issi Classic, Retinue MK II, Sultan Classic, Manchez, Zhaba");

						ImGui::Separator();

						if (ImGui::Button("Kit #2")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_VEHS"), 1, TRUE);
									notification1("Vehicle Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_VEHS"), 1, TRUE);
									notification1("Vehicle Kit Set!");
								}
								});
						}

						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Includes: Asbo, Drift Yosemite, Guantlet Classic, Stryder, Vagrant");

						ImGui::Separator();

						if (ImGui::Button("Kit #3")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_VEHS"), 2, TRUE);
									notification1("Vehicle Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_VEHS"), 2, TRUE);
									notification1("Vehicle Kit Set!");
								}
								});
						}

						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Includes: Kanjo, Sugoi, Ellie, Defiler, Outlaw");

						ImGui::Separator();

						if (ImGui::Button("Kit #4")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_VEHS"), 3, TRUE);
									notification1("Vehicle Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_VEHS"), 3, TRUE);
									notification1("Vehicle Kit Set!");
								}
								});
						}

						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Includes: Sentinel Classic, Jugular, Komoda, Lectro, Everon");

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Heist Weapons")) {

						if (ImGui::Button("Kit #1")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_WEAPS"), 0, TRUE);
									notification1("Heist Weapon Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_WEAPS"), 0, TRUE);
									notification1("Heist Weapon Kit Set!");
								}
								});
						}

						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Includes: Shotgun, Rifle, SMG, SMG MK II, Shotgun");

						ImGui::Separator();

						if (ImGui::Button("Kit #2")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_WEAPS"), 1, TRUE);
									notification1("Heist Weapon Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_WEAPS"), 1, TRUE);
									notification1("Heist Weapon Kit Set!");
								}
								});
						}

						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Includes: Revolver, Shotgun, Shotgun, Rifle MK II, Combat MG");

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Heist Masks")) {

						if (ImGui::Button("1 - Geometric Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 1, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 1, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("2 - Hunter Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 2, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 2, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("3 - Oni Half Mask Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 3, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 3, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("4 - Emoji Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 4, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 4, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("5 - Ornate Skull Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 5, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 5, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("6 - Lucky Fruit Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 6, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 6, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("7 - Gurilla Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 7, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 7, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("8 - Clown Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 8, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 8, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("9 - Animal Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 9, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 9, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("10 - Riot Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 10, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 10, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("11 - Oni Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 11, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 11, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("12 - Hockey Set")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_MASKS"), 12, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_MASKS"), 12, TRUE);
									notification1("Heist Masks Kit Set!");
								}
								});
						}

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Hard Approach/Last Approach")) {

						if (ImGui::BeginMenu("Hard Approach")) {

							if (ImGui::Button("1 - Stealth")) {
								g_fiber_pool->queue_job([] {
									if (character1() == 0) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3_HARD_APPROACH"), 1, TRUE);
										notification1("Hard Approach Set!");
									}
									if (character1() == 1) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3_HARD_APPROACH"), 1, TRUE);
										notification1("Hard Approach Set!");
									}
									});
							}

							ImGui::Separator();

							if (ImGui::Button("2 - Trickery")) {
								g_fiber_pool->queue_job([] {
									if (character1() == 0) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3_HARD_APPROACH"), 2, TRUE);
										notification1("Hard Approach Set!");
									}
									if (character1() == 1) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3_HARD_APPROACH"), 2, TRUE);
										notification1("Hard Approach Set!");
									}
									});
							}

							ImGui::Separator();

							if (ImGui::Button("3 - Loud")) {
								g_fiber_pool->queue_job([] {
									if (character1() == 0) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3_HARD_APPROACH"), 3, TRUE);
										notification1("Hard Approach Set!");
									}
									if (character1() == 1) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3_HARD_APPROACH"), 3, TRUE);
										notification1("Hard Approach Set!");
									}
									});
							}

							ImGui::EndMenu();
						}

						ImGui::Separator();

						if (ImGui::BeginMenu("Last Approach")) {

							if (ImGui::Button("Reset Last Approach")) {
								g_fiber_pool->queue_job([] {
									if (character1() == 0) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3_LAST_APPROACH"), 0, TRUE);
										notification1("Last Approach Reset!");
									}
									if (character1() == 1) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3_LAST_APPROACH"), 0, TRUE);
										notification1("Last Approach Reset!");
									}
									});
							}

							ImGui::Separator();

							if (ImGui::Button("1 - Stealth")) {
								g_fiber_pool->queue_job([] {
									if (character1() == 0) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3_LAST_APPROACH"), 1, TRUE);
										notification1("Last Approach Set!");
									}
									if (character1() == 1) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3_LAST_APPROACH"), 1, TRUE);
										notification1("Last Approach Set!");
									}
									});
							}

							ImGui::Separator();

							if (ImGui::Button("2 - Trickery")) {
								g_fiber_pool->queue_job([] {
									if (character1() == 0) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3_LAST_APPROACH"), 2, TRUE);
										notification1("Last Approach Set!");
									}
									if (character1() == 1) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3_LAST_APPROACH"), 2, TRUE);
										notification1("Last Approach Set!");
									}
									});
							}

							ImGui::Separator();

							if (ImGui::Button("3 - Loud")) {
								g_fiber_pool->queue_job([] {
									if (character1() == 0) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3_LAST_APPROACH"), 3, TRUE);
										notification1("Last Approach Set!");
									}
									if (character1() == 1) {
										STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3_LAST_APPROACH"), 3, TRUE);
										notification1("Last Approach Set!");
									}
									});
							}

							ImGui::EndMenu();
						}

						ImGui::EndMenu();
					}

					ImGui::Separator();

					if (ImGui::BeginMenu("Misc Options")) {

						if (ImGui::Button("Skip the First Board")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_BITSET1"), -1, TRUE);
									notification1("Done!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_BITSET1"), -1, TRUE);
									notification1("Done!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("Skip the Second Board")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_BITSET0"), -1, TRUE);
									notification1("Done!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_BITSET0"), -1, TRUE);
									notification1("Done!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("Reset Heist Cooldown")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3_COMPLETEDPOSIX"), 1, TRUE);
									STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_H3_COOLDOWN"), 1, TRUE);
									notification1("Cooldown Reset!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3_COMPLETEDPOSIX"), 1, TRUE);
									STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_H3_COOLDOWN"), 1, TRUE);
									notification1("Cooldown Reset!");
								}
								});
						}

						ImGui::Separator();

						if (ImGui::Button("Remove Lester Cut")) {
							g_fiber_pool->queue_job([] {
								if (character1() == 0) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWWEAP"), 6, TRUE);
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWDRIVER"), 6, TRUE);
									STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H3OPT_CREWHACKER"), 6, TRUE);
									notification1("Stats Set!");
								}
								if (character1() == 1) {
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWWEAP"), 6, TRUE);
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWDRIVER"), 6, TRUE);
									STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H3OPT_CREWHACKER"), 6, TRUE);
									notification1("Stats Set!");
								}
								});
						}

						ImGui::EndMenu();
					}

					ImGui::EndMenu();
				}

				ImGui::Separator();

				if (ImGui::BeginMenu("Cayo Perico Heist")) {

					if (ImGui::Button("Skip Heist Prep")) {
						g_fiber_pool->queue_job([] {
							if (character1() == 0) {
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_BS_GEN"), 131071, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_WEAPONS"), 1, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_WEP_DISRP"), 3, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_ARM_DISRP"), 3, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_HEL_DISRP"), 3, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_TARGET"), 5, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_BOLTCUT"), 4424, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_UNIFORM"), 5256, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_GRAPPEL"), 5156, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4CNF_TROJAN"), 1, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_CASH_I"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_CASH_I_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_CASH_C"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_CASH_C_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_COKE_I"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_COKE_I_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_COKE_C"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_COKE_C_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_GOLD_I"), 16777215, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_GOLD_I_SCOPED"), 16777215, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_GOLD_C"), 255, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_GOLD_C_SCOPED"), 255, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_WEED_I"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_WEED_I_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_WEED_C"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_WEED_C_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_PAINT"), 127, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_PAINT_SCOPED"), 127, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_GOLD_V"), 598484, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4LOOT_PAINT_V"), 448863, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4_PROGRESS"), 124271, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4_MISSIONS"), 65535, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4_PLAYTHROUGH_STATUS"), 40000, TRUE);
								STATS::STAT_SAVE(0, 0, 3, 0);
								notification1("Done!");
							}
							if (character1() == 1) {
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4CNF_BS_GEN"), 131071, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4CNF_WEAPONS"), 1, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4CNF_WEP_DISRP"), 3, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4CNF_ARM_DISRP"), 3, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4CNF_HEL_DISRP"), 3, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4CNF_TARGET"), 5, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4CNF_BOLTCUT"), 4424, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4CNF_UNIFORM"), 5256, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4CNF_GRAPPEL"), 5156, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4CNF_TROJAN"), 1, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_CASH_I"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_CASH_I_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_CASH_C"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_CASH_C_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_COKE_I"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_COKE_I_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_COKE_C"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_COKE_C_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_GOLD_I"), 16777215, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_GOLD_I_SCOPED"), 16777215, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_GOLD_C"), 255, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_GOLD_C_SCOPED"), 255, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_WEED_I"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_WEED_I_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_WEED_C"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_WEED_C_SCOPED"), 0, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_PAINT"), 127, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_PAINT_SCOPED"), 127, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_GOLD_V"), 598484, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4LOOT_PAINT_V"), 448863, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4_PROGRESS"), 124271, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4_MISSIONS"), 65535, TRUE);
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4_PLAYTHROUGH_STATUS"), 40000, TRUE);
								STATS::STAT_SAVE(0, 0, 3, 0);
								notification1("Done!");
							}
							});
					}

					ImGui::Separator();

					if (ImGui::Button("Enable Hard Mode")) {
						g_fiber_pool->queue_job([] {
							if (character1() == 0) {
								STATS::STAT_SET_INT(RAGE_JOAAT("MP0_H4_PROGRESS"), 131055, TRUE);
								STATS::STAT_SAVE(0, 0, 3, 0);
								notification1("Done!");
							}
							if (character1() == 1) {
								STATS::STAT_SET_INT(RAGE_JOAAT("MP1_H4_PROGRESS"), 131055, TRUE);
								STATS::STAT_SAVE(0, 0, 3, 0);
								notification1("Done!");
							}
							});
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			ImGui::Separator();

			ImGui::EndTabItem();
		}
	}
}