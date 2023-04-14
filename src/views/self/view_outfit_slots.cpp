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

			static outfit::outfit_t outfit;

			g_fiber_pool->queue_job([] {
				for (auto& item : outfit.components)
				{
					item.drawable_id     = *outfit::get_component_drawable_id_address(slot, item.id);
					item.drawable_id_max = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(self::ped, item.id) - 1;

					item.texture_id = *outfit::get_component_texture_id_address(slot, item.id);
					item.texture_id_max = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(self::ped, item.id, item.drawable_id) - 1;
				}

				for (auto& item : outfit.props)
				{
					item.drawable_id     = *outfit::get_prop_drawable_id_address(slot, item.id);
					item.drawable_id_max = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(self::ped, item.id) - 1;

					item.texture_id = *outfit::get_prop_texture_id_address(slot, item.id);
					item.texture_id_max = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(self::ped, item.id, item.drawable_id) - 1;
				}
			});

			components::button("EXPORT_TO_CLIPBOARD"_T, [] {
				ImGui::SetClipboardText(outfit.export_to_clipboard().c_str());
				g_notification_service->push("OUTFIT"_T.data(), "EXPORT_TO_CLIPBOARD"_T.data());
			});
			ImGui::SameLine();

			components::button("IMPORT_FROM_CLIPBOARD"_T, [] {
				outfit.import_from_clipboard(ImGui::GetClipboardText());
				for (auto& item : outfit.components)
				{
					*outfit::get_component_drawable_id_address(slot, item.id) = item.drawable_id;
					*outfit::get_component_texture_id_address(slot, item.id)  = item.texture_id;
				}
				for (auto& item : outfit.props)
				{
					*outfit::get_prop_drawable_id_address(slot, item.id) = item.drawable_id;
					*outfit::get_prop_texture_id_address(slot, item.id)  = item.texture_id;
				}
			});

			ImGui::BeginGroup();
			for (auto& item : outfit.components)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt(std::format("{} [0,{}]", item.label, item.drawable_id_max).c_str(), outfit::get_component_drawable_id_address(slot, item.id), 0);
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			for (auto& item : outfit.components)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt(std::format("{} {} [0,{}]", item.label, "OUTFIT_TEX"_T, item.texture_id_max).c_str(), outfit::get_component_texture_id_address(slot, item.id), 0);
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			for (auto& item : outfit.props)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt(std::format("{} [0,{}]", item.label, item.drawable_id_max).c_str(), outfit::get_prop_drawable_id_address(slot, item.id), 0);
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			for (auto& item : outfit.props)
			{
				ImGui::SetNextItemWidth(60);
				ImGui::InputInt(std::format("{} {} [0,{}]", item.label, "OUTFIT_TEX"_T, item.texture_id_max).c_str(), outfit::get_prop_texture_id_address(slot, item.id), 0);
			}
			ImGui::EndGroup();
		}
	}
}