#include "core/data/spawned_vehs.hpp"
#include "natives.hpp"
#include "util/delete_entity.hpp"
#include "util/ped.hpp"
#include "views/view.hpp"

namespace big
{
	struct veh_details
	{
		Vehicle veh;
		const char* player_name;
	};

	void view::spawned_vehicles()
	{
		static std::vector<veh_details> spawned_vehs;
		static int tick_count = 61;

		++tick_count;

		if (tick_count > 60)
		{
			tick_count = 0;
			g_fiber_pool->queue_job([] {
				std::vector<veh_details> temp_vehs;

				for (auto veh : g_spawned_vehicles)
				{
					veh_details details = {veh, "[No player]"};
					if (!ENTITY::DOES_ENTITY_EXIST(veh) || ENTITY::IS_ENTITY_DEAD(veh, 0))
						details.player_name = "[DEAD]";
					else if (auto player = ped::get_player_from_ped(VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1, 0)))
						details.player_name = player->get_name();

					temp_vehs.push_back(details);
				}

				spawned_vehs = temp_vehs;
			});
		}

		components::button("Clear All", [] {
			for (auto veh : g_spawned_vehicles)
				entity::delete_entity(veh);
			g_spawned_vehicles.clear();
		});
		ImGui::SameLine();
		ImGui::Text(std::to_string(g_spawned_vehicles.size()).c_str());

		ImGui::BeginChild("ScrollingRegion", {400, 300});

		for (int i = 0; i < spawned_vehs.size(); ++i)
		{
			ImGui::Text(spawned_vehs[i].player_name);
			ImGui::SameLine();
			components::button(std::format("Clear {}", i), [spawned_veh = spawned_vehs[i], i] {
				auto ent = static_cast<Entity>(spawned_veh.veh);
				entity::delete_entity(ent);
				g_spawned_vehicles.erase(g_spawned_vehicles.begin() + i);
			});
			ImGui::Spacing();
		}

		ImGui::EndChild();
	}
}