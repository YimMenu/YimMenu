#include "services/hotkey/hotkey_service.hpp"
#include "views/view.hpp"
#include "widgets/imgui_hotkey.hpp"

namespace big
{
	void view::hotkey_settings()
	{
		ImGui::PushItemWidth(350.f);

		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_MENU_TOGGLE"_T.data(), &g.settings.hotkeys.menu_toggle))
			g.settings.hotkeys.editing_menu_toggle = true; // make our menu reappear

		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TELEPORT_TO_WAYPOINT"_T.data(), &g.settings.hotkeys.teleport_waypoint))
			g_hotkey_service->update_hotkey("waypoint", g.settings.hotkeys.teleport_waypoint);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TELEPORT_TO_OBJECTIVE"_T.data(), &g.settings.hotkeys.teleport_objective))
			g_hotkey_service->update_hotkey("objective", g.settings.hotkeys.teleport_objective);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TELEPORT_TO_SELECTED"_T.data(), &g.settings.hotkeys.teleport_selected))
			g_hotkey_service->update_hotkey("highlighttp", g.settings.hotkeys.teleport_selected);
		if (ImGui::Hotkey("TP_IN_PV"_T.data(), &g.settings.hotkeys.teleport_pv))
			g_hotkey_service->update_hotkey("pvtp", g.settings.hotkeys.teleport_pv);

		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TOGGLE_NOCLIP"_T.data(), &g.settings.hotkeys.noclip))
			g_hotkey_service->update_hotkey("noclip", g.settings.hotkeys.noclip);
		if (ImGui::Hotkey("BRING_PV"_T.data(), &g.settings.hotkeys.bringvehicle))
			g_hotkey_service->update_hotkey("bringpv", g.settings.hotkeys.bringvehicle);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TOGGLE_INVISIBILITY"_T.data(), &g.settings.hotkeys.invis))
			g_hotkey_service->update_hotkey("invis", g.settings.hotkeys.invis);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TOGGLE_PASSIVE_MODE"_T.data(), &g.settings.hotkeys.passive))
			g_hotkey_service->update_hotkey("passive", g.settings.hotkeys.passive);
		if (ImGui::Hotkey("HEAL"_T.data(), &g.settings.hotkeys.heal))
			g_hotkey_service->update_hotkey("heal", g.settings.hotkeys.heal);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_FILL_SNACKS"_T.data(), &g.settings.hotkeys.fill_inventory))
			g_hotkey_service->update_hotkey("fillsnacks", g.settings.hotkeys.fill_inventory);
		if (ImGui::Hotkey("SKIP_CUTSCENE"_T.data(), &g.settings.hotkeys.skip_cutscene))
			g_hotkey_service->update_hotkey("skipcutscene", g.settings.hotkeys.skip_cutscene);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TOGGLE_FREECAM"_T.data(), &g.settings.hotkeys.freecam))
			g_hotkey_service->update_hotkey("freecam", g.settings.hotkeys.freecam);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TOGGLE_FASTRUN"_T.data(), &g.settings.hotkeys.superrun))
			g_hotkey_service->update_hotkey("fastrun", g.settings.hotkeys.superrun);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TOGGLE_SUPERJUMP"_T.data(), &g.settings.hotkeys.superjump))
			g_hotkey_service->update_hotkey("superjump", g.settings.hotkeys.superjump);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TOGGLE_BEASTJUMP"_T.data(), &g.settings.hotkeys.beastjump))
			g_hotkey_service->update_hotkey("beastjump", g.settings.hotkeys.beastjump);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TOGGLE_VEHICLE_INVISIBILITY"_T.data(), &g.settings.hotkeys.invisveh))
			g_hotkey_service->update_hotkey("invisveh", g.settings.hotkeys.invisveh);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TOGGLE_LOCAL_VEHICLE_INVISIBILITY"_T.data(), &g.settings.hotkeys.localinvisveh))
			g_hotkey_service->update_hotkey("localinvisveh", g.settings.hotkeys.localinvisveh);
		if (ImGui::Hotkey("FILL_AMMO"_T.data(), &g.settings.hotkeys.fill_ammo));
			g_hotkey_service->update_hotkey("fillammo", g.settings.hotkeys.fill_ammo);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_RAGE_QUIT"_T.data(), &g.settings.hotkeys.fast_quit))
			g_hotkey_service->update_hotkey("fastquit", g.settings.hotkeys.fast_quit);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TOGGLE_COMMAND_EXECUTOR"_T.data(), &g.settings.hotkeys.cmd_excecutor))
			g_hotkey_service->update_hotkey("cmdexecutor", g.settings.hotkeys.cmd_excecutor);
		if (ImGui::Hotkey("REPAIR_PV"_T.data(), &g.settings.hotkeys.repairpv))
			g_hotkey_service->update_hotkey("repairpv", g.settings.hotkeys.repairpv);
		if (ImGui::Hotkey("VEHICLE_CONTROLLER"_T.data(), &g.settings.hotkeys.open_vehicle_controller))
			g_hotkey_service->update_hotkey("vehiclecontroller", g.settings.hotkeys.open_vehicle_controller);
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_TOGGLE_VEHICLE_FLY"_T.data(), &g.settings.hotkeys.vehicle_flymode))
			g_hotkey_service->update_hotkey("vehiclefly", g.settings.hotkeys.vehicle_flymode);
		if (ImGui::Hotkey("CLEAR_WANTED_LEVEL"_T.data(), &g.settings.hotkeys.clear_wanted))
			g_hotkey_service->update_hotkey("clearwantedself", g.settings.hotkeys.clear_wanted);

		ImGui::PopItemWidth();
	}
}
