#include "fiber_pool.hpp"
#include "services/mobile/mobile_service.hpp"
#include "util/mobile.hpp"
#include "views/view.hpp"

namespace big
{
	void view::mobile()
	{
		ImGui::SetWindowSize({0.f, (float)*g_pointers->m_gta.m_resolution_y}, ImGuiCond_Always);


		ImGui::SeparatorText("MERRYWEATHER"_T.data());

		components::button("MW_AMMO_DROP"_T, [] {
			mobile::merry_weather::request_ammo_drop();
		});

		components::button("MW_HELI_PICKUP"_T, [] {
			mobile::merry_weather::request_helicopter_pickup();
		});

		components::command_button<"boatpickup">();

		components::button("MW_BACKUP_HELI"_T, [] {
			mobile::merry_weather::request_backup_helicopter();
		});

		components::button("MW_AIRSTRIKE"_T, [] {
			mobile::merry_weather::request_airstrike();
		});


		ImGui::SeparatorText("CEO_ABILITIES"_T.data());

		components::button("CEO_BULLSHARK"_T, [] {
			mobile::ceo_abilities::request_bullshark_testosterone();
		});

		components::command_button<"ballisticarmor">();

		components::button("Request MOC", [] {
			mobile::ceo_abilities::request_mobile_operations_center();
		});

		components::button("Request Avenger", [] {
			mobile::ceo_abilities::request_avenger();
		});

		components::button("Request Terrobyte", [] {
			mobile::ceo_abilities::request_terrobyte();
		});

		components::button("Request Acid Lab", [] {
			mobile::ceo_abilities::request_acidlab();
		});

		components::button("Request Acid Bike", [] {
			mobile::ceo_abilities::request_acidlab_bike();
		});


		ImGui::SeparatorText("Miscellaneous");

		components::button("Request Taxi", [] {
			mobile::misc::request_taxi();
		});


		ImGui::SeparatorText("MORS_MUTUAL"_T.data());

		components::button("MORS_FIX_ALL"_T, [] {
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push_success("MOBILE"_T.data(),
			    std::vformat("VEHICLE_FIX_AMOUNT"_T,
			        std::make_format_args(amount_fixed,
			            amount_fixed == 1 ? "VEHICLE_FIX_HAS"_T.data() : "VEHICLE_FIX_HAVE"_T.data())));
		});
	}
}