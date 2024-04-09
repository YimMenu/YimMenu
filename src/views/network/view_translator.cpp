#include "views/view.hpp"
#include "util/chat.hpp"
#include "backend/bool_command.hpp"
#include "services/api/api_service.hpp"

#include <imgui_internal.h>


namespace big
{
	struct DeeplTargetLanguage
	{
		const char* TargetLanguageType;
		const char* TargetLanguageName;
	};
	struct BingTargetLanguage
	{
		const char* TargetLanguageType;
		const char* TargetLanguageName;
	};
	struct GoogleTargetLanguage
	{
		const char* TargetLanguageType;
		const char* TargetLanguageName;
	};
	struct ServiceProvider
	{
		int ProviderID;
		const char* ProviderName;
	};

	bool_command chat_translate("translatechat", "translate chat message", "translate chat message", g.session.translatechat);
	bool_command chat_translate_hide_d("hideduplicate", "bypass same language", "Do not translate when source and target languages ​​are the same",
	    g.session.hideduplicate);

	void view::translator()
	{
		components::sub_title("Chat Translation");

		static const auto Provider = std::to_array<ServiceProvider>({{0, "Microsoft"}, {1, "Google"}, {2, "DeepLx"}, {3, "OpenAI"}});

		if (ImGui::BeginCombo("Service Provider##ServiceProvider", Provider[g.session.t_service_provider].ProviderName))
		{
			for (const auto& [id, name] : Provider)
			{
				components::selectable(name, false, [&id] {
					g.session.t_service_provider = id;
				});
			}
			ImGui::EndCombo();
		}

		components::button("testmsg", [] {
			ChatMessage messagetoadd{"testsender", "This is a test message"};
			MsgQueue.push(messagetoadd);
		});
		components::command_checkbox<"translatechat">();
		components::command_checkbox<"hideduplicate">();

		components::sub_title("Output");
		ImGui::Checkbox("Send to Chat"_T.data(), &g.session.translatechat_send);
		ImGui::SameLine();
		ImGui::Checkbox("Team Chat"_T.data(), &g.session.translatechat_send_team);
		ImGui::Checkbox("Print to Console"_T.data(), &g.session.translatechat_print);

		if (ImGui::CollapsingHeader("Bing Settings"_T.data()))
		{
			static const auto BingTargetLang = std::to_array<BingTargetLanguage>({{"ar", "Arabic"}, {"az", "Azerbaijani"}, {"bn", "Bangla"}, {"bg", "Bulgarian"}, {"zh-Hans", "Chinese Simplified"}, {"zh-Hant", "Chinese Traditional"}, {"hr", "Croatian"}, {"cs", "Czech"}, {"da", "Danish"}, {"de", "German"}, {"el", "Greek"}, {"en", "English"}, {"es", "Spanish"}, {"et", "Estonian"}, {"fi", "Finnish"}, {"fr", "French"}, {"hu", "Hungarian"}, {"id", "Indonesian"}, {"it", "Italian"}, {"ja", "Japanese"}, {"ko", "Korean"}, {"lt", "Lithuanian"}, {"lv", "Latvian"}, {"nb", "Norwegian(Bokmål)"}, {"nl", "Dutch"}, {"pl", "Polish"}, {"pt", "Portuguese"}, {"pt-br", "Portuguese(Brazilian)"}, {"ro", "Romanian"}, {"ru", "Russian"}, {"sk", "Slovak"}, {"sl", "Slovenian"}, {"sv", "Swedish"}, {"th", "Thai"}, {"tr", "Turkish"}, {"uk", "Ukrainian"}, {"vi", "Vietnamese"}});

			if (ImGui::BeginCombo("TargetLanguage##BingTargetLanguage", g.session.Bing_target_lang.c_str()))
			{
				for (const auto& [type, name] : BingTargetLang)
				{
					components::selectable(name, false, [&type] {
						g.session.Bing_target_lang = type;
					});
				}
				ImGui::EndCombo();
			}
			components::button("Refresh token", [] {
				ms_token_str = "";
			});

		}
		if (ImGui::CollapsingHeader("Google Settings"_T.data()))
		{
			static const auto GoogleTargetLang = std::to_array<GoogleTargetLanguage>({{"ar", "Arabic"}, {"az", "Azerbaijani"}, {"bg", "Bulgarian"}, {"zh-CN", "Chinese Simplified"}, {"zh-TW", "Chinese Traditional"}, {"hr", "Croatian"}, {"cs", "Czech"}, {"da", "Danish"}, {"de", "German"}, {"el", "Greek"}, {"en", "English"}, {"es", "Spanish"}, {"et", "Estonian"}, {"fi", "Finnish"}, {"fr", "French"}, {"hu", "Hungarian"}, {"id", "Indonesian"}, {"it", "Italian"}, {"ja", "Japanese"}, {"ko", "Korean"}, {"lt", "Lithuanian"}, {"lv", "Latvian"}, {"n0", "Norwegian"}, {"nl", "Dutch"}, {"pl", "Polish"}, {"pt", "Portuguese"}, {"ro", "Romanian"}, {"ru", "Russian"}, {"sk", "Slovak"}, {"sl", "Slovenian"}, {"sv", "Swedish"}, {"th", "Thai"}, {"tr", "Turkish"}, {"uk", "Ukrainian"}, {"vi", "Vietnamese"}});

			if (ImGui::BeginCombo("TargetLanguage##GoogleTargetLangSwitcher", g.session.Google_target_lang.c_str()))
			{
				for (const auto& [type, name] : GoogleTargetLang)
				{
					components::selectable(name, false, [&type] {
						g.session.Google_target_lang = type;
					});
				}
				ImGui::EndCombo();
			}
		}

		if (ImGui::CollapsingHeader("DeepL Settings"_T.data()))
		{
			static const auto DeepLTargetLang = std::to_array<DeeplTargetLanguage>({{"AR", "Arabic"}, {"BG", "Bulgarian"}, {"CS", "Czech"}, {"DA", "Danish"}, {"DE", "German"}, {"EL", "Greek"}, {"EN", "English"}, {"EN-GB", "English(British)"}, {"EN-US", "English(American)"}, {"ES", "Spanish"}, {"ET", "Estonian"}, {"FI", "Finnish"}, {"FR", "French"}, {"HU", "Hungarian"}, {"ID", "Indonesian"}, {"IT", "Italian"}, {"JA", "Japanese"}, {"KO", "Korean"}, {"LT", "Lithuanian"}, {"LV", "Latvian"}, {"NB", "Norwegian(Bokmål)"}, {"NL", "Dutch"}, {"PL", "Polish"}, {"PT", "Portuguese"}, {"PT-BR", "Portuguese(Brazilian)"}, {"PT-PT", "Portuguese(Others)"}, {"RO", "Romanian"}, {"RU", "Russian"}, {"SK", "Slovak"}, {"SL", "Slovenian"}, {"SV", "Swedish"}, {"TR", "Turkish"}, {"UK", "Ukrainian"}, {"ZH", "Chinese(simplified)"}});
			
			components::input_text_with_hint("DeepLx URL", "http://127.0.0.1:1188/translate", g.session.DeepLx_url);
			
			if (ImGui::BeginCombo("TargetLanguage##DeepLTargetLangSwitcher", g.session.DeepL_target_lang.c_str()))
			{
				for (const auto& [type, name] : DeepLTargetLang)
				{
					components::selectable(name, false, [&type] {
						g.session.DeepL_target_lang = type;
					});
				}
				ImGui::EndCombo();
			}

		}

		if (ImGui::CollapsingHeader("OpenAI Settings"_T.data()))
		{

			components::input_text_with_hint("OpenAI Endpoint", "https://api.openai.com/", g.session.OpenAI_endpoint);
			components::input_text_with_hint("OpenAI key", "sk-*", g.session.OpenAI_key);
			components::input_text_with_hint("model", "gpt-3.5-turbo", g.session.OpenAI_model);
			components::input_text_with_hint("Target Language##OpenAI", "English", g.session.OpenAI_target_lang);

		}

	}
}