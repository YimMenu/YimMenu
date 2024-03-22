#include "http_client/http_client.hpp"
#include "thread_pool.hpp"
#include "views/view.hpp"

namespace big
{
	void view::proxy_settings()
	{
		ImGui::TextWrapped("PROXY_SETTINGS_DESCRIPTION"_T.data());

		static auto settings = g_http_client.proxy_mgr().settings();
		if (ImGui::BeginCombo("PROXY_SETTINGS_PROTOCOL"_T.data(), g_http_client.proxy_mgr().protocol_str(settings.protocol).data()))
		{
			for (const auto [key, protocol] : g_http_client.proxy_mgr().protocols())
			{
				if (ImGui::Selectable(protocol.data(), key == settings.protocol))
				{
					settings.protocol = key;
				}
			}
			ImGui::EndCombo();
		}

		if (settings.protocol != ProxyProtocol::NONE)
		{
			components::input_text_with_hint("PROXY_SETTINGS_HOST"_T, "example.com", settings.proxy_host);
			ImGui::InputInt("PROXY_SETTINGS_PORT"_T.data(), &settings.proxy_port);
			settings.proxy_port = std::clamp(settings.proxy_port, 0, 0xffff);

			ImGui::Checkbox("PROXY_SETTINGS_USES_CREDENTIALS"_T.data(), &settings.creds.uses_creds);
			if (settings.creds.uses_creds)
			{
				components::input_text_with_hint("PROXY_SETTINGS_USER"_T, "user", settings.creds.user);
				components::input_text_with_hint("PROXY_SETTINGS_PASSWORD"_T, "passw0rd", settings.creds.password);
			}
		}

		if (components::button("PROXY_SETTINGS_TEST_CURRENT"_T))
		{
			g_thread_pool->push([] {
				const auto response = g_http_client.get("https://github.com/YimMenu/YimMenu/raw/master/metadata.json");
				try
				{
					const auto j = nlohmann::json::parse(response.text);
					g_notification_service.push_success("PROXY_SETTINGS"_T.data(), "PROXY_SETTINGS_TEST_CURRENT_SUCCESS"_T.data());
				}
				catch (const std::exception& e)
				{
					g_notification_service.push_error("PROXY_SETTINGS"_T.data(), "PROXY_SETTINGS_TEST_CURRENT_FAIL"_T.data());
				}
			});
		}
		if (components::button("RESET"_T))
		{
			settings = {};
			g_http_client.proxy_mgr().reset();
		}
		ImGui::SameLine();
		if (components::button("PROXY_SETTINGS_UPDATE"_T))
		{
			if (settings.protocol == ProxyProtocol::NONE)
				settings = {};

			if (settings.creds.uses_creds)
				g_http_client.proxy_mgr().update(settings.proxy_host, settings.proxy_port, settings.protocol, settings.creds.user, settings.creds.password);
			else
				g_http_client.proxy_mgr().update(settings.proxy_host, settings.proxy_port, settings.protocol);

			g_notification_service.push("PROXY_SETTINGS"_T.data(), "PROXY_SETTINGS_UPDATE_SUCCESS"_T.data());
		}
	}
}
