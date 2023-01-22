#include "views/view.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::player_vehicle()
	{
		if (ImGui::TreeNode("Vehicle"))
		{
			components::player_command_button<"vehkick">(g_player_service->get_selected(), {});
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
			components::button("Kill vehicle engine", [] {
				vehicle::kill_vehicle_engine(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Burst tires", [] {
				vehicle::burst_tires(g_player_service->get_selected()->id());
				});

			components::button("Smash windows", [] {
				vehicle::smash_windows(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Black window tint", [] {
				vehicle::set_tint(g_player_service->get_selected()->id());
				});

			components::button("Lock doors", [] {
				vehicle::lock_doors(g_player_service->get_selected()->id());
				});
			ImGui::SameLine();
			components::button("Unlock doors", [] {
				vehicle::unlock_doors(g_player_service->get_selected()->id());
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
