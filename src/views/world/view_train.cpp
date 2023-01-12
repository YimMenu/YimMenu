#include "views/view.hpp"
#include "util/train.hpp"

#include <imgui_internal.h>


namespace big
{
	void view::train()
	{
		components::button("HIJACK_TRAIN"_T.data(), []
			{
				train::hijack_train();
			});

		ImGui::SameLine();
		
		components::button("DELETE_TRAIN"_T.data(), []
			{
				train::delete_train();
			});

		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("DELETE_TRAIN_DESC"_T.data());
		
		ImGui::SameLine();
		
		components::button("EXIT_TRAIN"_T.data(), []
			{
				train::exit_train();
			});
	
		static float train_speed = 0;

		ImGui::SliderFloat("TRAIN_SPEED"_T.data(), &train_speed, -500.f, 500.f);
		ImGui::SameLine();
		components::button("SET"_T.data(), [] { train::set_train_speed(train_speed); });

		ImGui::Checkbox("DRIVE_TRAIN"_T.data(), &g.train.drive_train);
		
		ImGui::SameLine();
		
		ImGui::Checkbox("DERAIL_TRAIN"_T.data(), &g.train.derail_train);
		
	}
}