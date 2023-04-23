#include "core/data/ipls.hpp"
#include "util/local_player.hpp"
#include "views/view.hpp"

namespace big
{
	void view::ipl()
	{
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
		ImGui::Text(std::vformat("IPL_POSITION"_T, std::make_format_args(selected_ipl.location.x, selected_ipl.location.y, selected_ipl.location.z)).data());
	}
}