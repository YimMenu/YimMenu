#include "fiber_pool.hpp"
#include "services/mobile/mobile_service.hpp"
#include "util/mobile.hpp"
#include "views/view.hpp"

namespace big
{
	//Doing the grouping stuff here too because its done everywhere else

	void view::mobile() 
	{
		ImGui::SetWindowSize({ 0.f, (float)*g_pointers->m_resolution_y }, ImGuiCond_Always);
    
		//This "Lester" tab used to be here in an older version of the menu, but was removed
		//Because it was the only thing in the mobile tab. Now that other features are here,
		//I think it belongs back where it was. Let me know if this is dumb.
		components::sub_title("Lester");

		ImGui::BeginGroup();
		{
			components::command_checkbox<"otr">();

			ImGui::EndGroup();
		}


		ImGui::Separator();
		components::sub_title("Merryweather");

		ImGui::BeginGroup();
		{
			components::button("Request Ammo Drop", [] {mobile::merry_weather::request_ammo_drop(); });
			components::button("Helicopter Pickup", [] {mobile::merry_weather::request_helicopter_pickup(); });
			components::button("Request Backup Helicopter", [] {mobile::merry_weather::request_backup_helicopter(); });
			components::button("Request Airstrike", [] {mobile::merry_weather::request_airstrike(); });

			ImGui::EndGroup();
		}


		ImGui::Separator();	
		components::sub_title("Mors Mutual");

		ImGui::BeginGroup();
		{
			components::button("Mors Mutual Fix All Vehicles", []
			{
				int amount_fixed = mobile::mors_mutual::fix_all();

				g_notification_service->push(
					"Mobile",
					std::format("{} vehicle{} been fixed.",
					amount_fixed, amount_fixed == 1 ? " has" : "s have")
				);
			});

			ImGui::EndGroup();
		}


		ImGui::Separator();
		components::sub_title("CEO Abilities");

		ImGui::BeginGroup();
		{
			components::button("Bullshark Testosterone", [] {mobile::ceo_abilities::request_bullshark_testosterone(); });

			ImGui::EndGroup();
		}
	}
}