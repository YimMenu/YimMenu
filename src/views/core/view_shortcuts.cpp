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


namespace big
{
	void view::shortcuts()
	{

		if (!g.window.quickmenu)
			return;

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::SetNextWindowBgAlpha(0.5f);
		if (ImGui::Begin("Shortcuts", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize))
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

			if (ImGui::TreeNode("Vehicle"))
			{
				components::command_checkbox_notooltip<"vehgodmode">();
				components::command_checkbox_notooltip<"blockhoming">();
				components::command_checkbox_notooltip<"seatbelt">();
				components::command_checkbox_notooltip<"driveunder">();

				ImGui::TreePop();
			}

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

			components::command_button_notooltip<"skipcutscene">();

			

			ImGui::PopStyleVar();
		}
		ImGui::End();

		ImGui::SetItemDefaultFocus(); // Set focus to the first button every frame
	}
}
