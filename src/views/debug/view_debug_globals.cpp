#include "gui/components/components.hpp"
#include "script_global.hpp"
#include "thread_pool.hpp"
#include "view_debug.hpp"

namespace big
{
	enum GlobalAppendageType : int
	{
		GlobalAppendageType_At,
		GlobalAppendageType_ReadGlobal,
		GlobalAppendageType_PlayerId,
	};

	struct global_debug_inner
	{
		GlobalAppendageType type{};
		std::ptrdiff_t index{};
		std::size_t size{};
		std::string global_name{};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(global_debug_inner, type, index, size, global_name)
	};

	struct global_debug
	{
		std::size_t global_index{};
		std::vector<global_debug_inner> global_appendages{};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(global_debug, global_index, global_appendages)
	};

	nlohmann::json get_globals_json()
	{
		nlohmann::json globals{};

		auto file = g_file_manager.get_project_file("./globals.json");
		if (file.exists())
		{
			std::ifstream iffstream_file(file.get_path());
			iffstream_file >> globals;
		}

		return globals;
	}

	void load_global_menu(const std::string& selected_global, global_debug& global_obj)
	{
		if (!selected_global.empty())
		{
			auto globals = get_globals_json();
			if (globals[selected_global].is_null())
				return;
			global_obj = globals[selected_global].get<global_debug>();
		}
	}

	int64_t* get_global_ptr(global_debug& global_test)
	{
		script_global global_to_read = script_global(global_test.global_index);
		for (auto item : global_test.global_appendages)
		{
			if (item.type == GlobalAppendageType_At)
			{
				if (item.size != 0)
					global_to_read = global_to_read.at(item.index, item.size);
				else
					global_to_read = global_to_read.at(item.index);
			}
			else if (item.type == GlobalAppendageType_ReadGlobal)
			{
				global_debug global_read;
				load_global_menu(item.global_name, global_read);
				if (auto ptr = get_global_ptr(global_read))
					if (item.size != 0)
						global_to_read = global_to_read.at(*ptr, item.size);
					else
						global_to_read = global_to_read.at(*ptr);
				else
					LOG(WARNING) << "Failed to read " << item.global_name << "for get_global_ptr";
			}
			else if (item.type == GlobalAppendageType_PlayerId)
			{
				if (item.size != 0)
					global_to_read = global_to_read.at(self::id, item.size);
				else
					global_to_read = global_to_read.at(self::id);
			}
		}
		auto retn_val = global_to_read.as<int64_t*>();
		if ((size_t)retn_val < UINT32_MAX)
			return nullptr;
		return retn_val;
	}

	std::map<std::string, global_debug> list_globals()
	{
		auto json = get_globals_json();
		std::map<std::string, global_debug> return_value;
		for (auto& item : json.items())
			return_value[item.key()] = item.value();
		return return_value;
	}

	void save_global(char* global_name, global_debug& global_obj)
	{
		std::string teleport_name_string = global_name;
		if (!teleport_name_string.empty())
		{
			auto json                  = get_globals_json();
			json[teleport_name_string] = global_obj;

			auto file_path = g_file_manager.get_project_file("./globals.json").get_path();
			std::ofstream file(file_path, std::ios::out | std::ios::trunc);
			file << json.dump(4);
			file.close();
			ZeroMemory(global_name, sizeof(global_name));
		}
	}

	void delete_global(std::string name)
	{
		auto locations = get_globals_json();
		if (locations[name].is_null())
			return;
		locations.erase(name);
		auto file_path = g_file_manager.get_project_file("./globals.json").get_path();
		std::ofstream file(file_path, std::ios::out | std::ios::trunc);
		file << locations.dump(4);
		file.close();
	}

	void debug::globals()
	{
		if (ImGui::BeginTabItem("DEBUG_TAB_GLOBALS"_T.data()))
		{
			static global_debug global_test{};
			static script_global glo_bal_sunday = script_global(global_test.global_index);
			ImGui::SetNextItemWidth(200.f);
			if (ImGui::InputScalar("VIEW_DEBUG_GLOBAL"_T.data(), ImGuiDataType_U64, &global_test.global_index))
				glo_bal_sunday = script_global(global_test.global_index);

			for (int i = 0; i < global_test.global_appendages.size(); i++)
			{
				auto item = global_test.global_appendages[i];
				ImGui::PushID(i + item.type);
				switch (item.type)
				{
					case GlobalAppendageType_At:
						ImGui::SetNextItemWidth(200.f);
						ImGui::InputScalar("VIEW_DEBUG_GLOBAL_AT"_T.data(), ImGuiDataType_S64, &global_test.global_appendages[i].index);
						ImGui::SameLine();
						ImGui::SetNextItemWidth(200.f);
						ImGui::InputScalar("VIEW_DEBUG_GLOBAL_SIZE"_T.data(), ImGuiDataType_S64, &global_test.global_appendages[i].size);
						break;
					case GlobalAppendageType_ReadGlobal:
						ImGui::Text(std::format("{} {}", "VIEW_DEBUG_GLOBAL_READ_GLOBAL"_T, item.global_name).c_str());
						ImGui::SameLine();
						ImGui::SetNextItemWidth(200.f);
						ImGui::InputScalar("VIEW_DEBUG_GLOBAL_SIZE"_T.data(), ImGuiDataType_S64, &global_test.global_appendages[i].size);
						break;
					case GlobalAppendageType_PlayerId:
						ImGui::SetNextItemWidth(200.f);
						ImGui::InputScalar("VIEW_DEBUG_GLOBAL_READ_PLAYER_ID_SIZE"_T.data(), ImGuiDataType_S64, &global_test.global_appendages[i].size);
						break;
				}
				ImGui::PopID();
			}

			if (ImGui::Button("VIEW_DEBUG_GLOBAL_ADD_OFFSET"_T.data()))
				global_test.global_appendages.push_back({GlobalAppendageType_At, 0LL, 0ULL});
			ImGui::SameLine();
			if (ImGui::Button("VIEW_DEBUG_GLOBAL_ADD_READ_PLAYER_ID"_T.data()))
				global_test.global_appendages.push_back({GlobalAppendageType_PlayerId, 0LL, 0ULL});

			if (global_test.global_appendages.size() > 0 && ImGui::Button("VIEW_DEBUG_GLOBAL_REMOVE_OFFSET"_T.data()))
				global_test.global_appendages.pop_back();

			if (auto ptr = get_global_ptr(global_test))
			{
				ImGui::SetNextItemWidth(200.f);
				ImGui::InputScalar("VIEW_DEBUG_GLOBAL_VALUE"_T.data(), ImGuiDataType_S32, ptr);
			}
			else
				ImGui::Text("VIEW_DEBUG_GLOBAL_INVALID_GLOBAL_READ"_T.data());

			auto globals = list_globals();
			static std::string selected_global;
			ImGui::Text("VIEW_DEBUG_GLOBAL_SAVED_GLOBALS"_T.data());
			if (ImGui::BeginListBox("##savedglobals", ImVec2(200, 200)))
			{
				for (auto pair : globals)
				{
					if (ImGui::Selectable(pair.first.c_str(), selected_global == pair.first))
						selected_global = std::string(pair.first);
				}
				ImGui::EndListBox();
			}
			ImGui::SameLine();
			if (ImGui::BeginListBox("##globalvalues", ImVec2(200, 200)))
			{
				for (auto pair : globals)
				{
					if (auto ptr = get_global_ptr(pair.second))
						ImGui::Selectable(std::format("{}", (std::int32_t)*ptr).c_str(), false, ImGuiSelectableFlags_Disabled);
					else
						ImGui::Selectable("VIEW_DEBUG_GLOBAL_INVALID_GLOBAL_READ"_T.data(), false, ImGuiSelectableFlags_Disabled);
				}
				ImGui::EndListBox();
			}
			ImGui::SameLine();
			ImGui::BeginGroup();
			static char global_name[50]{};
			ImGui::SetNextItemWidth(200.f);
			ImGui::InputText("##GlobalName", global_name, IM_ARRAYSIZE(global_name));
			if (ImGui::IsItemActive())
				g.self.hud.typing = TYPING_TICKS;
			if (ImGui::Button("Save Global"))
			{
				save_global(global_name, global_test);
			}
			ImGui::SameLine();
			if (ImGui::Button("VIEW_DEBUG_GLOBAL_LOAD_GLOBAL"_T.data()))
			{
				load_global_menu(selected_global, global_test);
			}

			if (ImGui::Button("VIEW_DEBUG_GLOBAL_DELETE_GLOBAL"_T.data()))
			{
				if (!selected_global.empty())
				{
					delete_global(selected_global);
					selected_global.clear();
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("VIEW_DEBUG_GLOBAL_ADD_READ_GLOBAL"_T.data()))
			{
				global_test.global_appendages.push_back({GlobalAppendageType_ReadGlobal, 0LL, 0ULL, selected_global});
			}
			ImGui::SameLine();
			if (ImGui::Button("VIEW_DEBUG_GLOBAL_CLEAR"_T.data()))
			{
				global_test.global_index = 0;
				global_test.global_appendages.clear();
			}
			ImGui::EndGroup();
			ImGui::EndTabItem();
		}
	}
}