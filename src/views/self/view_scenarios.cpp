#include "pointers.hpp"
#include "services/context_menu/context_menu_service.hpp"
#include "services/notifications/notification_service.hpp"
#include "util/strings.hpp"
#include "views/view.hpp"

using json = nlohmann::json;

namespace big
{
	namespace scenariosNm
	{
		struct Scenario
		{
			std::string custom_name;
			std::string name;
		};

		NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Scenario, custom_name, name);

		Entity get_context_menu_ped()
		{
			if (big::g_context_menu_service->m_handle && ENTITY::DOES_ENTITY_EXIST(big::g_context_menu_service->m_handle)
			    && big::g_context_menu_service->m_pointer && big::g_context_menu_service->m_pointer->m_model_info->m_model_type == eModelType::Ped)
				return big::g_context_menu_service->m_handle;
			return 0;
		}

		std::filesystem::path getSavedScenariosFilePath()
		{
			return big::g_file_manager.get_project_file("savedScenarios.json").get_path();
		}
		void load_scenarios(std::vector<std::string>& list)
		{
			try
			{
				auto filePath = big::g_file_manager.get_project_file("scenariosCompact.json").get_path();

				if (std::filesystem::exists(filePath))
				{
					std::ifstream f(filePath);

					if (f.is_open())
					{
						list = json::parse(f);
						f.close();
					}
				}
				else
					big::g_notification_service->push_warning("Sorry", "Please download scenariosCompact.json.");
			}
			catch (std::exception e)
			{
				LOG(WARNING) << e.what();
			}
		}
		void loadSavedScenarios(std::map<std::string, std::vector<Scenario>>& list)
		{
			auto savedFilePath = getSavedScenariosFilePath();
			list.clear();
			try
			{
				if (std::filesystem::exists(savedFilePath))
				{
					std::ifstream f(savedFilePath);
					if (f.is_open())
					{
						list = json::parse(f);
						f.close();
					}
				}
			}
			catch (std::exception e)
			{
				LOG(WARNING) << e.what();
			}
		}
		void save_scenario(std::map<std::string, std::vector<Scenario>>& list)
		{
			auto savedFilePath = getSavedScenariosFilePath();

			try
			{
				json j = list;

				std::ofstream o(savedFilePath);
				if (o.is_open())
				{
					o << std::setw(4) << j << std::endl;
					o.close();
				}
			}
			catch (std::exception e)
			{
				LOG(WARNING) << e.what();
			}
		}
	}

	void view::scenarios()
	{
		static std::vector<std::string> scenarios, searchedScenarios;
		static std::map<std::string, std::vector<scenariosNm::Scenario>> savedScenarios;
		static std::string searchScenarioText, selected_scenario;
		static int is_ped_selected = 0;

		ImGui::SeparatorText("Select Entity");

		ImGui::RadioButton("Current player", &is_ped_selected, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Context menu ped/player", &is_ped_selected, 1);


		ImGui::SetNextItemWidth(200);
		if (components::input_text_with_hint("##searchScenarioText", "searchScenario", searchScenarioText))
			searchedScenarios.clear();
		ImGui::SameLine();
		components::button("Load scenarios", [&] {
			scenariosNm::load_scenarios(scenarios);
		});
		ImGui::SameLine();
		components::button("Stop scenarios", [=] {
			if (Entity e = is_ped_selected == 1 ? scenariosNm::get_context_menu_ped() : self::ped; e)
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(e);
		});

		components::small_text("Scenarios List");
		if (ImGui::BeginListBox("##Scenarios", {400, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			std::vector<std::string> temp_objs;

			if (searchedScenarios.size())
				temp_objs = searchedScenarios;
			else if (searchScenarioText.length() > 0)
				temp_objs = searchedScenarios = filterStrings(scenarios, searchScenarioText);

			for (auto& scenario : (searchScenarioText.length() > 0 ? temp_objs : scenarios))
				if (ImGui::Selectable(scenario.c_str(), selected_scenario == scenario, ImGuiSelectableFlags_AllowDoubleClick))
				{
					selected_scenario = scenario;
					if (ImGui::IsMouseDoubleClicked(0))
						g_fiber_pool->queue_job([=] {
							Entity e = is_ped_selected == 1 ? scenariosNm::get_context_menu_ped() : self::ped;
							if (e)
								TASK::TASK_START_SCENARIO_IN_PLACE(e, scenario.c_str(), -1, 0);
						});
				}


			ImGui::EndListBox();
		}

		ImGui::SeparatorText("Save Scenario");

		static std::string groupName, customScenarioName, selectedGroupName;

		ImGui::PushItemWidth(200);
		components::input_text_with_hint("##groupName", "groupName", groupName);
		components::input_text_with_hint("##customScenarioName", "customScenarioName", customScenarioName);
		ImGui::PopItemWidth();

		components::button("save", [&] {
			std::string _groupName          = trimString(groupName);
			std::string _customScenarioName = trimString(customScenarioName);

			if (_groupName.size() > 0 && _customScenarioName.size() > 0 && selected_scenario.size() > 0)
			{
				scenariosNm::Scenario obj = {_customScenarioName, selected_scenario};

				if (savedScenarios.size() == 0)
					scenariosNm::loadSavedScenarios(savedScenarios);

				if (savedScenarios.find(_groupName) != savedScenarios.end())
				{
					auto& _savedList = savedScenarios[_groupName];

					auto it = std::find_if(_savedList.begin(), _savedList.end(), [&_customScenarioName](const scenariosNm::Scenario& v) {
						return v.custom_name == _customScenarioName;
					});

					// if scenario already present
					if (it != _savedList.end())
						*it = obj;
					else
						_savedList.push_back(obj);
				}
				else
					savedScenarios[_groupName] = std::vector({obj});

				scenariosNm::save_scenario(savedScenarios);
			}
		});
		ImGui::SameLine();
		components::button("Load saved scenarios", [&] {
			scenariosNm::loadSavedScenarios(savedScenarios);
		});

		components::small_text("Shift click to delete a groupName or scenario inside it");

		static std::string groupToDelete;
		static int scenarioToDelete = -1;

		ImGui::BeginGroup();
		components::small_text("groupNames");
		if (ImGui::BeginListBox("##groupNames", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			for (auto& obj : savedScenarios)
				if (ImGui::Selectable(obj.first.c_str(), obj.first == selectedGroupName))
				{
					if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					{
						groupToDelete    = obj.first;
						scenarioToDelete = -1;
					}
					else
						selectedGroupName = groupName = obj.first;
				}
			ImGui::EndListBox();
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		components::small_text("scenarioNames");
		if (selectedGroupName.length()
		    && ImGui::BeginListBox("##scenarioNames", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			for (int i = 0; i < savedScenarios[selectedGroupName].size(); ++i)
			{
				auto& scen = savedScenarios[selectedGroupName][i];

				if (ImGui::Selectable(scen.custom_name.c_str(), scen.name == selected_scenario, ImGuiSelectableFlags_AllowDoubleClick))
				{
					if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					{
						groupToDelete    = selectedGroupName;
						scenarioToDelete = i;
					}
					else
					{
						customScenarioName = scen.custom_name;
						selected_scenario  = scen.name;

						if (ImGui::IsMouseDoubleClicked(0))
							g_fiber_pool->queue_job([=] {
								Entity e = is_ped_selected == 1 ? scenariosNm::get_context_menu_ped() : self::ped;
								if (e)
									TASK::TASK_START_SCENARIO_IN_PLACE(e, scen.name.c_str(), -1, 0);
							});
					}
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndGroup();


		if (!std::string(groupToDelete).empty() || scenarioToDelete != -1)
			ImGui::OpenPopup("##deleteSavedScenarioOrGroup");
		if (ImGui::BeginPopupModal("##deleteSavedScenarioOrGroup", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text(
			    std::format("Are you sure you want to delete {}", (scenarioToDelete != -1 ? "scenario" : "group")).c_str());
			ImGui::Spacing();
			if (ImGui::Button("Yes"))
			{
				if (scenarioToDelete != -1)
					savedScenarios[groupToDelete].erase(savedScenarios[groupToDelete].begin() + scenarioToDelete);
				else
				{
					savedScenarios.erase(groupToDelete);
					if (selectedGroupName == groupToDelete || savedScenarios.size() == 0)
						selectedGroupName = "";
				}
				scenariosNm::save_scenario(savedScenarios);

				groupToDelete    = "";
				scenarioToDelete = -1;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("No"))
			{
				groupToDelete    = "";
				scenarioToDelete = -1;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}