#include "fiber_pool.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"
#include "views/view.hpp"


namespace big
{
	void view::missile()
	{
		ImGui::Text("Missile Launch");

		static player_ptr victim = g_player_service->get_selected();
		ImGui::SeparatorText("Victim");

		if (ImGui::BeginCombo("##victim", victim->get_name()))
		{
			auto self = g_player_service->get_self();
			if (ImGui::Selectable(self->get_name(), self->id() == victim->id()))
				victim = self;
			for (auto player : g_player_service->players() | std::ranges::views::values)
			{
				if (ImGui::Selectable(player->get_name(), player->id() == victim->id()))
				{
					victim = player;
					if (g.player.spectating)
					{
						g_player_service->set_selected(victim);
					}
				}
			}
			ImGui::EndCombo();
		}
		if (ImGui::Button("Launch"))
		{
			if (victim != nullptr)
			{
				g_fiber_pool->queue_job([] {
					auto& pos = *victim->get_ped()->get_position();
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(pos.x, pos.y, pos.z + 100.0f, pos.x, pos.y, pos.z, 9999, true, RAGE_JOAAT("VEHICLE_WEAPON_SPACE_ROCKET"), self::ped, true, false, 90.0f);
				});
			}
		}
	}

}
