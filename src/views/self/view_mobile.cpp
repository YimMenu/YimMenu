#include "fiber_pool.hpp"
#include "services/mobile/mobile_service.hpp"
#include "util/mobile.hpp"
#include "views/view.hpp"

namespace big
{
	void view::mobile() {
		ImGui::SetWindowSize({ 0.f, (float)*g_pointers->m_resolution_y }, ImGuiCond_Always);
    
		components::sub_title("MERRYWEATHER"_T.data());
		ImGui::Separator();

		components::button("MW_AMMO_DROP"_T.data(), [] {
			mobile::merry_weather::request_ammo_drop();
		});

		components::button("MW_HELI_PICKUP"_T.data(), [] {
			mobile::merry_weather::request_helicopter_pickup();
		});

		components::button("MW_BACKUP_HELI"_T.data(), [] {
			mobile::merry_weather::request_backup_helicopter();
		});

		components::button("MW_AIRSTRIKE"_T.data(), [] {
			mobile::merry_weather::request_airstrike();
		});

		components::sub_title("MORS_MUTUAL");
		ImGui::Separator();

		components::button("MORS_FIX_ALL"_T.data(), [] {
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push("MOBILE"_T.data(),
				std::format("VEHICLE_FIX_AMOUNT"_T.data(), amount_fixed, amount_fixed == 1 ? "VEHICLE_FIX_HAS"_T.data() : "VEHICLE_FIX_HAVE"_T.data())
			);
		});

		components::sub_title("CEO_ABILITIES"_T.data());
		ImGui::Separator();

		components::button("CEO_BULLSHARK"_T.data(), [] {
			mobile::ceo_abilities::request_bullshark_testosterone();
		});

	}
}