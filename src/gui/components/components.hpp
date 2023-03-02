#pragma once
#include "backend/command.hpp"
#include "backend/looped_command.hpp"
#include "backend/player_command.hpp"
#include "fiber_pool.hpp"

namespace big
{
	struct navigation_struct;
	enum class tabs;

	class components
	{
		static void custom_text(const std::string_view, ImFont*);

	public:
		static bool nav_button(const std::string_view);
		static void icon(const std::string_view);
		static void small_text(const std::string_view);
		static void sub_title(const std::string_view);
		static void title(const std::string_view);
		static void nav_item(std::pair<tabs, navigation_struct>&, int);

		static void input_text_with_hint(const std::string_view label, const std::string_view hint, char* buf, size_t buf_size, ImGuiInputTextFlags_ flag = ImGuiInputTextFlags_None, std::function<void()> cb = nullptr);
		static void input_text(const std::string_view label, char* buf, size_t buf_size, ImGuiInputTextFlags_ flag = ImGuiInputTextFlags_None, std::function<void()> cb = nullptr);

		static bool selectable(const std::string_view, bool);
		static bool selectable(const std::string_view, bool, ImGuiSelectableFlags);
		static void selectable(const std::string_view, bool, std::function<void()>);
		static void selectable(const std::string_view, bool, ImGuiSelectableFlags, std::function<void()>);

		static bool script_patch_checkbox(const std::string_view text, bool* option, const std::string_view tooltip = "");

		template<template_str cmd_str, ImVec2 size = ImVec2(0, 0), ImVec4 color = ImVec4(0.24f, 0.23f, 0.29f, 1.00f)>
		static void command_button(const std::vector<std::uint64_t> args = {}, std::optional<const std::string_view> label_override = std::nullopt)
		{
			static command* command = command::get(rage::consteval_joaat(cmd_str.value));
			if (ImGui::Button(label_override.value_or(command->get_label()).data()))
				command->call(args);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(command->get_description().c_str());
		}

		template<template_str cmd_str, ImVec2 size = ImVec2(0, 0), ImVec4 color = ImVec4(0.24f, 0.23f, 0.29f, 1.00f)>
		static void player_command_button(player_ptr player = g_player_service->get_selected(), const std::vector<std::uint64_t> args = {}, std::optional<const std::string_view> label_override = std::nullopt)
		{
			static player_command* command = (player_command*)command::get(rage::consteval_joaat(cmd_str.value));
			if (ImGui::Button(label_override.value_or(command->get_label()).data()))
				command->call(player, args);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(command->get_description().c_str());
		}

		template<template_str cmd_str>
		static void command_checkbox(std::optional<const std::string_view> label_override = std::nullopt)
		{
			static bool_command* command = (bool_command*)command::get(rage::consteval_joaat(cmd_str.value));
			if (ImGui::Checkbox(label_override.value_or(command->get_label()).data(), &command->is_enabled()))
				command->refresh();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(command->get_description().c_str());
		}

		template<ImVec2 size = ImVec2(0, 0), ImVec4 color = ImVec4(0.24f, 0.23f, 0.29f, 1.00f)>
		static bool button(const std::string_view text)
		{
			bool status = false;
			ImGui::PushStyleColor(ImGuiCol_Button, color);
			status = ImGui::Button(text.data(), size);
			ImGui::PopStyleColor(1);
			return status;
		}

		template<ImVec2 size = ImVec2(0, 0), ImVec4 color = ImVec4(0.24f, 0.23f, 0.29f, 1.00f)>
		static void button(const std::string_view text, std::function<void()> cb)
		{
			if (button<size, color>(text))
			{
				g_fiber_pool->queue_job(cb);
			}
		}

		template<typename PredicateFn, typename ComponentsFn>
		static void disable_unless(PredicateFn predicate_fn, ComponentsFn components_fn)
		{
			auto const result = predicate_fn();
			if (!result)
				ImGui::BeginDisabled(true);
			components_fn();
			if (!result)
				ImGui::EndDisabled();
		}
	};
}
