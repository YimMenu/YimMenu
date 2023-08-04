#include "gui/components/components.hpp"
#include "util/animations.hpp"
#include "util/ped.hpp"
#include "view_debug.hpp"

namespace big
{
	void debug::animations(std::string* dict, std::string* anim)
	{
		static std::string current_dict, current_anim;
		static std::vector<std::string> selected_dict_anim_list{};

		if(dict && anim)
		{
			*dict = current_dict;
			*anim = current_anim;
		}
			
		static auto reload_anim_list = []() -> void {
			selected_dict_anim_list.clear();
			auto range = animations::all_anims.equal_range(current_dict);
			for (auto it = range.first; it != range.second; ++it)
			{
				selected_dict_anim_list.push_back(it->second);
			}
		};
		
		if(animations::has_anim_list_been_populated())
			ImGui::Text(std::format("There are {} dictionaries with {} animations in memory", animations::anim_dict_count(), animations::total_anim_count()).data());

		components::button("Fetch All Anims", [] {
			animations::fetch_all_anims();
		});

		ImGui::SetNextItemWidth(400);
		components::input_text_with_hint("##dictionaryfilter", "Dictionary", current_dict);

		if (animations::has_anim_list_been_populated() && ImGui::BeginListBox("##dictionaries", ImVec2(400, 200)))
		{
			for (auto& entry : animations::all_dicts)
			{
				std::string entry_lowercase  = entry;
				std::string search_lowercase = current_dict;
				std::transform(entry.begin(), entry.end(), entry.begin(), ::tolower);
				std::transform(current_dict.begin(), current_dict.end(), current_dict.begin(), ::tolower);
				if (entry.find(search_lowercase) != std::string::npos && ImGui::Selectable(entry.data()))
				{
					current_dict = entry;
					reload_anim_list();
				}
			}

			ImGui::EndListBox();
		}

		if (selected_dict_anim_list.size() > 0 && ImGui::BeginListBox("##animations", ImVec2(400, 200)))
		{
			for (auto& entry : selected_dict_anim_list)
			{
				if (ImGui::Selectable(entry.data(), entry == current_anim))
				{
					current_anim = entry;
				}
			}

			ImGui::EndListBox();
		}

		components::button("Play", [] {
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);
			ped::ped_play_animation(self::ped, current_dict, current_anim, 4.f, -4.f, -1, 0, 0, false);
		});
		ImGui::SameLine();
		components::button("Stop", [] {
			TASK::CLEAR_PED_TASKS(self::ped);
		});
	}
}