#include "core/data/ptfx_effects.hpp"

#include "pointers.hpp"
#include "services/notifications/notification_service.hpp"
#include "util/strings.hpp"
#include "views/view.hpp"

using json = nlohmann::json;

namespace big
{
	namespace ptfxEffects
	{
		struct Effect
		{
			std::string name;
			std::string dict;
			std::string effect;
			float size; // default size
		};

		struct AnimDictCompactObj
		{
			std::string DictionaryName;
			std::vector<std::string> EffectNames;
		};

		NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Effect, name, dict, effect, size);
		NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimDictCompactObj, DictionaryName, EffectNames);

		std::filesystem::path getSavedEffectsFilePath()
		{
			return big::g_file_manager.get_project_file("savedPtfxEffects.json").get_path();
		}
		void loadEffects(std::vector<AnimDictCompactObj>& list)
		{
			try
			{
				auto filePath = big::g_file_manager.get_project_file("particleEffectsCompact.json").get_path();

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
					big::g_notification_service->push_warning("Sorry", "Please download particleEffectsCompact.json.");
			}
			catch (std::exception e)
			{
				LOG(WARNING) << e.what();
			}
		}
		void loadSavedEffects(std::map<std::string, std::vector<Effect>>& list)
		{
			auto savedFilePath = getSavedEffectsFilePath();
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
		void saveEffects(std::map<std::string, std::vector<Effect>>& list)
		{
			auto savedFilePath = getSavedEffectsFilePath();

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

	auto animDictCompactObjReducer = [](ptfxEffects::AnimDictCompactObj& v) {
		return v.DictionaryName;
	};

	void view::ptfx_effects()
	{
		static std::vector<ptfxEffects::AnimDictCompactObj> animDictCompactObjs, searchedAnimDictCompactObjs;
		static std::map<std::string, std::vector<ptfxEffects::Effect>> savedEffects;
		static std::string searchDicText;
		static int selecDicIndex = -1;

		ImGui::BeginGroup();
		components::command_checkbox<"ptfx">();
		ImGui::SameLine();
		ImGui::SetNextItemWidth(400);
		ImGui::SliderFloat("PTFX Size", &g_ptfx_effects.size, 0.1f, 2.f);

		ImGui::SetNextItemWidth(200);
		if (components::input_text_with_hint("##searchDicText", "searchDic", searchDicText))
			searchedAnimDictCompactObjs.clear();
		ImGui::SameLine();
		components::button("Load ptfx effects", [&] {
			ptfxEffects::loadEffects(animDictCompactObjs);
		});

		ImGui::BeginGroup();
		components::small_text("DictionaryName");
		if (ImGui::BeginListBox("##dictionaries", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			std::vector<ptfxEffects::AnimDictCompactObj> temp_objs;

			if (searchedAnimDictCompactObjs.size())
				temp_objs = searchedAnimDictCompactObjs;
			else if (searchDicText.length() > 0)
				temp_objs = searchedAnimDictCompactObjs = filterStrings<ptfxEffects::AnimDictCompactObj>(animDictCompactObjs, searchDicText, animDictCompactObjReducer);

			unsigned i = 0;
			for (auto& dicObj : (searchDicText.length() > 0 ? temp_objs : animDictCompactObjs))
			{
				if (ImGui::Selectable(dicObj.DictionaryName.c_str(), selecDicIndex == i))
					selecDicIndex = i;
				++i;
			}

			ImGui::EndListBox();
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		components::small_text("EffectNames");
		if (selecDicIndex != -1 && ImGui::BeginListBox("##effectNames", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			for (auto& effectName : animDictCompactObjs[selecDicIndex].EffectNames)
				if (ImGui::Selectable(effectName.c_str(), effectName == g_ptfx_effects.effect))
				{
					g_ptfx_effects.asset  = animDictCompactObjs[selecDicIndex].DictionaryName.c_str();
					g_ptfx_effects.effect = effectName.c_str();
				}

			ImGui::EndListBox();
		}
		ImGui::EndGroup();

		ImGui::SeparatorText("Save an effect");

		static std::string groupName, customEffectName, selectedGroupName;

		ImGui::PushItemWidth(200);
		components::input_text_with_hint("##groupName", "groupName", groupName);
		components::input_text_with_hint("##customEffectName", "customEffectName", customEffectName);
		ImGui::PopItemWidth();
		components::button("save", [&] {
			std::string _groupName = trimString(groupName);
			std::string effectName = trimString(customEffectName);
			std::string currDict   = g_ptfx_effects.asset;
			std::string currEffect = g_ptfx_effects.effect;

			if (_groupName.size() > 0 && effectName.size() > 0 && currDict.size() > 0 && currEffect.size() > 0)
			{
				ptfxEffects::Effect effect = {effectName, currDict, currEffect, g_ptfx_effects.size};

				if (savedEffects.size() == 0)
					ptfxEffects::loadSavedEffects(savedEffects);

				if (savedEffects.find(_groupName) != savedEffects.end())
				{
					auto& effects = savedEffects[_groupName];

					auto it = std::find_if(effects.begin(), effects.end(), [&effectName](const ptfxEffects::Effect& effect) {
						return effect.name == effectName;
					});

					// if effect already present
					if (it != effects.end())
						*it = effect;
					else
						savedEffects[_groupName].push_back(effect);
				}
				else
					savedEffects[_groupName] = std::vector({effect});

				ptfxEffects::saveEffects(savedEffects);
			}
		});
		ImGui::SameLine();
		components::button("Load saved effects", [&] {
			ptfxEffects::loadSavedEffects(savedEffects);
		});

		components::small_text("Shift click to delete a groupName or effect inside it");

		static std::string groupToDelete;
		static int customEffectToDeleteIndex = -1;

		ImGui::BeginGroup();
		components::small_text("groupNames");
		if (ImGui::BeginListBox("##groupNames", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			for (auto& obj : savedEffects)
				if (ImGui::Selectable(obj.first.c_str(), obj.first == selectedGroupName))
				{
					if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					{
						groupToDelete             = obj.first;
						customEffectToDeleteIndex = -1;
					}
					else
						selectedGroupName = groupName = obj.first;
				}
			ImGui::EndListBox();
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		components::small_text("customEffectNames");
		if (selectedGroupName.length()
		    && ImGui::BeginListBox("##customEffectNames", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			for (int i = 0; i < savedEffects[selectedGroupName].size(); ++i)
			{
				auto& effect = savedEffects[selectedGroupName][i];

				if (ImGui::Selectable(effect.name.c_str(), effect.effect.c_str() == g_ptfx_effects.effect))
				{
					if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					{
						groupToDelete             = selectedGroupName;
						customEffectToDeleteIndex = i;
					}
					else
					{
						customEffectName      = effect.name;
						g_ptfx_effects.asset  = effect.dict.c_str();
						g_ptfx_effects.effect = effect.effect.c_str();
						g_ptfx_effects.size   = effect.size;
					}
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndGroup();


		if (!std::string(groupToDelete).empty() || customEffectToDeleteIndex != -1)
			ImGui::OpenPopup("##deleteCustomEffectOrGroup");
		if (ImGui::BeginPopupModal("##deleteCustomEffectOrGroup", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text(std::format("Are you sure you want to delete {}", (customEffectToDeleteIndex != -1 ? "effect" : "group"))
			                .c_str());
			ImGui::Spacing();
			if (ImGui::Button("Yes"))
			{
				if (customEffectToDeleteIndex != -1)
					savedEffects[groupToDelete].erase(savedEffects[groupToDelete].begin() + customEffectToDeleteIndex);
				else
				{
					savedEffects.erase(groupToDelete);
					if (selectedGroupName == groupToDelete || savedEffects.size() == 0)
						selectedGroupName = "";
				}
				ptfxEffects::saveEffects(savedEffects);

				groupToDelete             = "";
				customEffectToDeleteIndex = -1;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("No"))
			{
				groupToDelete             = "";
				customEffectToDeleteIndex = -1;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}


		ImGui::EndGroup();
	}
}