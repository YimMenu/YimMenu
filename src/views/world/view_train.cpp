#include "fiber_pool.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "views/view.hpp"
#include "util/train.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/model_preview/model_preview_service.hpp"
#include "services/players/player_service.hpp"

#include <imgui_internal.h>


namespace big
{
	void view::train()
	{
		components::button("Hijack Train", []
			{
				train::hijack_train();
			});

		ImGui::SameLine();
		
		components::button("Delete Train", []
			{
				train::delete_train();
			});

		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("You cant delete the train while in it.");
		
		ImGui::SameLine();
		
		components::button("Exit Train", []
			{
				train::exit_train();
			});
	
		static float train_speed = 0;

		ImGui::SliderFloat("Train Speed", &train_speed, -500.f, 500.f);
		ImGui::SameLine();
		components::button("Set", [] { train::set_train_speed(train_speed); });

		ImGui::Checkbox("Drive Train", &g.train.drive_train);
		
		ImGui::SameLine();
		
		ImGui::Checkbox("Derail Train", &g.train.derail_train);
		
	}
}