#include "fiber_pool.hpp"
#include "services/mobile/mobile_service.hpp"
#include "util/mobile.hpp"
#include "views/view.hpp"
#include "core/data/phone_types.hpp"

namespace big
{
	void view::mobile() {
		/*components::sub_title("Phone selection");
		if (ImGui::BeginCombo("Phones", phone_types[g->tunables.phone_type]))
		{
			for (int i = 0; i < phone_types.size(); i++)
			{
				if (ImGui::Selectable(phone_types[i], g->tunables.phone_type == i))
				{
					g->tunables.phone_type = i;
				};
			}
			ImGui::EndCombo();
		}*/

		components::sub_title("Lester");

		ImGui::Checkbox("Off Radar", &g->self.off_radar);

		ImGui::Separator();	
		
		components::sub_title("Merryweather");

		ImGui::Separator();

		components::button("Request Ammo Drop", [] {
			mobile::merry_weather::request_ammo_drop();
		});

		components::button("Helicopter Pickup", [] {
			mobile::merry_weather::request_helicopter_pickup();
		});

		ImGui::Separator();

		components::button("Mors Mutual Fix All Vehicles", [] {
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push("Mobile",
				std::format("{} vehicle{} been fixed.", amount_fixed, amount_fixed == 1 ? " has" : "s have")
			);
		});
	}
}
