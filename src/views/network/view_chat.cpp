#include "gta_util.hpp"
#include "views/view.hpp"
#include "util/chat.hpp"
#include "core/data/command_access_levels.hpp"

namespace big
{
	struct target_language_type
	{
		const char* type;
		const char* name;
	};

	void view::chat()
	{
		static char msg[256];
		ImGui::Checkbox("USE_SPAM_TIMER"_T.data(), &g.session.use_spam_timer);
		if (g.session.use_spam_timer)
		{
			ImGui::SliderFloat("SPAM_TIMER"_T.data(), &g.session.spam_timer, 0.5f, 5.0f);
			ImGui::SliderInt("SPAM_LENGTH"_T.data(), &g.session.spam_length, 1, 256);
		}
		ImGui::Checkbox("LOG_CHAT_MSG"_T.data(), &g.session.log_chat_messages);
		ImGui::Checkbox("LOG_TXT_MSG"_T.data(), &g.session.log_text_messages);
		components::input_text_with_hint("##message", "VIEW_NET_CHAT_MESSAGE"_T, msg, sizeof(msg));

		ImGui::Checkbox("IS_TEAM"_T.data(), &g.session.is_team);
		ImGui::SameLine();
		components::button("SEND"_T, [] {
			if (const auto net_game_player = gta_util::get_network_player_mgr()->m_local_net_player; net_game_player)
			{
				chat::send_message(msg, nullptr, true, g.session.is_team);
			}
		});

		ImGui::Separator();

		ImGui::Checkbox("CHAT_COMMANDS"_T.data(), &g.session.chat_commands);
		if (g.session.chat_commands)
		{
			components::small_text("DEFAULT_CMD_PERMISSIONS"_T);
			if (ImGui::BeginCombo("##defualtchatcommands", COMMAND_ACCESS_LEVELS[g.session.chat_command_default_access_level]))
			{
				for (const auto& [type, name] : COMMAND_ACCESS_LEVELS)
				{
					if (ImGui::Selectable(name, type == g.session.chat_command_default_access_level))
					{
						g.session.chat_command_default_access_level = type;
					}

					if (type == g.session.chat_command_default_access_level)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}
		}

		components::command_checkbox<"translatechat">();
		if (g.session.chat_translator.enabled)
		{
			ImGui::Checkbox("TRANSLATOR_HIDE_SAME_LANGUAGE"_T.data(), &g.session.chat_translator.bypass_same_language);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("TRANSLATOR_HIDE_SAME_LANGUAGE_DESC"_T.data());

			components::small_text("TRANSLATOR_OUTPUT"_T.data());
			ImGui::Checkbox("TRANSLATOR_SHOW_ON_CHAT"_T.data(), &g.session.chat_translator.draw_result);
			ImGui::Checkbox("TRANSLATOR_PRINT_TO_CONSOLE"_T.data(), &g.session.chat_translator.print_result);

			static const auto target_language = std::to_array<target_language_type>({{"sq", "Albanian"}, {"ar", "Arabic"}, {"az", "Azerbaijani"}, {"bn", "Bengali"}, {"bg", "Bulgarian"}, {"ca", "Catalan"}, {"zh", "Chinese"}, {"zt", "Chinese(traditional)"}, {"cs", "Czech"}, {"da", "Danish"}, {"nl", "Dutch"}, {"en", "English"}, {"eo", "Esperanto"}, {"et", "Estonian"}, {"fi", "Finnish"}, {"fr", "French"}, {"de", "German"}, {"el", "Greek"}, {"he", "Hebrew"}, {"hi", "Hindi"}, {"hu", "Hungarian"}, {"id", "Indonesian"}, {"ga", "Irish"}, {"it", "Italian"}, {"ja", "Japanese"}, {"ko", "Korean"}, {"lv", "Latvian"}, {"lt", "Lithuanian"}, {"ms", "Malay"}, {"nb", "Norwegian"}, {"fa", "Persian"}, {"pl", "Polish"}, {"pt", "Portuguese"}, {"ro", "Romanian"}, {"ru", "Russian"}, {"sr", "Serbian"}, {"sk", "Slovak"}, {"sl", "Slovenian"}, {"es", "Spanish"}, {"sv", "Swedish"}, {"tl", "Tagalog"}, {"th", "Thai"}, {"tr", "Turkish"}, {"uk", "Ukrainian"}, {"ur", "Urdu"}, {"vi", "Vietnamese"}});

			components::input_text_with_hint("TRANSLATOR_ENDPOINT"_T.data(),
			    "http://localhost:5000/translate",
			    g.session.chat_translator.endpoint);

			if (ImGui::BeginCombo("TRANSLATOR_TARGET_LANGUAGE"_T.data(), g.session.chat_translator.target_language.c_str()))
			{
				for (const auto& [type, name] : target_language)
				{
					components::selectable(name, false, [&type] {
						g.session.chat_translator.target_language = type;
					});
				}
				ImGui::EndCombo();
			}
		}	
	}
}
