#include "backend/context/default_command_context.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "services/hotkey/hotkey_service.hpp"
#include "util/string_operations.hpp"
#include "views/view.hpp"

namespace big
{
	//TODO Argument suggestions are limited to the last word in the buffer
	//TODO Allow for optional arguments??

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

	std::vector<std::string> deque_to_vector(std::deque<std::string> deque)
	{
		std::vector<std::string> vector;
		for (auto& element : deque)
		{
			vector.push_back(element);
		}
		return vector;
	}

	static void add_to_last_used_commands(const std::string& command)
	{
		if (does_string_exist_in_list(command, deque_to_vector(g.cmd.command_history)))
		{
			return;
		}

		if (g.cmd.command_history.size() >= 10)
		{
			g.cmd.command_history.pop_back();
		}

		g.cmd.command_history.push_front(command);
	}

	std::string auto_fill_command(std::string current_buffer)
	{
		if (command::get(rage::joaat(current_buffer)) != nullptr)
			return current_buffer;

		for (auto [key, cmd] : g_commands)
		{
			if (cmd && cmd->get(key) && &cmd->get_name())
			{
				if (cmd->get_name().find(current_buffer) != std::string::npos)
					return cmd->get_name();
			}
		}

		return std::string();
	}

	// What word in the sentence are we currently at
	int current_index(std::string current_buffer)
	{
		auto separate_commands = string::operations::split(current_buffer, ';'); // Split by semicolon to support multiple commands
		auto words = string::operations::split(separate_commands.back(), ' ');
		return words.size();
	}

	std::vector<std::string> suggestion_list_filtered(std::vector<std::string> suggestions, std::string filter)
	{
		std::vector<std::string> suggestions_filtered;
		std::string filter_lowercase = filter;
		string::operations::to_lower(filter_lowercase);
		for (auto suggestion : suggestions)
		{
			std::string suggestion_lowercase = suggestion;
			string::operations::to_lower(suggestion_lowercase);
			auto words = string::operations::split(command_buffer, ' ');
			if (suggestion_lowercase.find(filter_lowercase) != std::string::npos || does_string_exist_in_list(words.back(), current_suggestion_list) /*Need this to maintain suggestion list while navigating it*/)
				suggestions_filtered.push_back(suggestion);
		}

		return suggestions_filtered;
	}

	void get_appropriate_suggestion(std::string current_buffer, std::string& suggestion_)
	{
		auto separate_commands = string::operations::split(current_buffer, ';'); // Split by semicolon to support multiple commands
		auto words           = string::operations::split(separate_commands.back(), ' ');
		auto current_command = command::get(rage::joaat(words.front()));
		auto argument_index  = current_index(current_buffer);

		if (argument_index == 1)
		{
			suggestion_ = auto_fill_command(words.back());
			return;
		}
		else
		{
			if (!current_command)
				return;

			auto suggestions = current_command->get_argument_suggestions(argument_index - 1);

			if (suggestions == std::nullopt)
				return;

			for (auto suggestion : suggestion_list_filtered(suggestions.value(), words.back()))
			{
				std::string guess_lowercase      = words.back();
				std::string suggestion_lowercase = suggestion;
				string::operations::to_lower(suggestion_lowercase);
				string::operations::to_lower(guess_lowercase);

				if (suggestion_lowercase.find(guess_lowercase) != std::string::npos)
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

		if (*found == list.front())
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

		if (*found == list.back())
		{
			current = list.front();
			return;
		}

		if (found + 1 != list.end())
			current = *(found + 1);
	}

	void rebuild_buffer_with_suggestion(ImGuiInputTextCallbackData* data, std::string suggestion)
	{
		auto separate_commands = string::operations::split(data->Buf, ';'); // Split by semicolon to support multiple commands
		auto words = string::operations::split(separate_commands.back(), ' ');
		std::string new_text;

		// Replace the last word with the suggestion
		words.pop_back();
		words.push_back(suggestion);

		// Replace the last command with the new suggestion
		separate_commands.pop_back();
		separate_commands.push_back(string::operations::join(words, ' '));

		new_text = string::operations::join(separate_commands, ';');

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
				if (command::process(command_buffer, std::make_shared<default_command_context>(), false))
				{
					g.cmd_executor.enabled = false;
					add_to_last_used_commands(command_buffer);
					command_buffer      = {};
					selected_suggestion = std::string();
				}
			}

			if (!command_buffer.empty())
			{
				auto separate_commands = string::operations::split(command_buffer, ';'); // Split by semicolon to support multiple commands
				get_appropriate_suggestion(separate_commands.back(), auto_fill_suggestion);

				if (auto_fill_suggestion != command_buffer)
					ImGui::Text("Suggestion: %s", auto_fill_suggestion.data());
			}

			components::small_text("CMD_EXECUTOR_MULTIPLE_CMDS"_T);
			components::small_text("CMD_EXECUTOR_INSTRUCTIONS"_T);
			ImGui::Separator();
			ImGui::Spacing();

			if (current_suggestion_list.size() > 0)
			{
				for (auto suggestion : current_suggestion_list)
				{
					components::selectable(suggestion, suggestion == selected_suggestion);
				}
			}

			if (current_index(command_buffer) == 1)
			{
				if (!g.cmd.command_history.empty())
				{
					current_suggestion_list = deque_to_vector(g.cmd.command_history);
				}
			}
			// If we are at any index above the first word, suggest arguments
			else if (current_index(command_buffer) > 1)
			{
				auto current_buffer_index = current_index(command_buffer);
				auto separate_commands = string::operations::split(command_buffer, ';'); // Split by semicolon to support multiple commands
				auto buffer_words = string::operations::split(separate_commands.back(), ' ');

				if (auto current_command = command::get(rage::joaat(buffer_words.front())))
				{
					auto argument_suggestions = current_command->get_argument_suggestions(current_buffer_index - 1);
					if (argument_suggestions != std::nullopt)
					{
						auto filtered_suggestions = suggestion_list_filtered(argument_suggestions.value(), buffer_words.back());
						if (filtered_suggestions.size() > 10)
						{
							current_suggestion_list =
							    std::vector<std::string>(filtered_suggestions.begin(), filtered_suggestions.begin() + 10);
						}
						else
						{
							current_suggestion_list = filtered_suggestions;
						}
					}
				}
			}
			ImGui::PopStyleVar();
		}

		ImGui::End();
	}

	bool_command g_cmd_executor("cmdexecutor", "CMD_EXECUTOR", "CMD_EXECUTOR_DESC", g.cmd_executor.enabled, false);
}