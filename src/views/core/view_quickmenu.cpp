#include "fiber_pool.hpp"
#include "services/mobile/mobile_service.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"
#include "views/view.hpp"
#include "gta_util.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"
#include "util/local_player.hpp"
#include "util/scripts.hpp"
#include "util/globals.hpp"
#include "gta/joaat.hpp"
#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/vehicle_helper/vehicle_helper.hpp"


namespace big
{
	void view::quickmenu()
	{

		if (!g.window.quickmenu)
			return;

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_FirstUseEver, ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowBgAlpha(0.5f);
		
		static Vehicle player_vehicle = 0;

		player_vehicle = self::veh;

		if (ImGui::Begin("quickmenu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));

			

			if (!g_gui->is_open())
			{
				ImGui::SetWindowFocus();
			}

			ImGui::SetItemDefaultFocus(); // Set initial focus to the first item


			if (ImGui::TreeNode("Self"))
			{
				components::command_checkbox_notooltip<"godmode">();
				ImGui::Checkbox("NEVER_WANTED"_T.data(), &g.self.never_wanted);
				components::command_checkbox_notooltip<"noragdoll">();
				components::command_checkbox_notooltip<"noidlekick">();
				components::command_checkbox_notooltip<"otr">();
				components::command_button_notooltip<"suicide">();
				components::command_button_notooltip<"heal">();

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Weapons"))
			{
				components::command_checkbox_notooltip<"infammo">();
				components::command_checkbox_notooltip<"alwaysfullammo">();
				components::command_checkbox_notooltip<"infclip">();
				components::command_checkbox_notooltip<"infrange">();
				components::command_checkbox_notooltip<"norecoil">();
				components::command_checkbox_notooltip<"nospread">();
				ImGui::Checkbox("Allow Weapons In Interiors", &g.weapons.interior_weapon);

				ImGui::TreePop();
			}


			if (ImGui::TreeNode("Vehicle"))
			{
				components::command_checkbox_notooltip<"vehgodmode">();
				components::command_checkbox_notooltip<"blockhoming">();
				components::command_checkbox_notooltip<"seatbelt">();
				components::command_checkbox_notooltip<"driveunder">();

				components::button("MORS_FIX_ALL"_T, [] {
					int amount_fixed = mobile::mors_mutual::fix_all();
					g_notification_service->push_success("MOBILE"_T.data(),
					    std::vformat("VEHICLE_FIX_AMOUNT"_T,
					        std::make_format_args(amount_fixed,
					            amount_fixed == 1 ? "VEHICLE_FIX_HAS"_T.data() : "VEHICLE_FIX_HAVE"_T.data())));
				});

				components::button("TP_IN_PV"_T, [] {
					Vehicle veh = mobile::mechanic::get_personal_vehicle();
					teleport::into_vehicle(veh);
				});

				components::button("BRING_PV"_T, [] {
					Vehicle veh = mobile::mechanic::get_personal_vehicle();
					vehicle::bring(veh, self::pos, true);
				});

				if (components::button("MAX_VEHICLE"_T))
				{
					g_fiber_pool->queue_job([] {
						vehicle::max_vehicle(self::veh);

						// refresh mod names
						player_vehicle = 0;
					});
				}

				if (components::button("Max Performance"))
				{
					g_fiber_pool->queue_job([] {
						vehicle::max_vehicle_performance(self::veh);

						// refresh mod names
						player_vehicle = 0;
					});
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Misc"))
			{
				components::command_button_notooltip<"skipcutscene">();
				components::command_button_notooltip<"waypointtp">({}, "Waypoint");



				ImGui::TreePop();
			}
			

			

			

			ImGui::PopStyleVar();
		}
		ImGui::End();

		ImGui::SetItemDefaultFocus(); // Set focus to the first button every frame
	}
}
