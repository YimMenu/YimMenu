#include "services/ped_animations/ped_animations_service.hpp"
#include "util/animations.hpp"
#include "views/debug/view_debug.hpp"
#include "views/view.hpp"

namespace big
{
	void view::animations()
	{
		ImGui::BeginGroup();

		static ped_animation new_template{};
		static std::string category = "Default";
		static ped_animation deletion_ped_animation{};

		if (!std::string(deletion_ped_animation.name).empty())
			ImGui::OpenPopup("##deletepedanimation");

		if (ImGui::BeginPopupModal("##deletepedanimation", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text(std::format("Are you sure you want to delete {}", deletion_ped_animation.name).data());

			ImGui::Spacing();

			if (ImGui::Button("Yes"))
			{
				g_ped_animation_service.delete_saved_animation(category, deletion_ped_animation);
				deletion_ped_animation.name = "";
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("No"))
			{
				deletion_ped_animation.name = "";
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::PushItemWidth(250);
		components::input_text_with_hint("##dict", "Dict", &new_template.dict);
		components::options_modal(
		    "Debug animations",
		    [] {
			    debug::animations(&new_template.dict, &new_template.anim);
		    },
		    true,
		    "List From Debug");
		components::input_text_with_hint("##anim", "Anim", &new_template.anim);

		if (ImGui::TreeNode("Advanced Options"))
		{
			ImGui::SliderFloat("Blend in", &new_template.blendin, -5, 10);
			ImGui::SliderFloat("Blend out", &new_template.blendout, -5, 10);
			ImGui::InputInt("Duration in ms", &new_template.time_to_play);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("-1 will make the duration indefinite, assuming it is looped");
			ImGui::PopItemWidth();

			ImGui::BeginGroup(); //Regular flags

			ImGui::CheckboxFlags("Looped", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::LOOPING));
			ImGui::CheckboxFlags("Hold Last Frame", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::HOLD_LAST_FRAME));
			ImGui::CheckboxFlags("Uninterruptable", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::NOT_INTERRUPTABLE));
			ImGui::CheckboxFlags("Only Upperbody", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::UPPERBODY));
			ImGui::CheckboxFlags("Secondary slot", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::SECONDARY));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Allow primary animations to run simultaniously, such as walking");
			ImGui::CheckboxFlags("Realize Animation Orientation", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::REORIENT_WHEN_FINISHED));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Use the final orientation achieved in the animation");
			ImGui::CheckboxFlags("Hide Weapon", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::HIDE_WEAPON));

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			//Sync flags
			ImGui::CheckboxFlags("Sync In", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::TAG_SYNC_IN));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Seamless transition into the animation, for example from walking");
			ImGui::CheckboxFlags("Sync Out", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::TAG_SYNC_OUT));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Seamless transition out of the animation, for example to continue walking");
			ImGui::CheckboxFlags("Sync Continuous", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::TAG_SYNC_CONTINUOUS));
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Seamless transition during the animation, especially usefull for upperbody animations");
			ImGui::CheckboxFlags("Force Start", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::FORCE_START));
			ImGui::CheckboxFlags("Disable Colission", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::TURN_OFF_COLLISION));
			ImGui::CheckboxFlags("Override Physics", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::OVERRIDE_PHYSICS));
			ImGui::CheckboxFlags("Ignore Gravity", reinterpret_cast<unsigned int*>(&new_template.flags), static_cast<unsigned int>(animations::anim_flags::IGNORE_GRAVITY));

			ImGui::EndGroup();

			ImGui::TreePop();
		}

		components::button("Play", [] {
			g_ped_animation_service.play_saved_ped_animation(new_template, self::ped);
		});
		ImGui::SameLine();
		components::button("Stop", [] {
			TASK::CLEAR_PED_TASKS(self::ped);
		});

		ImGui::SeparatorText("Saving");

		components::input_text_with_hint("Category", "Category", &category);
		components::input_text_with_hint("Name", "Name", &new_template.name);

		static auto save_response = [=]() -> bool {
			if (!STREAMING::DOES_ANIM_DICT_EXIST(new_template.dict.data()))
			{
				g_notification_service->push_warning("Animations",
				    std::format("Dict with the name {} does not exist", new_template.dict));
				return false;
			}

			if (g_ped_animation_service.get_animation_by_name(new_template.name))
			{
				g_notification_service->push_warning("Animations",
				    std::format("Animation with the name {} already exists", new_template.name));
				return false;
			}

			if (new_template.anim.empty())
			{
				g_notification_service->push_warning("Animations", "Animation name can't be empty");
				return false;
			}

			return true;
		};

		components::button("Save", [] {
			if (save_response())
				g_ped_animation_service.save_new_animation(category, new_template);
		});

		ImGui::EndGroup();

		ImGui::SeparatorText("Saved");

		components::small_text("Double click to play\nShift click to delete");

		static std::string filter;

		ImGui::BeginGroup();

		components::input_text_with_hint("##filter", "Search", &filter);

		ImGui::BeginGroup();
		components::small_text("Categories");
		if (ImGui::BeginListBox("##categories", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.5)}))
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
		components::small_text("Animations");
		if (ImGui::BeginListBox("##animations", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.5)}))
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
					if (ImGui::Selectable(p.name.data(), p.name == new_template.name, ImGuiSelectableFlags_AllowDoubleClick))
					{
						if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
						{
							deletion_ped_animation = p;
						}
						else
						{
							new_template = p;
							if (ImGui::IsMouseDoubleClicked(0))
							{
								g_fiber_pool->queue_job([p] {
									g_ped_animation_service.play_saved_ped_animation(new_template, self::ped);
								});
							}
						}
					}
					if (ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						if (p.name.length() > 25)
							ImGui::Text(p.name.data());

						ImGui::Text(std::format("Dict: {}\nAnim: {}", p.dict, p.anim).data());
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