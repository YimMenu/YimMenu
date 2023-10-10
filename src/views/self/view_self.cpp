
#include "core/scr_globals.hpp"
#include "core/settings.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "util/pools.hpp"
#include "views/view.hpp"

#include <script/globals/GPBD_FM_3.hpp>

namespace big
{
	void view::self()
	{
		ImGui::Spacing();
		{
			components::command_button<"suicide">();
			ImGui::SameLine();
			components::command_button<"clearwantedlvl">();

			ImGui::SameLine(0, 2.0f * ImGui::GetTextLineHeight());

			components::command_button<"heal">();
			ImGui::SameLine();
			components::command_button<"clean">();
		}
		ImGui::SeparatorText("###self_checkboxs");
		{
			ImGui::BeginGroup();
			{
				components::command_checkbox<"godmode">();
				components::command_checkbox<"nophone">();
				components::command_checkbox<"infoxy">();
				components::command_checkbox<"noragdoll">();
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				const auto gpbd_fm_3 = scr_globals::gpbd_fm_3.as<GPBD_FM_3*>();

				components::command_checkbox<"noidlekick">();
				components::command_checkbox<"cleanloop">();
				components::command_checkbox<"otr">();
				if (g.self.off_radar && *g_pointers->m_gta.m_is_session_started && gpbd_fm_3->Entries[self::id].BossGoon.Boss == self::id)
					components::command_checkbox<"ghostorg">();

				ImGui::BeginDisabled(!*g_pointers->m_gta.m_is_session_started || gpbd_fm_3->Entries[self::id].BossGoon.Boss != -1 || gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller")) || gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")));
				components::command_checkbox<"passive">();
				ImGui::EndDisabled();
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				components::command_checkbox<"freecam">();
				components::command_checkbox<"noclip">();
				components::options_modal("Noclip", [] {
					ImGui::Separator();

					ImGui::BeginGroup();
					ImGui::Text("No Clip Movement Speed Multiplier While Aiming");
					ImGui::SliderFloat("##noclipaimspeedmult", &g.self.noclip_aim_speed_multiplier, 0.1f, 1.0f);
					ImGui::Text("No Clip Movement Speed Multiplier");
					ImGui::SliderFloat("##noclipspeedmult", &g.self.noclip_speed_multiplier, 1.f, 100.f);
					ImGui::EndGroup();
				});
				ImGui::Checkbox("Context Menu Enabled", &g.context_menu.enabled);
				components::options_modal("Context Menu Enabled", [] {
					ImGui::Text("Allowed Entity Types:");
					ImGui::CheckboxFlags("Object", reinterpret_cast<int*>(&g.context_menu.allowed_entity_types), static_cast<int>(ContextEntityType::OBJECT));
					ImGui::SameLine();
					ImGui::CheckboxFlags("Ped", reinterpret_cast<int*>(&g.context_menu.allowed_entity_types), static_cast<int>(ContextEntityType::PED));
					ImGui::SameLine();
					ImGui::CheckboxFlags("Player", reinterpret_cast<int*>(&g.context_menu.allowed_entity_types), static_cast<int>(ContextEntityType::PLAYER));
					ImGui::SameLine();
					ImGui::CheckboxFlags("Vehicle", reinterpret_cast<int*>(&g.context_menu.allowed_entity_types), static_cast<int>(ContextEntityType::VEHICLE));

					static ImVec4 selected_option_color = ImGui::ColorConvertU32ToFloat4(g.context_menu.selected_option_color);
					ImGui::Text("Selected Option Color:");
					if (ImGui::ColorEdit4("###BSelected Option Color##cm_picker", (float*)&selected_option_color, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
					{
						g.context_menu.selected_option_color = ImGui::ColorConvertFloat4ToU32(selected_option_color);
					}

					ImGui::Checkbox("Bounding Box Enabled", &g.context_menu.bounding_box_enabled);

					if (g.context_menu.bounding_box_enabled)
					{
						static ImVec4 bounding_box_color = ImGui::ColorConvertU32ToFloat4(g.context_menu.bounding_box_color);
						ImGui::Text("Bounding Box Color:");
						if (ImGui::ColorEdit4("###Bounding Box Color##cm_picker", (float*)&bounding_box_color, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
						{
							g.context_menu.bounding_box_color = ImGui::ColorConvertFloat4ToU32(bounding_box_color);
						}
					}
				});
			}
			ImGui::EndGroup();
		}
		ImGui::Spacing();
		ImGui::SeparatorText("###otherselfOptions");
		{
			static bool hideRadar = false;

			components::command_button<"skipcutscene">();
			ImGui::SameLine();
			components::command_button<"fillsnacks">();
			ImGui::SameLine();
			components::button("Clear Attachments", [] {
				for (auto obj : pools::get_all_props())
				{
					auto object = g_pointers->m_gta.m_ptr_to_handle(obj);
					if (!object)
						break;

					if (!ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(self::ped, object))
						continue;

					ENTITY::DELETE_ENTITY(&object);
				}
			});
			ImGui::SameLine();
			components::button("Hide Radar", [] {
				HUD::DISPLAY_RADAR(hideRadar = !hideRadar);
			});
		}
	}
}
