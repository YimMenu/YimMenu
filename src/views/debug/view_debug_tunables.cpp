#include "gui/components/components.hpp"
#include "services/tunables/tunables_service.hpp"
#include "widgets/imgui_bitfield.hpp"
#include "view_debug.hpp"

namespace big
{
	enum TunableValueType : int
	{
		INT,
		BOOLEAN,
		BITSET,
		FLOAT
	};

	struct tunable_debug
	{
		std::string tunable_name{};
		TunableValueType tunable_value_type = TunableValueType::INT;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(tunable_debug, tunable_name, tunable_value_type)
	};

	nlohmann::json get_tunables_json()
	{
		nlohmann::json tunables{};
		auto file = g_file_manager.get_project_file("./tunables.json");
		if (file.exists())
		{
			std::ifstream iffstream_file(file.get_path());
			iffstream_file >> tunables;
		}
		return tunables;
	}

	void load_tunable_menu(const std::string& selected_tunable, tunable_debug& tunable_obj)
	{
		if (!selected_tunable.empty())
		{
			auto tunables = get_tunables_json();
			if (tunables[selected_tunable].is_null())
				return;
			tunable_obj = tunables[selected_tunable].get<tunable_debug>();
		}
	}

	bool is_numeric(const std::string& str)
	{
		if (str[0] == '-')
			return str.size() > 1 && std::all_of(str.begin() + 1, str.end(), ::isdigit);

		return std::all_of(str.begin(), str.end(), ::isdigit);
	}

	bool is_hexadecimal(const std::string& str)
	{
		if (str.size() > 2 && str[0] == '0' && str[1] == 'x')
		{
			return std::all_of(str.begin() + 2, str.end(), [](unsigned char c) {
				return std::isxdigit(c);
			});
		}

		return false;
	}

	int64_t parse_tunable(const std::string& tunable)
	{
		if (tunable.empty())
			return 0;

		std::string str = tunable;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		try
		{
			if (is_numeric(str))
			{
				return std::stoll(str);
			}
			else if (is_hexadecimal(str))
			{
				return std::stoll(str, nullptr, 16);
			}

			return rage::joaat(str);
		}
		catch (const std::out_of_range&)
		{
			return 0;
		}
	}

	int64_t* get_tunable_ptr(tunable_debug& tunable_test)
	{
		auto retn_val = g_tunables_service->get_tunable<int64_t*>(parse_tunable(tunable_test.tunable_name));
		if ((size_t)retn_val < UINT32_MAX)
			return nullptr;
		return retn_val;
	}

	std::string get_tunable_display(tunable_debug& tunable_test)
	{
		auto ptr = get_tunable_ptr(tunable_test);
		if (ptr != nullptr)
		{
			switch (tunable_test.tunable_value_type)
			{
			case TunableValueType::INT:
			{
				return std::to_string(*(PINT)ptr);
			}
			case TunableValueType::BOOLEAN:
			{
				return (*ptr == TRUE) ? "TRUE" : "FALSE";
			}
			case TunableValueType::BITSET:
			{
				std::ostringstream o;
				o << "0x" << std::hex << std::uppercase << (DWORD)*ptr;
				return o.str();
			}
			case TunableValueType::FLOAT:
			{
				return std::to_string(*(PFLOAT)ptr);
			}
			}
		}
		return "VIEW_DEBUG_TUNABLE_INVALID_TUNABLE_READ"_T.data();
	}

	std::map<std::string, tunable_debug> list_tunables()
	{
		auto json = get_tunables_json();
		std::map<std::string, tunable_debug> return_value;
		for (auto& item : json.items())
			return_value[item.key()] = item.value();
		return return_value;
	}

	void save_tunable(char* tunable_name, tunable_debug& tunable_obj)
	{
		std::string tunable_name_string = tunable_name;
		if (!tunable_name_string.empty())
		{
			auto json                  = get_tunables_json();
			json[tunable_name_string]  = tunable_obj;

			auto file_path = g_file_manager.get_project_file("./tunables.json").get_path();
			std::ofstream file(file_path, std::ios::out | std::ios::trunc);
			file << json.dump(4);
			file.close();
			ZeroMemory(tunable_name, sizeof(tunable_name));
		}
	}

	void delete_tunable(std::string name)
	{
		auto locations = get_tunables_json();
		if (locations[name].is_null())
			return;
		locations.erase(name);
		auto file_path = g_file_manager.get_project_file("./tunables.json").get_path();
		std::ofstream file(file_path, std::ios::out | std::ios::trunc);
		file << locations.dump(4);
		file.close();
	}

	void debug::tunables()
	{
		if (ImGui::BeginTabItem("DEBUG_TAB_TUNABLES"_T.data()))
		{
			static tunable_debug tunable_test{};
			ImGui::SetNextItemWidth(300.f);
			components::input_text("VIEW_DEBUG_TUNABLE"_T.data(), tunable_test.tunable_name);
			if (auto ptr = get_tunable_ptr(tunable_test))
			{
				auto tunable_offset = g_tunables_service->get_tunable_offset(parse_tunable(tunable_test.tunable_name));
				ImGui::SetNextItemWidth(300.f);
				ImGui::InputScalar("VIEW_DEBUG_TUNABLE_OFFSET"_T.data(), ImGuiDataType_S32, &tunable_offset, 0, 0, 0, ImGuiInputTextFlags_ReadOnly);

				switch (tunable_test.tunable_value_type)
				{
				case TunableValueType::INT:
				{
					ImGui::SetNextItemWidth(300.f);
					ImGui::InputScalar("VIEW_DEBUG_GLOBAL_VALUE"_T.data(), ImGuiDataType_S32, ptr);
					break;
				}
				case TunableValueType::BOOLEAN:
				{
					bool is_tunable_enabled = (*ptr == TRUE);
					if (ImGui::Checkbox("VIEW_DEBUG_GLOBAL_VALUE"_T.data(), &is_tunable_enabled))
					{
						*ptr = is_tunable_enabled;
					}
					break;
				}
				case TunableValueType::BITSET:
				{
					ImGui::SetNextItemWidth(300.f);
					ImGui::Bitfield("VIEW_DEBUG_GLOBAL_VALUE"_T.data(), (PINT)ptr);
					break;
				}
				case TunableValueType::FLOAT:
				{
					ImGui::SetNextItemWidth(300.f);
					ImGui::InputScalar("VIEW_DEBUG_GLOBAL_VALUE"_T.data(), ImGuiDataType_Float, ptr);
					break;
				}
				}
			}
			else
			{
				ImGui::Text("VIEW_DEBUG_TUNABLE_INVALID_TUNABLE_READ"_T.data());
			}

			ImGui::SetNextItemWidth(150.f);
			ImGui::Combo("VIEW_DEBUG_GLOBAL_TYPE"_T.data(), (int*)&tunable_test.tunable_value_type, "INT\0BOOLEAN\0BITSET\0FLOAT\0");

			auto tunables = list_tunables();
			static std::string selected_tunable;
			ImGui::Text("VIEW_DEBUG_TUNABLE_SAVED_TUNABLES"_T.data());
			if (ImGui::BeginListBox("##savedtunables", ImVec2(200, 250)))
			{
				for (auto pair : tunables)
				{
					if (ImGui::Selectable(pair.first.c_str(), selected_tunable == pair.first))
						selected_tunable = std::string(pair.first);
				}
				ImGui::EndListBox();
			}
			ImGui::SameLine();
			if (ImGui::BeginListBox("##tunablevalues", ImVec2(250, 250)))
			{
				for (auto pair : tunables)
				{
					ImGui::Selectable(get_tunable_display(pair.second).c_str(), false, ImGuiSelectableFlags_Disabled);
				}
				ImGui::EndListBox();
			}
			ImGui::SameLine();
			ImGui::BeginGroup();
			static char tunable_name_to_save[50]{};
			ImGui::SetNextItemWidth(200.f);
			components::input_text("##tunableName", tunable_name_to_save, IM_ARRAYSIZE(tunable_name_to_save));
			if (ImGui::Button("VIEW_DEBUG_TUNABLE_SAVE_TUNABLE"_T.data()))
			{
				save_tunable(tunable_name_to_save, tunable_test);
			}
			ImGui::SameLine();
			if (ImGui::Button("VIEW_DEBUG_TUNABLE_LOAD_TUNABLE"_T.data()))
			{
				load_tunable_menu(selected_tunable, tunable_test);
			}

			if (ImGui::Button("VIEW_DEBUG_TUNABLE_DELETE_TUNABLE"_T.data()))
			{
				if (!selected_tunable.empty())
				{
					delete_tunable(selected_tunable);
					selected_tunable.clear();
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("VIEW_DEBUG_GLOBAL_CLEAR"_T.data()))
			{
				tunable_test.tunable_name = "";
			}
			ImGui::EndGroup();
			ImGui::EndTabItem();
		}
	}
}