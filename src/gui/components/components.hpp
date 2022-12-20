#pragma once
#include "imgui.h"
#include "backend/command.hpp"
#include "backend/looped_command.hpp"
#include "backend/player_command.hpp"

namespace big
{
	struct navigation_struct;
	enum class tabs;

	class components
	{
		static void custom_text(const std::string_view, ImFont*);
	public:
		static bool nav_button(const std::string_view);
		static bool button(const std::string_view);
		static void icon(const std::string_view);
		static void small_text(const std::string_view);
		static void sub_title(const std::string_view);
		static void title(const std::string_view);
		static void button(const std::string_view, std::function<void()>);
		static void nav_item(std::pair<tabs, navigation_struct>&, int);

		static void input_text_with_hint(const std::string_view label, const std::string_view hint, char* buf, size_t buf_size, ImGuiInputTextFlags_ flag = ImGuiInputTextFlags_None, std::function<void()> cb = nullptr);

		static bool selectable(const std::string_view, bool);
		static bool selectable(const std::string_view, bool, ImGuiSelectableFlags);
		static void selectable(const std::string_view, bool, std::function<void()>);
		static void selectable(const std::string_view, bool, ImGuiSelectableFlags, std::function<void()>);

		static bool script_patch_checkbox(const std::string_view text, bool* option, const std::string_view tooltip = "");

		template<size_t N>
		struct template_str
		{
			constexpr template_str(const char(&str)[N])
			{
				std::copy_n(str, N, value);
			}

			char value[N];
		};

		template<template_str cmd_str>
		static void command_button(const std::string_view name, const std::vector<std::uint64_t> args = {})
		{
			static command* command = command::get(rage::consteval_joaat(cmd_str.value));
			if (ImGui::Button(name.data()))
				command->call(args);
		}

		template<template_str cmd_str>
		static void player_command_button(const std::string_view name, player_ptr player = g_player_service->get_selected(), const std::vector<std::uint64_t> args = {})
		{
			static player_command* command = (player_command*)command::get(rage::consteval_joaat(cmd_str.value));
			if (ImGui::Button(name.data()))
				command->call(player, args);
		}

		template<template_str cmd_str>
		static void command_checkbox(const std::string_view label)
		{
			static looped_command* command = (looped_command*)command::get(rage::consteval_joaat(cmd_str.value));
			if (ImGui::Checkbox(label.data(), &command->is_enabled()))
				command->refresh();
		}
	};
}
