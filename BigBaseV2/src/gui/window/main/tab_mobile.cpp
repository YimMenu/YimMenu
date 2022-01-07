#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "util/mobile.hpp"
#include "util/notify.hpp"

namespace big
{
	void tab_main::tab_mobile()
	{
		if (ImGui::BeginTabItem("Mobile"))
		{
			if (ImGui::Button("Mors Mutual Fix All Vehicles"))
			{
				int amount_fixed = mobile::mors_mutual::fix_all();

				QUEUE_JOB_BEGIN_CLAUSE(amount_fixed)
				{
					char vehicles_fixed[42];
					sprintf(vehicles_fixed, "<C>%d</C> vehicle%s been fixed.", amount_fixed, amount_fixed == 1 ? " has" : "s have");

					notify::above_map(vehicles_fixed);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}