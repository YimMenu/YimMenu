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
			if (ImGui::InputInt("OUTFIT_SLOT"_T.data(), &slot))
			{
				if (slot < 0)
					slot = 19;
				if (slot > 19)
					slot = 0;
			}

			ImGui::SetNextItemWidth(300);
			ImGui::InputText("OUTFIT_NAME"_T.data(), outfit::get_slot_name_address(slot), 16);

			struct outfit_t
			{
				int id;
				std::string label;
				int drawable_id     = 0;
				int drawable_id_max = 0;
				int texture_id      = 0;
				int texture_id_max  = 0;
			};

			static std::vector<outfit_t> components = {{0, "OUTFIT_HEAD"_T.data()},
			    {1, "OUTFIT_BERD"_T.data()},
			    {2, "OUTFIT_HAIR"_T.data()},
			    {3, "OUTFIT_UPPR"_T.data()},
			    {4, "OUTFIT_LOWR"_T.data()},
			    {5, "OUTFIT_HAND"_T.data()},
			    {6, "OUTFIT_FEET"_T.data()},
			    {7, "OUTFIT_TEEF"_T.data()},
			    {8, "OUTFIT_ACCS"_T.data()},
			    {9, "OUTFIT_TASK"_T.data()},
			    {10, "OUTFIT_DECL"_T.data()},
			    {11, "OUTFIT_JBIB"_T.data()}};
			static std::vector<outfit_t> props      = {{0, "OUTFIT_HEAD"_T.data()},
			         {1, "OUTFIT_GLASSES"_T.data()},
			         {2, "OUTFIT_EARS"_T.data()},
			         {3, "OUTFIT_UNK1"_T.data()},
			         {4, "OUTFIT_UNK2"_T.data()},
			         {5, "OUTFIT_UNK3"_T.data()},
			         {6, "OUTFIT_WATCH"_T.data()},
			         {7, "OUTFIT_WRIST"_T.data()},
			         {8, "OUTFIT_UNK4"_T.data()}};

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

			components::button("EXPORT_TO_CLIPBOARD"_T, [] {
				std::stringstream ss;
				for (auto& item : components)
					ss << item.id << " " << item.drawable_id << " " << item.texture_id << " ";
				for (auto& item : props)
					ss << item.id << " " << item.drawable_id << " " << item.texture_id << " ";
				ImGui::SetClipboardText(ss.str().c_str());
				g_notification_service->push("OUTFIT"_T.data(), "EXPORT_TO_CLIPBOARD"_T.data());
			});
			ImGui::SameLine();

			components::button("IMPORT_FROM_CLIPBOARD"_T, [] {
				std::stringstream ss(ImGui::GetClipboardText());
				for (auto& item : components)
				{
					int id         = 0;
					int draw_id    = 0;
					int texture_id = 0;
					ss >> id;
					ss >> draw_id;
					ss >> texture_id;
					*outfit::get_component_drawable_id_address(slot, id) = draw_id;
					*outfit::get_component_texture_id_address(slot, id)  = texture_id;
				}
				for (auto& item : props)
				{
					int id         = 0;
					int draw_id    = 0;
					int texture_id = 0;
					ss >> id;
					ss >> draw_id;
					ss >> texture_id;
					*outfit::get_prop_drawable_id_address(slot, id) = draw_id;
					*outfit::get_prop_texture_id_address(slot, id)  = texture_id;
				}
			});

			ImGui::BeginGroup();
			for (auto& item : components)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt(std::format("{} [0,{}]", item.label, item.drawable_id_max).c_str(), outfit::get_component_drawable_id_address(slot, item.id), ImGuiInputTextFlags_None);
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			for (auto& item : components)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt(std::format("{} {} [0,{}]", item.label, "OUTFIT_TEX"_T, item.texture_id_max).c_str(), outfit::get_component_texture_id_address(slot, item.id), ImGuiInputTextFlags_None);
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			for (auto& item : props)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt(std::format("{} [0,{}]", item.label, item.drawable_id_max).c_str(), outfit::get_prop_drawable_id_address(slot, item.id), ImGuiInputTextFlags_None);
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			for (auto& item : props)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt(std::format("{} {} [0,{}]", item.label, "OUTFIT_TEX"_T, item.texture_id_max).c_str(), outfit::get_prop_texture_id_address(slot, item.id), ImGuiInputTextFlags_None);
			}
			ImGui::EndGroup();
		}
	}
}