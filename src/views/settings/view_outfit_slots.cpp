#include "natives.hpp"
#include "pointers.hpp"
#include "util/outfit.hpp"
#include "views/view.hpp"

namespace big
{
	void view::outfit_slots()
	{
		if (*g_pointers->m_script_globals)
		{
			static int slot = 0;
			ImGui::SetNextItemWidth(160);
			if (ImGui::InputInt("Slot", &slot))
			{
				if (slot < 0)
					slot = 19;
				if (slot > 19)
					slot = 0;
			}

			ImGui::SetNextItemWidth(300);
			ImGui::InputText("Name", outfit::get_slot_name_address(slot), 16);

			struct outfit_t
			{
				int id;
				std::string label;
				int drawable_id     = 0;
				int drawable_id_max = 0;
				int texture_id      = 0;
				int texture_id_max  = 0;
			};

			static std::vector<outfit_t> components = {{0, "HEAD"}, {1, "BERD"}, {2, "HAIR"}, {3, "UPPR"}, {4, "LOWR"}, {5, "HAND"}, {6, "FEET"}, {7, "TEEF"}, {8, "ACCS"}, {9, "TASK"}, {10, "DECL"}, {11, "JBIB"}};
			static std::vector<outfit_t> props      = {{0, "HEAD"}, {1, "GLASSES"}, {2, "EARS"}, {3, "UNK1"}, {4, "UNK2"}, {5, "UNK3"}, {6, "WATCH"}, {7, "WRIST"}, {8, "UNK4"}};

			g_fiber_pool->queue_job([] {
				for (auto& item : components)
				{
					item.drawable_id     = *outfit::get_component_drawable_id_address(slot, item.id);
					item.drawable_id_max = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(self::ped, item.id) - 1;

					item.texture_id = *outfit::get_component_texture_id_address(slot, item.id);
					item.texture_id_max = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(self::ped, item.id, item.drawable_id) - 1;
				}

				for (auto& item : props)
				{
					item.drawable_id     = *outfit::get_prop_drawable_id_address(slot, item.id);
					item.drawable_id_max = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(self::ped, item.id) - 1;

					item.texture_id = *outfit::get_prop_texture_id_address(slot, item.id);
					item.texture_id_max = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(self::ped, item.id, item.drawable_id) - 1;
				}
			});

			components::button("Export To Clipboard", [] {
				std::stringstream ss;
				for (auto& item : components)
					ss << item.drawable_id << " " << item.texture_id << " ";
				for (auto& item : props)
					ss << item.drawable_id << " " << item.texture_id << " ";
				ImGui::SetClipboardText(ss.str().c_str());
				g_notification_service->push("Outfit", "Export to clipboard");
			});
			ImGui::SameLine();

			components::button("Import From Clipboard", [] {
				std::stringstream ss(ImGui::GetClipboardText());
				for (auto& item : components)
				{
					int draw_id    = 0;
					int texture_id = 0;
					ss >> draw_id;
					ss >> texture_id;
					*outfit::get_component_drawable_id_address(slot, item.id) = draw_id;
					*outfit::get_component_texture_id_address(slot, item.id)  = texture_id;
				}
				for (auto& item : props)
				{
					int draw_id    = 0;
					int texture_id = 0;
					ss >> draw_id;
					ss >> texture_id;
					*outfit::get_prop_drawable_id_address(slot, item.id) = draw_id;
					*outfit::get_prop_texture_id_address(slot, item.id)  = texture_id;
				}
			});

			ImGui::BeginGroup();
			for (auto& item : components)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt((item.label + " [0," + std::to_string(item.drawable_id_max) + "]").c_str(), outfit::get_component_drawable_id_address(slot, item.id), ImGuiInputTextFlags_None);
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			for (auto& item : components)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt((item.label + " TEX" + +" [0," + std::to_string(item.texture_id_max) + "]").c_str(), outfit::get_component_texture_id_address(slot, item.id), ImGuiInputTextFlags_None);
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			for (auto& item : props)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt((item.label + " [0," + std::to_string(item.drawable_id_max) + "]").c_str(), outfit::get_prop_drawable_id_address(slot, item.id), ImGuiInputTextFlags_None);
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			for (auto& item : props)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt((item.label + " TEX" + +" [0," + std::to_string(item.texture_id_max) + "]").c_str(), outfit::get_prop_texture_id_address(slot, item.id), ImGuiInputTextFlags_None);
			}
			ImGui::EndGroup();
		}
	}
}