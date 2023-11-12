#include "backend/looped/looped.hpp"
#include "services/gui/gui_service.hpp"
#include "util/lua_script.cpp"
#include "views/view.hpp"

const char* approachs[] = {"Unselected", "Silent & Sneaky", "The Big Con", "Aggressive"};
const char* targets[]   = {"Money", "Gold", "Art", "Diamonds"};
const char* gunmans[] = {"Unselected", "Karl Abolaji", "Gustavo Mota", "Charlie Reed", "Chester McCoy", "Patrick McReary"};
const char* drivers[] = {"Unselected", "Karim Deniz", "Taliana Martinez", "Eddie Toh", "Zach Nelson", "Chester McCoy"};
const char* hackers[] = {"Unselected", "Rickie Lukens", "Christian Feltz", "Yohan Blair", "Avi Schwartzman", "Page Harris"};
const char* masks[] = {"Unselected", "Geometric Set", "Hunter Set", "Oni Half Mask Set", "Emoji Set", "Ornate Skull Set", "Lucky Fruit Set", "Gurilla Set", "Clown Set", "Animal Set", "Riot Set", "Oni Set", "Hockey Set"};

int slots_random_results_table            = 1344;
int fm_mission_controller_cart_grab       = 10247;
int fm_mission_controller_cart_grab_speed = 14;

namespace big
{
	static struct casino_shared_data
	{
		// bool rig_slot_machine;
		bool fm_mission_controller_cart_autograb;
	} casino_shared_data{};

	void looped::casino()
	{
		if (g_gui_service->get_selected_tab().empty() || g_gui_service->get_selected_tab().back() != tabs::CASINO)
			return;

		// if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::joaat("casino_slots")) != 0)
		// {
		// 	bool needsRun = false;

		// 	if (casino_shared_data.rig_slot_machine)
		// 	{
		// 		for (int slotsIter = 3; slotsIter <= 195; ++slotsIter)
		// 			if (slotsIter != 67 && slotsIter != 132)
		// 				if (lua_script::locals::get_int("casino_slots", slots_random_results_table + slotsIter) != 6)
		// 					needsRun = true;
		// 	}
		// 	else
		// 	{
		// 		int sum = 0;
		// 		for (int slotsIter = 3; slotsIter <= 195; ++slotsIter)
		// 			if (slotsIter != 67 && slotsIter != 132)
		// 				sum += lua_script::locals::get_int("casino_slots", slots_random_results_table + slotsIter);

		// 		needsRun = (sum == 1146);
		// 	}

		// 	if (needsRun)
		// 	{
		// 		for (int slotsIter = 3; slotsIter <= 195; ++slotsIter)
		// 			if (slotsIter != 67 && slotsIter != 132)
		// 			{
		// 				int slotResult = 6;
		// 				if (!casino_shared_data.rig_slot_machine)
		// 				{
		// 					std::srand(static_cast<unsigned int>(std::time(nullptr)) + slotsIter);
		// 					slotResult = std::rand() % 8;
		// 				}
		// 				lua_script::locals::set_int("casino_slots", slots_random_results_table + slotsIter, slotResult);
		// 			}
		// 	}
		// }

		if (HUD::IS_PAUSE_MENU_ACTIVE())
		{
			PAD::DISABLE_CONTROL_ACTION(0, 348, true);
			PAD::DISABLE_CONTROL_ACTION(0, 204, true);
		}

		if (casino_shared_data.fm_mission_controller_cart_autograb)
		{
			if (lua_script::locals::get_int("fm_mission_controller", fm_mission_controller_cart_grab) == 3)
				lua_script::locals::set_int("fm_mission_controller", fm_mission_controller_cart_grab, 4);
			else if (lua_script::locals::get_int("fm_mission_controller", fm_mission_controller_cart_grab) == 4)
				lua_script::locals::set_float("fm_mission_controller", fm_mission_controller_cart_grab + fm_mission_controller_cart_grab_speed, 2);
		}
	}

	void view::casino()
	{
		ImGui::BeginGroup();

		// ImGui::Checkbox("Rig Slot Machines", &casino_shared_data.rig_slot_machine);

		ImGui::SeparatorText("Casino Heist");

		static int new_approach = 0, new_last_approach = 0, new_hard_approach = 0, new_target = 0, new_gunman = 0, new_driver = 0, new_hacker = 0, new_mask = 0;

		ImGui::PushItemWidth(165);
		ImGui::BeginGroup();
		if (ImGui::Combo("Approach", &new_approach, approachs, IM_ARRAYSIZE(approachs)))
			g_fiber_pool->queue_job([=] {
				lua_script::stats::set_int("MPX_H3OPT_APPROACH", new_approach);
			});
		if (ImGui::Combo("Last Approach", &new_last_approach, approachs, IM_ARRAYSIZE(approachs)))
			g_fiber_pool->queue_job([=] {
				lua_script::stats::set_int("MPX_H3_LAST_APPROACH", new_last_approach);
			});
		if (ImGui::Combo("Hard Approach", &new_hard_approach, approachs, IM_ARRAYSIZE(approachs)))
			g_fiber_pool->queue_job([=] {
				lua_script::stats::set_int("MPX_H3_HARD_APPROACH", new_hard_approach);
			});
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		if (ImGui::Combo("Target", &new_target, targets, IM_ARRAYSIZE(targets)))
			g_fiber_pool->queue_job([=] {
				lua_script::stats::set_int("MPX_H3OPT_TARGET", new_target);
			});
		if (ImGui::Combo("Masks", &new_mask, masks, IM_ARRAYSIZE(masks)))
			g_fiber_pool->queue_job([=] {
				lua_script::stats::set_int("MPX_H3OPT_MASKS", new_mask);
			});
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		if (ImGui::Combo("Gunman", &new_gunman, gunmans, IM_ARRAYSIZE(gunmans)))
			g_fiber_pool->queue_job([=] {
				lua_script::stats::set_int("MPX_H3OPT_CREWWEAP", new_gunman);
			});
		if (ImGui::Combo("Driver", &new_driver, drivers, IM_ARRAYSIZE(drivers)))
			g_fiber_pool->queue_job([=] {
				lua_script::stats::set_int("MPX_H3OPT_CREWDRIVER", new_driver);
			});
		if (ImGui::Combo("Hacker", &new_hacker, hackers, IM_ARRAYSIZE(hackers)))
			g_fiber_pool->queue_job([=] {
				lua_script::stats::set_int("MPX_H3OPT_CREWHACKER", new_hacker);
			});
		ImGui::EndGroup();
		ImGui::PopItemWidth();

		ImGui::Spacing();

		ImGui::Checkbox("Auto Grab Cash/Gold/Diamonds", &casino_shared_data.fm_mission_controller_cart_autograb);

		ImGui::Spacing();

		components::button("Refresh Current Heist State", [&] {
			new_approach      = lua_script::stats::get_int("MPX_H3OPT_APPROACH");
			new_target        = lua_script::stats::get_int("MPX_H3OPT_TARGET");
			new_last_approach = lua_script::stats::get_int("MPX_H3_LAST_APPROACH");
			new_hard_approach = lua_script::stats::get_int("MPX_H3_HARD_APPROACH");
			new_gunman        = lua_script::stats::get_int("MPX_H3OPT_CREWWEAP");
			new_driver        = lua_script::stats::get_int("MPX_H3OPT_CREWDRIVER");
			new_hacker        = lua_script::stats::get_int("MPX_H3OPT_CREWHACKER");
			new_mask          = lua_script::stats::get_int("MPX_H3OPT_MASKS");
		});

		ImGui::SameLine();

		static bool open_unlock_heist_options_conf_popup;

		if (components::button("Unlock All Heist Options"))
			open_unlock_heist_options_conf_popup = true;

		if (open_unlock_heist_options_conf_popup)
			ImGui::OpenPopup("##unlock_heist_options_conf_popup");
		if (ImGui::BeginPopupModal("##unlock_heist_options_conf_popup", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text("Are you sure you want to Unlock All Heist Option");
			ImGui::Spacing();
			if (ImGui::Button("Yes"))
			{
				g_fiber_pool->queue_job([] {
					lua_script::stats::set_int("MPX_H3OPT_ACCESSPOINTS", -1);
					lua_script::stats::set_int("MPX_H3OPT_POI", -1);
					lua_script::stats::set_int("MPX_H3OPT_BITSET0", -1);
					lua_script::stats::set_int("MPX_H3OPT_BITSET1", -1);
					lua_script::stats::set_int("MPX_H3OPT_BODYARMORLVL", 3);
					lua_script::stats::set_int("MPX_H3OPT_DISRUPTSHIP", 3);
					lua_script::stats::set_int("MPX_H3OPT_KEYLEVELS", 2);
					lua_script::stats::set_int("MPX_H3_COMPLETEDPOSIX", 0);
					lua_script::stats::set_int("MPX_CAS_HEIST_FLOW", -1);

					lua_script::stats::set_int("MPPLY_H3_COOLDOWN", 0);

					STATS::SET_PACKED_STAT_BOOL_CODE(26969, true, big::local_player::get_active_character_slot());
				});

				open_unlock_heist_options_conf_popup = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("No"))
			{
				open_unlock_heist_options_conf_popup = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::EndGroup();
	}
}
