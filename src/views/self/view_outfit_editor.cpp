#include "natives.hpp"
#include "pointers.hpp"
#include "util/outfit.hpp"
#include "util/ped.hpp"
#include "views/view.hpp"

namespace big
{
	void view::outfit_editor()
	{
		static outfit::outfit_t outfit;

		g_fiber_pool->queue_job([] {
			outfit.update(self::ped);
		});

		components::button("OUTFIT_RANDOM_COMPONENT"_T, [] {
			ped::set_ped_random_component_variation(self::ped);
		});
		ImGui::SameLine();

		components::button("OUTFIT_DEFAULT_COMPONENT"_T, [] {
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(self::ped);
		});
		ImGui::SameLine();

		components::button("OUTFIT_RANDOM_PROPS"_T, [] {
			PED::SET_PED_RANDOM_PROPS(self::ped);
		});
		ImGui::SameLine();

		components::button("OUTFIT_CLEAR_PROPS"_T, [] {
			PED::CLEAR_ALL_PED_PROPS(self::ped, 1);
		});
		ImGui::SameLine();

		components::button("EXPORT_TO_CLIPBOARD"_T, [] {
			ImGui::SetClipboardText(outfit.export_to_clipboard().c_str());
			g_notification_service->push("OUTFIT"_T.data(), "EXPORT_TO_CLIPBOARD"_T.data());
		});
		ImGui::SameLine();

		components::button("IMPORT_FROM_CLIPBOARD"_T, [] {
			outfit.import_from_clipboard(ImGui::GetClipboardText());
			outfit.apply(self::ped);
		});

		ImGui::BeginGroup();
		for (auto& item : outfit.components)
		{
			ImGui::SetNextItemWidth(60);
			if (ImGui::InputInt(std::format("{} [0,{}]", item.label, item.drawable_id_max).c_str(), &item.drawable_id, 0))
			{
				g_fiber_pool->queue_job([item] {
					PED::SET_PED_COMPONENT_VARIATION(self::ped, item.id, item.drawable_id, 0, PED::GET_PED_PALETTE_VARIATION(self::ped, item.id));
				});
			}
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		for (auto& item : outfit.components)
		{
			ImGui::SetNextItemWidth(60);
			if (ImGui::InputInt(std::format("{} {} [0,{}]", item.label, "OUTFIT_TEX"_T, item.texture_id_max).c_str(), &item.texture_id, 0))
			{
				g_fiber_pool->queue_job([item] {
					PED::SET_PED_COMPONENT_VARIATION(self::ped, item.id, item.drawable_id, item.texture_id, PED::GET_PED_PALETTE_VARIATION(self::ped, item.id));
				});
			}
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		for (auto& item : outfit.props)
		{
			ImGui::SetNextItemWidth(60);
			if (ImGui::InputInt(std::format("{} [0,{}]", item.label, item.drawable_id_max).c_str(), &item.drawable_id, 0))
			{
				g_fiber_pool->queue_job([item] {
					if (item.drawable_id == -1)
						PED::CLEAR_PED_PROP(self::ped, item.id, 1);
					else
						PED::SET_PED_PROP_INDEX(self::ped, item.id, item.drawable_id, 0, TRUE, 1);
				});
			}
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		for (auto& item : outfit.props)
		{
			ImGui::SetNextItemWidth(60);
			if (ImGui::InputInt(std::format("{} {} [0,{}]", item.label, "OUTFIT_TEX"_T, item.texture_id_max).c_str(), &item.texture_id, 0))
			{
				g_fiber_pool->queue_job([item] {
					PED::SET_PED_PROP_INDEX(self::ped, item.id, item.drawable_id, item.texture_id, TRUE, 1);
				});
			}
		}
		ImGui::EndGroup();

		ImGui::Separator();

		static char outfit_name[MAX_PATH]      = {};
		std::vector<std::string> saved_outfits = outfit.get_outfits();
		static int selected_index              = -1;

		ImGui::SetNextItemWidth(300);

		ImGui::InputText("##outfit_name", outfit_name, sizeof(outfit_name));
		ImGui::SameLine();

		components::button("OUTFIT_SAVE_CURRENT"_T, [] {
			size_t index               = 0;
			std::filesystem::path name = outfit_name;
			std::string og_name        = name.stem().string();
			if (name.extension() != ".json")
				name += ".json";
			while (std::filesystem::exists(outfit.get_path(name)))
				name.replace_filename(std::format("{}({})", og_name, ++index));
			outfit.save_json(name);
		});
		ImGui::SameLine();

		components::button("OUTFIT_APPLY_SELECTED"_T, [saved_outfits] {
			if (selected_index >= 0 && selected_index < saved_outfits.size())
			{
				outfit.load_json(saved_outfits[selected_index]);
				outfit.apply(self::ped);
			}
		});
		ImGui::SameLine();

		components::button("OUTFIT_DELETE_SELECTED"_T, [saved_outfits] {
			if (selected_index >= 0 && selected_index < saved_outfits.size())
			{
				std::filesystem::remove(outfit.get_path(saved_outfits[selected_index]));
				if (selected_index == saved_outfits.size() - 1)
					--selected_index;
			}
		});

		if (ImGui::BeginListBox("##outfit_editor_list_box", ImVec2(300, 0)))
		{
			for (size_t i = 0; i < saved_outfits.size(); i++)
				if (ImGui::Selectable(saved_outfits[i].c_str(), selected_index == i))
					selected_index = i;
			ImGui::EndListBox();
		}
	}
}