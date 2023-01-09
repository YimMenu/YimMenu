#include "fiber_pool.hpp"
#include "services/mobile/mobile_service.hpp"
#include "util/mobile.hpp"
#include "views/view.hpp"

namespace big
{
	void view::mobile() {
		ImGui::SetWindowSize({ 0.f, (float)*g_pointers->m_resolution_y }, ImGuiCond_Always);
    
		components::sub_title("Merryweather");
		ImGui::Separator();

		components::button("Request Ammo Drop", [] {
			mobile::merry_weather::request_ammo_drop();
		});

		components::button("Helicopter Pickup", [] {
			mobile::merry_weather::request_helicopter_pickup();
		});

		components::button("Request Backup Helicopter", [] {
			mobile::merry_weather::request_backup_helicopter();
		});

		components::button("Request Airstrike", [] {
			mobile::merry_weather::request_airstrike();
		});

		components::sub_title("Mors Mutual");
		ImGui::Separator();

		components::button("Mors Mutual Fix All Vehicles", [] {
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push("Mobile",
				std::format("{} vehicle{} been fixed.", amount_fixed, amount_fixed == 1 ? " has" : "s have")
			);
		});

		components::sub_title("CEO Abilities");
		ImGui::Separator();

		components::button("Bullshark Testosterone", [] {
			mobile::ceo_abilities::request_bullshark_testosterone();
		});

	}
}