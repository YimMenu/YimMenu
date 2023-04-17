#include "views/view.hpp"

namespace big
{
	void view::player_vehicle()
	{
		if (ImGui::TreeNode("Vehicle"))
		{
			components::player_command_button<"vehkick">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"flyingveh">(g_player_service->get_selected(), {});

			components::player_command_button<"boostveh">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"stopveh">(g_player_service->get_selected(), {});

			components::player_command_button<"flip180">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"rcplayer">(g_player_service->get_selected(), {});

			components::player_command_button<"killengine">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"burstwheels">(g_player_service->get_selected(), {});

			components::player_command_button<"smashwindows">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"blacktint">(g_player_service->get_selected(), {});

			components::player_command_button<"lockveh">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"unlockveh">(g_player_service->get_selected(), {});

			components::player_command_button<"opendoors">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"closedoors">(g_player_service->get_selected(), {});

			components::player_command_button<"upgradeveh">(g_player_service->get_selected(), {});
			ImGui::SameLine();
			components::player_command_button<"downgradeveh">(g_player_service->get_selected(), {});

			ImGui::TreePop();
		}
	}
}