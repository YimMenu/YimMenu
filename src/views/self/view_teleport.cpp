#include "core/data/ipls.hpp"
#include "fiber_pool.hpp"
#include "util/globals.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void view::teleport()
	{
		ImGui::Text("BLIPS"_T.data());

		components::command_button<"waypointtp">({}, "Waypoint");
		ImGui::SameLine();
		components::command_button<"objectivetp">({}, "Objective");
		components::command_checkbox<"autotptowp">();

		ImGui::Text("VEHICLES"_T.data());
		components::command_button<"lastvehtp">();
		ImGui::SameLine();
		components::command_button<"bringpv">();
		ImGui::SameLine();
		components::command_button<"pvtp">();

		components::title("GUI_TAB_IPL"_T.data());

		if (ImGui::BeginCombo("IPL_LOCATION"_T.data(), ipls[g.self.ipls.select].friendly_name))
		{
			for (int i = 0; i < IM_ARRAYSIZE(ipls); i++)
			{
				if (ImGui::Selectable(ipls[i].friendly_name, i == g.self.ipls.select))
					g.self.ipls.select = i;

				if (i == g.self.ipls.select)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		auto selected_ipl = ipls[g.self.ipls.select];
		if (components::button("LOAD_IPL"_T.data()))
		{
			//unload all previous ipls
			for (auto& ipl : ipls)
				for (auto& ipl_name : ipl.ipl_names)
				{
					if (STREAMING::IS_IPL_ACTIVE(ipl_name))
					{
						LOG(INFO) << "unloading existing ipl " << ipl_name;
						STREAMING::REMOVE_IPL(ipl_name);
					}
				}

			//load the new ipl
			for (auto& ipl_name : selected_ipl.ipl_names)
				STREAMING::REQUEST_IPL(ipl_name);
		}

		ImGui::SameLine();

		if (components::button("TP_TO_IPL"_T.data()))
		{
			PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped,
			    selected_ipl.location.x,
			    selected_ipl.location.y,
			    selected_ipl.location.z);
		}

		components::sub_title("IPL_INFOS"_T.data());
		ImGui::Text(std::vformat("IPL_CNT"_T, std::make_format_args(selected_ipl.ipl_names.size())).data());
		ImGui::Text(std::vformat("IPL_POSITION"_T,
		    std::make_format_args(selected_ipl.location.x, selected_ipl.location.y, selected_ipl.location.z))
		                .data());
	}
}
