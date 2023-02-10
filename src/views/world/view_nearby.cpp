#include "views/view.hpp"
#include "util/local_player.hpp"
#include "util/entity.hpp"
#include "util/ped.hpp"

namespace big
{
	void view::nearby()
	{
		components::sub_title("Peds");
		components::button("Delete", [] { for (auto peds : entity::get_entities(false, true)) entity::delete_entity(peds); }); ImGui::SameLine();
		components::button("Kill", [] { for (auto peds : entity::get_entities(false, true)) ped::kill_ped(peds); }, ImVec2(0, 0), ImVec4(0.95f, 0.2f, 0.2f, 1.f));
		components::command_checkbox<"pedsignore">(); ImGui::SameLine(140.f);
		components::command_checkbox<"pedrain">(); 
		components::command_checkbox<"highalert">(); ImGui::SameLine(140.f);
		components::command_checkbox<"pedrush">();
		components::sub_title("Vehicles");
		

		
	}
}