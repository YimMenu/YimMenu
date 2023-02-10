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
		components::button("Kill", [] { for (auto peds : entity::get_entities(false, true)) ped::kill_ped(peds); }); 

		components::sub_title("Vehicles");
		

		
	}
}