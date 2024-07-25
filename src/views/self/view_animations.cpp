#include "services/ped_animations/ped_animations_service.hpp"
#include "util/animations.hpp"
#include "util/ped.hpp"
#include "views/debug/view_debug.hpp"
#include "views/view.hpp"

namespace big
{
	void json_animations(std::string* dict, std::string* anim)
	{
		static std::string current_dict, current_anim;
		static std::vector<std::string> selected_dict_anim_list{};

		if (dict && anim)
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

		if (animations::has_anim_list_been_populated())
		{
			ImGui::Text("VIEW_DEBUG_ANIMATIONS_ANIMATIONS_IN_MEMORY"_T.data(), animations::anim_dict_count(), animations::total_anim_count());
		}

		components::button("VIEW_DEBUG_ANIMATIONS_FETCH_ALL_ANIMS"_T, [] {
			animations::fetch_all_anims();
		});

		ImGui::SetNextItemWidth(400);
		components::input_text_with_hint("##dictionaryfilter", "DICT"_T, current_dict);

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

		components::button("VIEW_DEBUG_ANIMATIONS_PLAY"_T, [] {
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);
			ped::ped_play_animation(self::ped, current_dict, current_anim, 4.f, -4.f, -1, 0, 0, false);
		});
		ImGui::SameLine();
		components::button("VIEW_DEBUG_ANIMATIONS_STOP"_T, [] {
			TASK::CLEAR_PED_TASKS(self::ped);
		});
	}

	void view::animations()
	{
		ImGui::BeginGroup();

		static std::string category = "DEFAULT"_T.data();
		static ped_animation deletion_ped_animation{};

		if (!std::string(deletion_ped_animation.name).empty())
			ImGui::OpenPopup("##deletepedanimation");

		if (ImGui::BeginPopupModal("##deletepedanimation", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text("VIEW_SELF_ANIMATIONS_ARE_YOU_SURE_DELETE"_T.data(), deletion_ped_animation.name);

			ImGui::Spacing();

			if (ImGui::Button("YES"_T.data()))
			{
				g_ped_animation_service.delete_saved_animation(category, deletion_ped_animation);
				deletion_ped_animation.name = "";
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("NO"_T.data()))
			{
				deletion_ped_animation.name = "";
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::PushItemWidth(250);
		components::input_text_with_hint("##dict", "DICT"_T, g_ped_animation_service.current_animation.dict);
		components::options_modal(
		    "VIEW_SELF_ANIMATIONS_DEBUG_ANIMATIONS"_T.data(),
		    [] {
			    json_animations(&g_ped_animation_service.current_animation.dict, &g_ped_animation_service.current_animation.anim);
		    },
		    true,
		    "VIEW_SELF_ANIMATIONS_LIST_FROM_DEBUG"_T.data());
		components::input_text_with_hint("##anim", "ANIMATION"_T, g_ped_animation_service.current_animation.anim);

		ImGui::SameLine();
		components::button("VIEW_DEBUG_ANIMATIONS_PLAY"_T.data(), [] {
			g_ped_animation_service.play_saved_ped_animation(g_ped_animation_service.current_animation, self::ped);
		});
		ImGui::SameLine();
		components::button("VIEW_DEBUG_ANIMATIONS_STOP"_T.data(), [] {
			TASK::CLEAR_PED_TASKS(self::ped);
		});

		if (ImGui::TreeNode("VIEW_SELF_ANIMATIONS_ADVANCED_OPTIONS"_T.data()))
		{
			ImGui::SliderFloat("VIEW_SELF_ANIMATIONS_BLEND_IN"_T.data(), &g_ped_animation_service.current_animation.blendin, -5, 10);
			ImGui::SliderFloat("VIEW_SELF_ANIMATIONS_BLEND_OUT"_T.data(), &g_ped_animation_service.current_animation.blendout, -5, 10);
			ImGui::InputInt("VIEW_SELF_ANIMATIONS_DURATION"_T.data(), &g_ped_animation_service.current_animation.time_to_play);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SELF_ANIMATIONS_DURATION_TOOLTIP"_T.data());
			ImGui::PopItemWidth();

			ImGui::Checkbox("VIEW_SELF_ANIMATIONS_AMBIENT"_T.data(), &g_ped_animation_service.current_animation.ambient);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SELF_ANIMATIONS_AMBIENT_TOOLTIP"_T.data());

			if (g_ped_animation_service.current_animation.ambient)
			{
				g_ped_animation_service.current_animation.pos[0] = self::pos.x;
				g_ped_animation_service.current_animation.pos[1] = self::pos.y;
				g_ped_animation_service.current_animation.pos[2] = self::pos.z;

				g_ped_animation_service.current_animation.rot[0] = self::rot.x;
				g_ped_animation_service.current_animation.rot[1] = self::rot.y;
				g_ped_animation_service.current_animation.rot[2] = self::rot.z;
			}
			else
			{
				g_ped_animation_service.current_animation.pos[0] = 0;
				g_ped_animation_service.current_animation.pos[1] = 0;
				g_ped_animation_service.current_animation.pos[2] = 0;

				g_ped_animation_service.current_animation.rot[0] = 0;
				g_ped_animation_service.current_animation.rot[1] = 0;
				g_ped_animation_service.current_animation.rot[2] = 0;
			}

			ImGui::BeginGroup(); //Regular flags

			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_LOOPED"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::LOOPING));
			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_HOLD_LAST_FRAME"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::HOLD_LAST_FRAME));
			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_UNINTERRUPTABLE"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::NOT_INTERRUPTABLE));
			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_ONLY_UPPERBODY"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::UPPERBODY));
			ImGui::CheckboxFlags("SECONDARY"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::SECONDARY));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SELF_ANIMATIONS_SECONDARY_TOOLTIP"_T.data());
			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_REALIZE_ANIMATION_ORIENTATION"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::REORIENT_WHEN_FINISHED));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SELF_ANIMATIONS_REALIZE_ANIMATION_ORIENTATION_TOOLTIP"_T.data());
			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_HIDE_WEAPON"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::HIDE_WEAPON));

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			//Sync flags
			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_SYNC_IN"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::TAG_SYNC_IN));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SELF_ANIMATIONS_SYNC_IN_TOOLTIP"_T.data());

			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_SYNC_OUT"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::TAG_SYNC_OUT));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SELF_ANIMATIONS_SYNC_OUT_TOOLTIP"_T.data());
			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_SYNC_CONTINUOUS"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::TAG_SYNC_CONTINUOUS));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SELF_ANIMATIONS_SYNC_CONTINUOUS_TOOLTIP"_T.data());
			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_FORCE_START"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::FORCE_START));
			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_DISABLE_COLLISION"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::TURN_OFF_COLLISION));
			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_OVERRIDE_PHYSICS"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::OVERRIDE_PHYSICS));
			ImGui::CheckboxFlags("VIEW_SELF_ANIMATIONS_IGNORE_GRAVITY"_T.data(), reinterpret_cast<unsigned int*>(&g_ped_animation_service.current_animation.flags), static_cast<unsigned int>(animations::anim_flags::IGNORE_GRAVITY));

			ImGui::EndGroup();

			ImGui::TreePop();
		}

		ImGui::SeparatorText("CREATOR_SAVE_TO_FILE"_T.data());

		components::input_text_with_hint("VIEW_SELF_ANIMATIONS_CATEGORY"_T, "VIEW_SELF_ANIMATIONS_CATEGORY_DESC"_T, category);
		components::input_text_with_hint("NAME"_T, "FILE_NAME"_T, g_ped_animation_service.current_animation.name);

		static auto save_response = [=]() -> bool {
			if (!STREAMING::DOES_ANIM_DICT_EXIST(g_ped_animation_service.current_animation.dict.data()))
			{
				g_notification_service.push_warning("GUI_TAB_ANIMATIONS"_T.data(),
				    std::vformat("VIEW_SELF_ANIMATIONS_DICT_DOES_NOT_EXIST"_T, std::make_format_args(g_ped_animation_service.current_animation.dict)));
				return false;
			}

			if (g_ped_animation_service.get_animation_by_name(g_ped_animation_service.current_animation.name))
			{
				g_notification_service.push_warning("GUI_TAB_ANIMATIONS"_T.data(),
					std::vformat("VIEW_SELF_ANIMATIONS_ANIM_ALREADY_EXISTS"_T, std::make_format_args(g_ped_animation_service.current_animation.name)));
				return false;
			}

			if (category.empty())
			{
				g_notification_service.push_warning("GUI_TAB_ANIMATIONS"_T.data(), "VIEW_SELF_ANIMATIONS_CATEGORY_EMPTY_ERROR"_T.data());
				return false;
			}

			if (g_ped_animation_service.current_animation.anim.empty())
			{
				g_notification_service.push_warning("GUI_TAB_ANIMATIONS"_T.data(), "VIEW_SELF_ANIMATIONS_ANIM_EMPTY_ERROR"_T.data());
				return false;
			}

			return true;
		};

		ImGui::SameLine();

		components::button("SAVE"_T, [] {
			if (save_response())
				g_ped_animation_service.save_new_animation(category, g_ped_animation_service.current_animation);
		});

		ImGui::EndGroup();

		ImGui::SeparatorText("VIEW_SELF_ANIMATIONS_SAVED"_T.data());
		components::button("REFRESH"_T, [] {
			g_ped_animation_service.fetch_saved_animations();
		});

		components::small_text("VIEW_SELF_ANIMATIONS_DOUBLE_CLICK_TO_PLAY"_T);
		components::small_text("VIEW_SELF_ANIMATIONS_DOUBLE_SHIFT_CLICK_TO_DELETE"_T);

		ImGui::SameLine();

		ImGui::Checkbox("VIEW_SELF_ANIMATIONS_PROMPT_AMBIENT"_T.data(), &g.self.prompt_ambient_animations);
		if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VIEW_SELF_ANIMATIONS_PROMPT_AMBIENT_TOOLTIP"_T.data());

		static std::string filter;

		ImGui::BeginGroup();

		components::input_text_with_hint("##filter", "SEARCH"_T, filter);

		ImGui::BeginGroup();
		components::small_text("VIEW_SELF_ANIMATIONS_CATEGORIES"_T);
		if (ImGui::BeginListBox("##categories", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			for (auto& l : g_ped_animation_service.all_saved_animations | std::ranges::views::keys)
			{
				if (ImGui::Selectable(l.data(), l == category))
				{
					category = l;
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		components::small_text("GUI_TAB_ANIMATIONS"_T);
		if (ImGui::BeginListBox("##animations", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			if (g_ped_animation_service.all_saved_animations.find(category)
			    != g_ped_animation_service.all_saved_animations.end())
			{
				std::vector<ped_animation> current_list{};

				if (!filter.empty())
					current_list = g_ped_animation_service.saved_animations_filtered_list(filter);
				else
					current_list = g_ped_animation_service.all_saved_animations.at(category);

				for (const auto& p : current_list)
				{
					if (ImGui::Selectable(p.name.data(), p.name == g_ped_animation_service.current_animation.name, ImGuiSelectableFlags_AllowDoubleClick))
					{
						if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
						{
							deletion_ped_animation = p;
						}
						else
						{
							g_ped_animation_service.current_animation = p;
							if (ImGui::IsMouseDoubleClicked(0))
							{
								g_fiber_pool->queue_job([p] {
									g_ped_animation_service.play_saved_ped_animation(g_ped_animation_service.current_animation, self::ped);
								});
							}
						}
					}
					if (ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						if (p.name.length() > 25)
							ImGui::Text(p.name.data());

						ImGui::Text(std::format("{}: {}\n{}: {}", "DICT"_T.data(), p.dict, "ANIMATION"_T.data(), p.anim).c_str());

						if (p.ambient)
							ImGui::BulletText("VIEW_SELF_ANIMATIONS_AMBIENT_ANIMATION"_T.data());
						ImGui::EndTooltip();
					}
				}
			}

			ImGui::EndListBox();
		}

		ImGui::EndGroup();

		ImGui::EndGroup();
	}
}
