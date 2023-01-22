#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"
#include "util/kick.hpp"

namespace big
{
	void view::player_vehicle()
	{
		if (ImGui::TreeNode("Vehicle"))
		{
			components::button("Kick From Vehicle", [] {
				vehicle::kick_player_from_vehicle(g_player_service->get_selected());
				});
			ImGui::SameLine();
			components::button("Flying Vehicle", [] {
				vehicle::flying_vehicle(g_player_service->get_selected()->id());
				});

			components::button("Boost player vehicle", [] {
				vehicle::boost_player_vehicle(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Stop player vehicle", [] {
				vehicle::stop_player_vehicle(g_player_service->get_selected()->id());
				});

			components::button("Rotate 180", [] {
				vehicle::flip_180(g_player_service->get_selected()->id());
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
				vehicle::kill_vehicle_engine(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Burst tires", [] {
				vehicle::BurstTires(g_player_service->get_selected()->id());
				});

			components::button("Smash windows", [] {
				vehicle::smash_windows(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Black window tint", [] {
				vehicle::set_tint(g_player_service->get_selected()->id());
				});

			components::button("Lock doors", [] {
				vehicle::LockDoors(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Unlock doors", [] {
				vehicle::UnlockDoors(g_player_service->get_selected()->id());
				});

			components::button("Open doors", [] {
				vehicle::open_doors(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Close doors", [] {
				vehicle::close_doors(g_player_service->get_selected()->id());
				});

			components::button("Upgrade Vehicle", [] {
				vehicle::upgrade_vehicle(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Downgrade Vehicle", [] {
				vehicle::downgrade_vehicle(g_player_service->get_selected()->id());
				});

			components::button("Gift vehicle", [] {
				vehicle::gift_vehicle(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Clone Vehicle", [] {
				vehicle::clone_vehicle(g_player_service->get_selected()->id());
				});

			ImGui::TreePop();
		}
	} 
}
