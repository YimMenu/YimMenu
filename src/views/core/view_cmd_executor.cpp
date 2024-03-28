#include "backend/context/default_command_context.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "services/hotkey/hotkey_service.hpp"
#include "util/string_operations.hpp"
#include "views/view.hpp"

namespace big
{
	static std::vector<std::string> current_suggestion_list;
	static std::string command_buffer;
	static std::string auto_fill_suggestion;
	static std::string selected_suggestion;

	bool does_string_exist_in_list(const std::string& command, std::vector<std::string> list)
	{
		auto found = std::find_if(list.begin(), list.end(), [&](const std::string& cmd) {
			return cmd == command;
		});
		return found != list.end();
	}

	static void add_to_last_used_commands(const std::string& command)
	{
		if (does_string_exist_in_list(command, g.cmd.command_history))
		{
			return;
		}
		if (g.cmd.command_history.size() >= 10)
		{
			g.cmd.command_history.erase(g.cmd.command_history.begin());
		}

		g.cmd.command_history.push_back(command);
	}

	std::string auto_fill_command(std::string current_buffer)
	{
		auto possible_commands = command::get_suggestions(current_buffer);
		if (possible_commands.size() == 0)
			return current_buffer;

		return possible_commands[0]->get_name();
	}

	// What word in the sentence are we currently at
	int current_index(std::string current_buffer)
	{
		auto words = string::operations::split(current_buffer, ' ');
		return words.size();
	}

	// TODO currently breaks the command if argument had to be uppercase
	std::vector<std::string> suggestion_list_filtered(std::vector<std::string> suggestions, std::string filter)
	{
		std::vector<std::string> suggestions_filtered;
		std::string filter_lowercase = filter;
		std::transform(filter_lowercase.begin(), filter_lowercase.end(), filter_lowercase.begin(), ::tolower);
		for (auto suggestion : suggestions)
		{
			std::string suggestion_lowercase = suggestion;
			std::transform(suggestion_lowercase.begin(), suggestion_lowercase.end(), suggestion_lowercase.begin(), ::tolower);
			auto words = string::operations::split(command_buffer, ' ');
			if (suggestion_lowercase.find(filter_lowercase) != std::string::npos || does_string_exist_in_list(words.back(), current_suggestion_list) /*Need this to maintain suggestion list while navigating it*/)
				suggestions_filtered.push_back(suggestion);
		}

		return suggestions_filtered;
	}

	void get_appropriate_suggestion(std::string current_buffer, std::string& suggestion_)
	{
		auto argument_index = current_index(current_buffer);
		if (argument_index == 1)
		{
			suggestion_ = auto_fill_command(current_buffer);
			return;
		}
		else
		{
			auto words           = string::operations::split(current_buffer, ' ');
			auto current_command = command::get(rage::joaat(words.front()));

			if (!current_command)
				return;

			auto suggestions = current_command->get_argument_suggestions(argument_index - 1);

			if (suggestions == std::nullopt)
				return;

			for (auto suggestion : suggestion_list_filtered(suggestions.value(), words.back()))
			{
				std::string guess_lowercase = words.back();
				std::transform(guess_lowercase.begin(), guess_lowercase.end(), guess_lowercase.begin(), ::tolower);

				if (suggestion.find(guess_lowercase) != std::string::npos)
				{
					suggestion_ = suggestion;
					break;
				}
			}
		}
	}

	void get_previous_from_list(std::vector<std::string>& list, std::string& current)
	{
		auto found = std::find_if(list.begin(), list.end(), [&](const std::string& cmd) {
			return cmd == current;
		});

		if (found == list.end())
		{
			if (list.size() > 0)
				current = list.back();

			return;
		}

		if (found == list.begin())
		{
			current = list.back();
			return;
		}

		if (found - 1 != list.end())
			current = *(found - 1);
	}

	void get_next_from_list(std::vector<std::string>& list, std::string& current)
	{
		auto found = std::find_if(list.begin(), list.end(), [&](const std::string& cmd) {
			return cmd == current;
		});

		if (found == list.end())
		{
			if (list.size() > 0)
				current = list.front();

			return;
		}

		if (found == list.end() - 1)
		{
			current = list.front();
			return;
		}

		if (found + 1 != list.end())
			current = *(found + 1);
	}

	void rebuild_buffer_with_suggestion(ImGuiInputTextCallbackData* data, std::string suggestion)
	{
		auto words = string::operations::split(data->Buf, ' ');
		std::string new_text;

		// Replace the last word with the suggestion
		words.pop_back();
		words.push_back(suggestion);

		// Rebuild the command with its arguments from scratch
		for (auto word : words)
		{
			new_text += word;
			if (word != words.back())
				new_text += " ";
		}

		data->DeleteChars(0, data->BufTextLen);
		data->InsertChars(0, new_text.c_str());
	}

	static int apply_suggestion(ImGuiInputTextCallbackData* data)
	{
		if (!data)
			return 0;

		if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion)
		{
			// User has a suggestion selectable higlighted, this takes precedence
			if (!selected_suggestion.empty())
			{
				// This could be a history suggestion with arguments, so we have to check for it
				auto words   = string::operations::split(selected_suggestion, ' ');
				auto command = command::get(rage::joaat(words.front()));

				// Its a command, lets rewrite the entire buffer (history command potentially with arguments)
				if (command)
				{
					data->DeleteChars(0, data->BufTextLen);
					data->InsertChars(0, selected_suggestion.c_str());
				}
				// Its probably an argument suggestion or a raw command, append it
				else
					rebuild_buffer_with_suggestion(data, selected_suggestion);

				selected_suggestion = std::string();
				return 0;
			}

			std::string auto_fill_suggestion;
			get_appropriate_suggestion(data->Buf, auto_fill_suggestion);

			if (auto_fill_suggestion != data->Buf)
			{
				rebuild_buffer_with_suggestion(data, auto_fill_suggestion);
			}
		}
		else if (data->EventFlag == ImGuiInputTextFlags_CallbackHistory)
		{
			if (current_suggestion_list.empty())
				return 0;

			if (data->EventKey == ImGuiKey_UpArrow)
				get_previous_from_list(current_suggestion_list, selected_suggestion);

			else if (data->EventKey == ImGuiKey_DownArrow)
				get_next_from_list(current_suggestion_list, selected_suggestion);
		}

		return 0;
	}

	void view::cmd_executor()
	{
		if (!g.cmd_executor.enabled)
			return;

		float screen_x = (float)*g_pointers->m_gta.m_resolution_x;
		float screen_y = (float)*g_pointers->m_gta.m_resolution_y;

		ImGui::SetNextWindowPos(ImVec2(screen_x * 0.25f, screen_y * 0.2f), ImGuiCond_Always);
		ImGui::SetNextWindowBgAlpha(0.65f);
		ImGui::SetNextWindowSize({screen_x * 0.5f, -1});

		if (ImGui::Begin("cmd_executor", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMouseInputs))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {10.f, 15.f});
			components::sub_title("CMD_EXECUTOR_TITLE"_T);

			// set focus by default on input box
			ImGui::SetKeyboardFocusHere(0);

			ImGui::SetNextItemWidth((screen_x * 0.5f) - 30.f);

			if (components::input_text_with_hint("", "CMD_EXECUTOR_TYPE_CMD"_T, command_buffer, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, nullptr, apply_suggestion))
			{
				if (command::process(command_buffer, std::make_shared<default_command_context>(), true))
				{
					g.cmd_executor.enabled = false;
					add_to_last_used_commands(command_buffer);
					command_buffer      = {};
					selected_suggestion = std::string();
				}
			}

			if (!command_buffer.empty())
			{
				get_appropriate_suggestion(command_buffer, auto_fill_suggestion);

				if (auto_fill_suggestion != command_buffer)
					ImGui::Text("Suggestion: %s", auto_fill_suggestion.data());
			}

			components::small_text("CMD_EXECUTOR_MULTIPLE_CMDS"_T);
			ImGui::Spacing();

			if (current_suggestion_list.size() > 0)
			{
				int suggestions = 0;
				for (auto suggestion : current_suggestion_list)
				{
					if (suggestions < 10 /*Hard limit to 10 for now*/)
						components::selectable(suggestion, suggestion == selected_suggestion);
					suggestions++;
				}
			}

			// TODO Add support for multiple commands at once (i.e with ; separation)
			if (current_index(command_buffer) == 1)
			{
				if (!g.cmd.command_history.empty())
				{
					current_suggestion_list = g.cmd.command_history;
				}
			}
			// If we are at any index above the first word, suggest arguments
			// TODO Add support for multiple commands at once (i.e with ; separation)
			else if (current_index(command_buffer) > 1)
			{
				auto current_buffer_index = current_index(command_buffer);
				auto buffer_words         = string::operations::split(command_buffer, ' ');

				if (auto current_command = command::get(rage::joaat(string::operations::split(command_buffer, ' ').front())))
				{
					auto argument_suggestions = current_command->get_argument_suggestions(current_buffer_index - 1);
					if (argument_suggestions != std::nullopt)
					{
						auto filtered_suggestions = suggestion_list_filtered(argument_suggestions.value(), buffer_words.back());
						current_suggestion_list = filtered_suggestions;
					}
				}
			}
			ImGui::PopStyleVar();
		}

		ImGui::End();
	}

	bool_command g_cmd_executor("cmdexecutor", "CMD_EXECUTOR", "CMD_EXECUTOR_DESC", g.cmd_executor.enabled, false);
}