#include "services/hotkey/hotkey_service.hpp"
#include "views/view.hpp"
#include "widgets/imgui_hotkey.hpp"

namespace big
{
	void view::hotkey_settings()
	{
		ImGui::PushItemWidth(350.f);

		if (ImGui::Hotkey("Menu Toggle", &g.settings.hotkeys.menu_toggle))
			g.settings.hotkeys.editing_menu_toggle = true; // make our menu reappear

		if (ImGui::Hotkey("Teleport to waypoint", &g.settings.hotkeys.teleport_waypoint))
			g_hotkey_service->update_hotkey("waypoint", g.settings.hotkeys.teleport_waypoint);
		if (ImGui::Hotkey("Teleport to objective", &g.settings.hotkeys.teleport_objective))
			g_hotkey_service->update_hotkey("objective", g.settings.hotkeys.teleport_objective);

		if (ImGui::Hotkey("Toggle Noclip", &g.settings.hotkeys.noclip))
			g_hotkey_service->update_hotkey("noclip", g.settings.hotkeys.noclip);
		if (ImGui::Hotkey("Bring PV", &g.settings.hotkeys.bringvehicle))
			g_hotkey_service->update_hotkey("bringpv", g.settings.hotkeys.bringvehicle);
		if (ImGui::Hotkey("Toggle invisibility", &g.settings.hotkeys.invis))
			g_hotkey_service->update_hotkey("invis", g.settings.hotkeys.invis);
		if (ImGui::Hotkey("Heal", &g.settings.hotkeys.heal))
			g_hotkey_service->update_hotkey("heal", g.settings.hotkeys.heal);
		if (ImGui::Hotkey("Fill Snacks", &g.settings.hotkeys.fill_inventory))
			g_hotkey_service->update_hotkey("fillsnacks", g.settings.hotkeys.fill_inventory);
		if (ImGui::Hotkey("Skip Cutscene", &g.settings.hotkeys.skip_cutscene))
			g_hotkey_service->update_hotkey("skipcutscene", g.settings.hotkeys.skip_cutscene);
		if (ImGui::Hotkey("Toggle Freecam", &g.settings.hotkeys.freecam))
			g_hotkey_service->update_hotkey("freecam", g.settings.hotkeys.freecam);
		if (ImGui::Hotkey("Toggle Fastrun", &g.settings.hotkeys.superrun))
			g_hotkey_service->update_hotkey("fastrun", g.settings.hotkeys.superrun);
		if (ImGui::Hotkey("Toggle Superjump", &g.settings.hotkeys.superjump))
			g_hotkey_service->update_hotkey("superjump", g.settings.hotkeys.superjump);
		if (ImGui::Hotkey("Toggle Beastjump", &g.settings.hotkeys.beastjump))
			g_hotkey_service->update_hotkey("beastjump", g.settings.hotkeys.beastjump);
		if (ImGui::Hotkey("Toggle Vehicle Invisibility", &g.settings.hotkeys.invisveh))
			g_hotkey_service->update_hotkey("invisveh", g.settings.hotkeys.invisveh);
		if (ImGui::Hotkey("Toggle Local Veh Invisibility", &g.settings.hotkeys.localinvisveh))
			g_hotkey_service->update_hotkey("localinvisveh", g.settings.hotkeys.localinvisveh);
		if (ImGui::Hotkey("Fill Ammo", &g.settings.hotkeys.fill_ammo));
			g_hotkey_service->update_hotkey("fillammo", g.settings.hotkeys.fill_ammo);
		if (ImGui::Hotkey("Rage Quit (Like Alt + F4)", &g.settings.hotkeys.fast_quit))
			g_hotkey_service->update_hotkey("fastquit", g.settings.hotkeys.fast_quit);
		if (ImGui::Hotkey("Toggle Command Executor", &g.settings.hotkeys.cmd_excecutor))
			g_hotkey_service->update_hotkey("cmdexecutor", g.settings.hotkeys.cmd_excecutor);
		if (ImGui::Hotkey("Repair PV", &g.settings.hotkeys.repairpv))
			g_hotkey_service->update_hotkey("repairpv", g.settings.hotkeys.repairpv);
		if (ImGui::Hotkey("Vehicle controller", &g.settings.hotkeys.open_vehicle_controller))
			g_hotkey_service->update_hotkey("vehiclecontroller", g.settings.hotkeys.open_vehicle_controller);
		if (ImGui::Hotkey("Clear Wanted", &g.settings.hotkeys.clear_wanted))
			g_hotkey_service->update_hotkey("clearwantedlvl", g.settings.hotkeys.clear_wanted);

		ImGui::PopItemWidth();
	}
}
