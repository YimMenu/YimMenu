#include "fiber_pool.hpp"
#include "services/mobile/mobile_service.hpp"
#include "util/mobile.hpp"
#include "views/view.hpp"

namespace big
{
	void view::mobile() {
		ImGui::SetWindowSize({ 0.f, (float)*g_pointers->m_resolution_y }, ImGuiCond_Always);

		components::sub_title("Lester");

		ImGui::Checkbox("Off Radar", &g->self.off_radar);

		ImGui::Separator();

		components::button("Mors Mutual Fix All Vehicles", [] {
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push("Mobile",
				std::format("{} vehicle{} been fixed.", amount_fixed, amount_fixed == 1 ? " has" : "s have")
			);
		});
	}
}
