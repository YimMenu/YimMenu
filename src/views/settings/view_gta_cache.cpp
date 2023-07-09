#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "thread_pool.hpp"
#include "views/view.hpp"

namespace big
{
	void view::gta_cache()
	{
		auto ped_count = g_gta_data_service->peds().size();
		auto veh_count = g_gta_data_service->vehicles().size();
		auto wep_count = g_gta_data_service->weapons().size();

		components::sub_title("GTA cache stats:");
		ImGui::Text("Peds Cached: %d\nVehicles Cached: %d\nWeapons Cached: %d", ped_count, veh_count, wep_count);

		if (components::button("Rebuild Cache"))
		{
			g_gta_data_service->set_state(eGtaDataUpdateState::NEEDS_UPDATE);
			g_gta_data_service->update_now();
		}
	}
}
