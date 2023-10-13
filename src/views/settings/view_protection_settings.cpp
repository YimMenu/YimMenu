#include "views/view.hpp"
#include "core/settings/protections.hpp"

namespace big
{
	static inline void set_all_protections(bool state)
	{
		for (size_t i = (size_t)&g_protections; i <= (size_t) & (g_protections.admin_check); i++)
			*(bool*)i = state;
	}

	static inline void reset_protections()
	{
		g_protections = {};
	}

	void view::protection_settings()
	{
		ImGui::BeginGroup();
		ImGui::Checkbox("CEO Money", &g_protections.script_events.ceo_money);
		ImGui::Checkbox("Force Mission", &g_protections.script_events.force_mission);
		ImGui::Checkbox("Force Teleport", &g_protections.script_events.force_teleport);
		ImGui::Checkbox("GTA Banner", &g_protections.script_events.gta_banner);
		ImGui::Checkbox("MC Teleport", &g_protections.script_events.mc_teleport);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox("Send to Cutscene", &g_protections.script_events.send_to_cutscene);
		ImGui::Checkbox("Send to Location", &g_protections.script_events.send_to_location);
		ImGui::Checkbox("Sound Spam", &g_protections.script_events.sound_spam);
		ImGui::Checkbox("Personal Vehicle Destroyed", &g_protections.script_events.personal_vehicle_destroyed);
		ImGui::Checkbox("Remote Off Radar", &g_protections.script_events.remote_off_radar);
		ImGui::Checkbox("Rotate Cam", &g_protections.script_events.rotate_cam);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox("Teleport To Warehouse", &g_protections.script_events.teleport_to_warehouse);
		ImGui::Checkbox("Start Activity", &g_protections.script_events.start_activity);
		ImGui::Checkbox("Send SMS", &g_protections.script_events.send_sms);
		ImGui::Checkbox("Spectate", &g_protections.script_events.spectate);
		ImGui::Checkbox("Vehicle Kick", &g_protections.script_events.vehicle_kick);
		ImGui::Checkbox("Wanted Level", &g_protections.script_events.clear_wanted_level);
		ImGui::EndGroup();
		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox("Block RID Joining", &g_protections.rid_join);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("This will block anyone trying to join, kick or crash you with your Rockstar ID, including your friends");
		ImGui::Checkbox("Receive Pickup", &g_protections.receive_pickup);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("This prevents the collection of pickups such as unwanted money bags\nNote: Normal pickups are also no longer possible to collect with this enabled");
		ImGui::Checkbox("Admin Check", &g_protections.admin_check);
		ImGui::EndGroup();

		ImGui::SeparatorText("Options");
		ImGui::BeginGroup();
		if (ImGui::Button("Enable All Protections"))
			set_all_protections(true);
		ImGui::SameLine();
		if (ImGui::Button("Disable All Protections"))
			set_all_protections(false);
		ImGui::SameLine();
		if (ImGui::Button("Reset Protections"))
			reset_protections();
		ImGui::EndGroup();
	};
}
