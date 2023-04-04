#include "views/view.hpp"

namespace big
{
	void view::protection_settings()
	{
		ImGui::BeginGroup();
		ImGui::Checkbox("BOUNTY"_T.data(), &g.protections.script_events.bounty);
		ImGui::Checkbox("CEO_MONEY"_T.data(), &g.protections.script_events.ceo_money);
		ImGui::Checkbox("FAKE_DEPOSIT"_T.data(), &g.protections.script_events.fake_deposit);
		ImGui::Checkbox("FORCE_MISSION"_T.data(), &g.protections.script_events.force_mission);
		ImGui::Checkbox("FORCE_TELEPORT"_T.data(), &g.protections.script_events.force_teleport);
		ImGui::Checkbox("GTA_BANNER"_T.data(), &g.protections.script_events.gta_banner);
		ImGui::Checkbox("MC_TELEPORT"_T.data(), &g.protections.script_events.mc_teleport);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox("SEND_TO_CUTSCENE"_T.data(), &g.protections.script_events.send_to_cutscene);
		ImGui::Checkbox("SEND_TO_LOCATION"_T.data(), &g.protections.script_events.send_to_location);
		ImGui::Checkbox("SOUND_SPAM"_T.data(), &g.protections.script_events.sound_spam);
		ImGui::Checkbox("PERSONAL_VEHICLE_DESTROYED"_T.data(), &g.protections.script_events.personal_vehicle_destroyed);
		ImGui::Checkbox("REMOTE_OFF_RADAR"_T.data(), &g.protections.script_events.remote_off_radar);
		ImGui::Checkbox("ROTATE_CAM"_T.data(), &g.protections.script_events.rotate_cam);
		ImGui::Checkbox("TELEPORT_TO_WAREHOUSE"_T.data(), &g.protections.script_events.teleport_to_warehouse);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox("START_ACTIVITY"_T.data(), &g.protections.script_events.start_activity);
		ImGui::Checkbox("SEND_SMS"_T.data(), &g.protections.script_events.send_sms);
		ImGui::Checkbox("SPECTATE"_T.data(), &g.protections.script_events.spectate);
		ImGui::Checkbox("VEHICLE_KICK"_T.data(), &g.protections.script_events.vehicle_kick);
		ImGui::Checkbox("WANTED_LEVEL"_T.data(), &g.protections.script_events.clear_wanted_level);
		ImGui::Checkbox("DESYNC_KICK"_T.data(), &g.protections.desync_kick);
		ImGui::EndGroup();
		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::Checkbox("BLOCK_RID_JOINING"_T.data(), &g.protections.rid_join);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("BLOCK_RID_JOINING_DESCRIPTION"_T.data());
		ImGui::Checkbox("LESSEN_BREAKUP_KICK"_T.data(), &g.protections.lessen_breakups);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("LESSEN_BREAKUP_KICK_DESCRIPTION"_T.data());
		ImGui::Checkbox("Receive Pickup", &g.protections.receive_pickup);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("This prevents any pickup from the ground such as unwanted money drops.\nAttention: Normal pickups are also no longer possible.");
		ImGui::EndGroup();
	}

}
