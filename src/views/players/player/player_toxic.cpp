#include "util/toxic.hpp"
#include "util/troll.hpp"
#include "views/view.hpp"

namespace big
{
	void view::player_toxic()
	{
		ImGui::SeparatorText("TOXIC"_T.data());
	
		ImGui::BeginGroup();
		components::player_command_button<"kill">(g_player_service->get_selected(), {});
		components::player_command_button<"explode">(g_player_service->get_selected(), {});
		components::player_command_button<"ceokick">(g_player_service->get_selected(), {});
		components::player_command_button<"ragdoll">(g_player_service->get_selected(), {});
		components::player_command_button<"beast">(g_player_service->get_selected(), {});
		components::player_command_button<"mission">(g_player_service->get_selected(), {});
		components::player_command_button<"breakgame">(g_player_service->get_selected(), {});
		components::player_command_button<"error">(g_player_service->get_selected(), {});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::player_command_button<"ceoraid">(g_player_service->get_selected(), {});
		components::button("TRIGGER_MC_RAID"_T, [] {
			toxic::start_activity(g_player_service->get_selected(), eActivityType::BikerDefend);
		});
		components::button("TRIGGER_BUNKER_RAID"_T, [] {
			toxic::start_activity(g_player_service->get_selected(), eActivityType::GunrunningDefend);
		});
		components::player_command_button<"sext">(g_player_service->get_selected(), {});
		components::player_command_button<"fakeban">(g_player_service->get_selected(), {});
		components::player_command_button<"remweaps">(g_player_service->get_selected(), {});
		components::player_command_button<"tutorial">(g_player_service->get_selected(), {});
		components::player_command_button<"golf">(g_player_service->get_selected(), {});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::player_command_button<"flightschool">(g_player_service->get_selected(), {});
		components::player_command_button<"darts">(g_player_service->get_selected(), {});
		components::player_command_button<"badlands">(g_player_service->get_selected(), {});
		components::player_command_button<"spacemonkey">(g_player_service->get_selected(), {});
		components::player_command_button<"wizard">(g_player_service->get_selected(), {});
		components::player_command_button<"qub3d">(g_player_service->get_selected(), {});
		components::player_command_button<"camhedz">(g_player_service->get_selected(), {});
		ImGui::EndGroup();

		ImGui::BeginGroup();
		components::small_text("WARP_TIME"_T);

		components::button("PLUS_1_MINUTE"_T, [] {
			toxic::warp_time_forward(g_player_service->get_selected(), 60 * 1000);
		});
		ImGui::SameLine();
		components::button("PLUS_5_MINUTES"_T, [] {
			toxic::warp_time_forward(g_player_service->get_selected(), 5 * 60 * 1000);
		});
		ImGui::SameLine();
		components::button("PLUS_48_MINUTES"_T, [] {
			toxic::warp_time_forward(g_player_service->get_selected(), 48 * 60 * 1000);
		});
		components::button("PLUS_96_MINUTES"_T, [] {
			toxic::warp_time_forward(g_player_service->get_selected(), 96 * 60 * 1000);
		});
		ImGui::SameLine();
		components::button("PLUS_200_MINUTES"_T, [] {
			toxic::warp_time_forward(g_player_service->get_selected(), 200 * 60 * 1000);
		});
		ImGui::SameLine();
		components::button("STOP_TIME"_T, [] {
			toxic::set_time(g_player_service->get_selected(), INT_MAX - 3000);
		});
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("PLAYER_TOXIC_NO_WAY_BACK"_T.data());
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		static int bounty_value = 0;
		ImGui::SetNextItemWidth(175);
		ImGui::SliderInt("BOUNTY"_T.data(), &bounty_value, 0, 10000);

		components::command_checkbox<"anonbounty">();
		ImGui::SameLine();
		ImGui::PushID("setbounty");
		components::button("SET"_T, [] {
			troll::set_bounty_on_player(g_player_service->get_selected(), bounty_value, g.session.anonymous_bounty);
		});
		ImGui::PopID();
		ImGui::EndGroup();

		ImGui::Checkbox("KILL_LOOP"_T.data(), &g_player_service->get_selected()->kill_loop);
		ImGui::SameLine();
		ImGui::Checkbox("EXPLOSION_LOOP"_T.data(), &g_player_service->get_selected()->explosion_loop);
		ImGui::SameLine();
		ImGui::Checkbox("RAGDOLL_LOOP"_T.data(), &g_player_service->get_selected()->ragdoll_loop);
		ImGui::SameLine();
		ImGui::Checkbox("ROT_CAM_LOOP"_T.data(), &g_player_service->get_selected()->rotate_cam_loop);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("PLAYER_TOXIC_BRING_PLAYER_OUT_GOD"_T.data());
		ImGui::SameLine();
		ImGui::Checkbox("SPAM_KILLFEED"_T.data(), &g_player_service->get_selected()->spam_killfeed);

		static int wanted_level;
		components::small_text("WANTED_LVL"_T);
		ImGui::SetNextItemWidth(150);
		ImGui::SliderInt("##wantedlevelslider", &wanted_level, 0, 5);
		ImGui::SameLine();
		components::player_command_button<"wanted">(g_player_service->get_selected(), {(uint64_t)wanted_level}, "Set");
	}
}