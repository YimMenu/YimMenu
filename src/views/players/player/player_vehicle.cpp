#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "util/kick.hpp"

namespace big
{
	void view::player_vehicle()
	{
		if (ImGui::TreeNode("Vehicle"))
		{
			components::button("Kick From Vehicle", [] {
				toxic::kick_player_from_vehicle(g_player_service->get_selected());
				});
			ImGui::SameLine();
			components::button("Flying Vehicle", [] {
				toxic::flying_vehicle(g_player_service->get_selected()->id());
				});

			components::button("Boost player vehicle", [] {
				toxic::boost_player_vehicle(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Stop player vehicle", [] {
				toxic::stop_player_vehicle(g_player_service->get_selected()->id());
				});

			components::button("Rotate 180", [] {
				toxic::flip_180(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Remote Control Vehicle", []
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), FALSE);
			if (veh == 0)
			{
				if (g.player.spectating)
					g_notification_service->push_warning("Remote Control", "Player not in a vehicle");
				else
					g_notification_service->push_warning("Remote Control", "Player not in a vehicle, try spectating the player");
				return;
			}

			vehicle::remote_control_vehicle(veh);
			g.player.spectating = false;
				});

			components::button("Kill vehicle engine", [] {
				toxic::kill_vehicle_engine(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Burst tires", [] {
				toxic::BurstTires(g_player_service->get_selected()->id());
				});

			components::button("Smash windows", [] {
				toxic::smash_windows(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Black window tint", [] {
				toxic::set_tint(g_player_service->get_selected()->id());
				});

			components::button("Lock doors", [] {
				toxic::LockDoors(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Unlock doors", [] {
				toxic::UnlockDoors(g_player_service->get_selected()->id());
				});

			components::button("Open doors", [] {
				toxic::open_doors(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Close doors", [] {
				toxic::close_doors(g_player_service->get_selected()->id());
				});

			components::button("Upgrade Vehicle", [] {
				toxic::upgrade_vehicle(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Downgrade Vehicle", [] {
				toxic::downgrade_vehicle(g_player_service->get_selected()->id());
				});

			components::button("Gift vehicle", [] {
				toxic::gift_vehicle(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Clone Vehicle", [] {
				toxic::clone_vehicle(g_player_service->get_selected()->id());
				});

			ImGui::TreePop();
		}
	} 
}
