#include "natives.hpp"
#include "util/outfit.hpp"
#include "util/ped.hpp"
#include "views/view.hpp"
#include "services/outfit/outfit_service.hpp"

namespace big
{
	void view::outfit_editor()
	{
		static outfit::components_t components;
		static outfit::props_t props;

		g_fiber_pool->queue_job([] {
			for (auto& item : components.items)
			{
				item.drawable_id     = PED::GET_PED_DRAWABLE_VARIATION(self::ped, item.id);
				item.drawable_id_max = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(self::ped, item.id) - 1;

				item.texture_id = PED::GET_PED_TEXTURE_VARIATION(self::ped, item.id);
				item.texture_id_max = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(self::ped, item.id, item.drawable_id) - 1;
			}

			for (auto& item : props.items)
			{
				item.drawable_id     = PED::GET_PED_PROP_INDEX(self::ped, item.id, 1);
				item.drawable_id_max = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(self::ped, item.id) - 1;

				item.texture_id = PED::GET_PED_PROP_TEXTURE_INDEX(self::ped, item.id);
				item.texture_id_max = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(self::ped, item.id, item.drawable_id) - 1;
			}
		});

		components::sub_title("VIEW_OUTFIT_EDITOR_TIP"_T);

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
			std::stringstream ss;
			for (auto& item : components.items)
				ss << item.id << " " << item.drawable_id << " " << item.texture_id << " ";
			for (auto& item : props.items)
				ss << item.id << " " << item.drawable_id << " " << item.texture_id << " ";
			ImGui::SetClipboardText(ss.str().c_str());
			g_notification_service.push_success("OUTFIT"_T.data(), "EXPORT_TO_CLIPBOARD"_T.data());
		});
		ImGui::SameLine();

		components::button("IMPORT_FROM_CLIPBOARD"_T, [] {
			std::stringstream ss(ImGui::GetClipboardText());
			for (auto& item : components.items)
			{
				int id          = 0;
				int drawable_id = 0;
				int texture_id  = 0;
				ss >> id;
				ss >> drawable_id;
				ss >> texture_id;
				PED::SET_PED_COMPONENT_VARIATION(self::ped, id, drawable_id, texture_id, PED::GET_PED_PALETTE_VARIATION(self::ped, id));
			}
			for (auto& item : props.items)
			{
				int id          = 0;
				int drawable_id = 0;
				int texture_id  = 0;
				ss >> id;
				ss >> drawable_id;
				ss >> texture_id;
				if (drawable_id == -1)
					PED::CLEAR_PED_PROP(self::ped, id, 1);
				else
				{
					PED::SET_PED_PROP_INDEX(self::ped, id, drawable_id, texture_id, TRUE, 1);
					if (id == 0)
					{
						//Prevent ped from taking helmet off.
						PED::SET_PED_HELMET_PROP_INDEX(self::ped, drawable_id, 0);
						PED::SET_PED_HELMET_TEXTURE_INDEX(self::ped, texture_id);
						PED::SET_PED_CONFIG_FLAG(self::ped, 34, true);
						if (!PED::IS_PED_ON_ANY_BIKE(self::ped))
							PED::SET_PED_CONFIG_FLAG(self::ped, 36, true);
					}
				}
			}
		});

		ImGui::BeginGroup();
		for (auto& item : components.items)
		{
			ImGui::SetNextItemWidth(120);
			if (ImGui::InputInt(std::format("{} [0,{}]##1", item.label, item.drawable_id_max).c_str(), &item.drawable_id))
			{
				outfit::check_bounds_drawable(&item, 0); // The game does this on it's own but seems to crash if we call OOB values to fast.

				g_fiber_pool->queue_job([item] {
					PED::SET_PED_COMPONENT_VARIATION(self::ped, item.id, item.drawable_id, 0, PED::GET_PED_PALETTE_VARIATION(self::ped, item.id));
				});
			}
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		for (auto& item : components.items)
		{
			ImGui::SetNextItemWidth(120);
			if (ImGui::InputInt(std::format("{} {} [0,{}]##2", item.label, "OUTFIT_TEX"_T, item.texture_id_max).c_str(), &item.texture_id))
			{
				outfit::check_bounds_texture(&item, 0); // The game does this on it's own but seems to crash if we call OOB values to fast.

				g_fiber_pool->queue_job([item] {
					PED::SET_PED_COMPONENT_VARIATION(self::ped, item.id, item.drawable_id, item.texture_id, PED::GET_PED_PALETTE_VARIATION(self::ped, item.id));
				});
			}
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		for (auto& item : props.items)
		{
			ImGui::SetNextItemWidth(120);
			if (ImGui::InputInt(std::format("{} [0,{}]##3", item.label, item.drawable_id_max).c_str(), &item.drawable_id))
			{
				outfit::check_bounds_drawable(&item, -1); // The game does this on it's own but seems to crash if we call OOB values to fast.

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
		for (auto& item : props.items)
		{
			ImGui::SetNextItemWidth(120);
			if (ImGui::InputInt(std::format("{} {} [0,{}]##4", item.label, "OUTFIT_TEX"_T, item.texture_id_max).c_str(), &item.texture_id))
			{
				outfit::check_bounds_texture(&item, -1); // The game does this on it's own but seems to crash if we call OOB values to fast.

				g_fiber_pool->queue_job([item] {
					PED::SET_PED_PROP_INDEX(self::ped, item.id, item.drawable_id, item.texture_id, TRUE, 1);
				});
			}
		}
		ImGui::EndGroup();

		ImGui::Separator();

		static char outfit_name[MAX_PATH] = {};
		static folder saved_outfit_path   = g_file_manager.get_project_folder("saved_outfits");
		std::vector<std::string> saved_outfits;
		for (const auto& directory_entry : std::filesystem::directory_iterator(saved_outfit_path.get_path()))
			saved_outfits.push_back(directory_entry.path().filename().generic_string());
		static int selected_index = -1;

		ImGui::SetNextItemWidth(300);

		ImGui::InputText("##outfit_name", outfit_name, sizeof(outfit_name));
		if (ImGui::IsItemActive())
			g.self.hud.typing = TYPING_TICKS;
		ImGui::SameLine();

		components::button("OUTFIT_SAVE_CURRENT"_T, [] {
			size_t index    = 0;
			std::string str = outfit_name;
			while (saved_outfit_path.get_file(str + ".json").exists())
				str = std::format("{}({})", outfit_name, ++index);

			outfit_service::save_outfit(str + ".json");
		});
		ImGui::SameLine();

		components::button("OUTFIT_APPLY_SELECTED"_T, [saved_outfits] {
			if (selected_index >= 0 && selected_index < saved_outfits.size())
			{
				std::ifstream i(saved_outfit_path.get_file(saved_outfits[selected_index]).get_path());
				nlohmann::json j;
				i >> j;

				outfit_service::apply_outfit(j, true);
			}
		});
		ImGui::SameLine();

		components::button("OUTFIT_DELETE_SELECTED"_T, [saved_outfits] {
			if (selected_index >= 0 && selected_index < saved_outfits.size())
			{
				std::filesystem::remove(saved_outfit_path.get_file(saved_outfits[selected_index]).get_path());
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
		ImGui::SameLine();
		ImGui::BeginGroup();
		if (ImGui::Button("VIEW_SELF_OUTFIT_SET_PERSIST_OUTFIT"_T.data()))
		{
			g.self.persist_outfit = saved_outfits[selected_index];
		}
		ImGui::SameLine();
		if (ImGui::Button("VIEW_SELF_OUTFIT_CLEAR_PERSIST_OUTFIT"_T.data()))
		{
			g.self.persist_outfit.clear();
		}
		ImGui::SameLine();
		ImGui::Checkbox("VIEW_SELF_OUTFIT_DISABLE_DURING_MISSIONS"_T.data(), &g.self.persist_outfits_mis);
		ImGui::Text(std::format("{}: {}", "VIEW_SELF_OUTFIT_CURRENT_PERSISTED_OUTFIT"_T.data(), g.self.persist_outfit).c_str());
		ImGui::EndGroup();
	}
}
