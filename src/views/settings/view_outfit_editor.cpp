#include "natives.hpp"
#include "pointers.hpp"
#include "views/view.hpp"

namespace big
{
	void view::outfit_editor()
	{
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
				item.drawable_id     = PED::GET_PED_DRAWABLE_VARIATION(self::ped, item.id);
				item.drawable_id_max = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(self::ped, item.id) - 1;

				item.texture_id     = PED::GET_PED_TEXTURE_VARIATION(self::ped, item.id);
				item.texture_id_max = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(self::ped, item.id, item.drawable_id) - 1;
			}

			for (auto& item : props)
			{
				item.drawable_id     = PED::GET_PED_PROP_INDEX(self::ped, item.id, 1);
				item.drawable_id_max = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(self::ped, item.id) - 1;

				item.texture_id = PED::GET_PED_PROP_TEXTURE_INDEX(self::ped, item.id);
				item.texture_id_max = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(self::ped, item.id, item.drawable_id) - 1;
			}
		});

		components::button("OUTFIT_RANDOM_COMPONENT"_T, [] {
			PED::SET_PED_RANDOM_COMPONENT_VARIATION(self::ped, 0);
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
				PED::SET_PED_COMPONENT_VARIATION(self::ped, id, draw_id, texture_id, PED::GET_PED_PALETTE_VARIATION(self::ped, id));
			}
			for (auto& item : props)
			{
				int id         = 0;
				int draw_id    = 0;
				int texture_id = 0;
				ss >> id;
				ss >> draw_id;
				ss >> texture_id;
				if (draw_id == -1)
					PED::CLEAR_PED_PROP(self::ped, id, 1);
				else
					PED::SET_PED_PROP_INDEX(self::ped, id, draw_id, texture_id, TRUE, 1);
			}
		});

		ImGui::BeginGroup();
		for (auto& item : components)
		{
			ImGui::SetNextItemWidth(60);
			if (ImGui::InputInt(std::format("{} [0,{}]", item.label, item.drawable_id_max).c_str(), &item.drawable_id, ImGuiInputTextFlags_None))
			{
				g_fiber_pool->queue_job([item] {
					PED::SET_PED_COMPONENT_VARIATION(self::ped, item.id, item.drawable_id, 0, PED::GET_PED_PALETTE_VARIATION(self::ped, item.id));
				});
			}
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		for (auto& item : components)
		{
			ImGui::SetNextItemWidth(60);
			if (ImGui::InputInt(std::format("{} {} [0,{}]", item.label, "OUTFIT_TEX"_T, item.texture_id_max).c_str(), &item.texture_id, ImGuiInputTextFlags_None))
			{
				g_fiber_pool->queue_job([item] {
					PED::SET_PED_COMPONENT_VARIATION(self::ped, item.id, item.drawable_id, item.texture_id, PED::GET_PED_PALETTE_VARIATION(self::ped, item.id));
				});
			}
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		for (auto& item : props)
		{
			ImGui::SetNextItemWidth(60);
			if (ImGui::InputInt(std::format("{} [0,{}]", item.label, item.drawable_id_max).c_str(), &item.drawable_id, ImGuiInputTextFlags_None))
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
		for (auto& item : props)
		{
			ImGui::SetNextItemWidth(60);
			if (ImGui::InputInt(std::format("{} {} [0,{}]", item.label, "OUTFIT_TEX"_T, item.texture_id_max).c_str(), &item.texture_id, ImGuiInputTextFlags_None))
			{
				g_fiber_pool->queue_job([item] {
					PED::SET_PED_PROP_INDEX(self::ped, item.id, item.drawable_id, item.texture_id, TRUE, 1);
				});
			}
		}
		ImGui::EndGroup();

		ImGui::Separator();

		static char outfit_name[MAX_PATH] = {};
		static folder saved_outfit_path   = g_file_manager->get_project_folder("saved_outfits");
		std::vector<std::string> saved_outfits;
		for (const auto& directory_entry : std::filesystem::directory_iterator(saved_outfit_path.get_path()))
			saved_outfits.push_back(directory_entry.path().filename().generic_string());
		static int selected_index = -1;

		ImGui::SetNextItemWidth(300);

		ImGui::InputText("##outfit_name", outfit_name, sizeof(outfit_name));
		ImGui::SameLine();

		components::button("OUTFIT_SAVE_CURRENT"_T, [] {
			if (outfit_name[0] != '\0')
			{
				nlohmann::json j;
				nlohmann::json j_components;
				nlohmann::json j_props;

				for (auto& item : components)
				{
					nlohmann::json tmp;
					tmp["drawable_id"]                    = item.drawable_id;
					tmp["texture_id"]                     = item.texture_id;
					j_components[std::to_string(item.id)] = tmp;
				}

				for (auto& item : props)
				{
					nlohmann::json tmp;
					tmp["drawable_id"]               = item.drawable_id;
					tmp["texture_id"]                = item.texture_id;
					j_props[std::to_string(item.id)] = tmp;
				}

				j["components"] = j_components;
				j["props"]      = j_props;

				size_t index    = 0;
				std::string str = outfit_name;
				while (saved_outfit_path.get_file(str + ".json").exists())
					str = std::format("{} ({})", outfit_name, ++index);

				std::ofstream o(saved_outfit_path.get_file(str + ".json").get_path());
				o << std::setw(4) << j << std::endl;
			}
		});
		ImGui::SameLine();

		components::button("OUTFIT_APPLY_SELECTED"_T, [saved_outfits] {
			if (selected_index >= 0 && selected_index < saved_outfits.size())
			{
				std::ifstream i(saved_outfit_path.get_file(saved_outfits[selected_index]).get_path());
				nlohmann::json j;
				i >> j;

				for (auto& item : j["components"].items())
				{
					std::stringstream ss(item.key());
					int id = 0;
					ss >> id;
					int draw_id    = item.value()["draw_id"];
					int texture_id = item.value()["texture_id"];
					PED::SET_PED_COMPONENT_VARIATION(self::ped, id, draw_id, texture_id, PED::GET_PED_PALETTE_VARIATION(self::ped, id));
				}

				for (auto& item : j["props"].items())
				{
					std::stringstream ss(item.key());
					int id = 0;
					ss >> id;
					int draw_id    = item.value()["draw_id"];
					int texture_id = item.value()["texture_id"];
					if (draw_id == -1)
						PED::CLEAR_PED_PROP(self::ped, id, 1);
					else
						PED::SET_PED_PROP_INDEX(self::ped, id, draw_id, texture_id, TRUE, 1);
				}
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
	}
}