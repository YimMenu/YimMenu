#include "http_client/http_client.hpp"
#include "thread_pool.hpp"
#include "views/view.hpp"

namespace big
{
	void view::proxy_settings()
	{
		ImGui::TextWrapped("Proxy settings are useful for users behind a firewall that blocks access to certain websites. If you do not know what this is used for leave the proxy protocol on 'None'.");

		static auto settings = g_http_client.proxy_mgr().settings();
		if (ImGui::BeginCombo("Proxy Protocol", g_http_client.proxy_mgr().protocol_str(settings.protocol).data()))
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
			components::input_text_with_hint("Proxy Host", "example.com", settings.proxy_host);
			ImGui::InputInt("Proxy Port", &settings.proxy_port);
			settings.proxy_port = std::clamp(settings.proxy_port, 0, 0xffff);

			ImGui::Checkbox("Use Credentials", &settings.creds.uses_creds);
			if (settings.creds.uses_creds)
			{
				components::input_text_with_hint("Proxy Username", "user", settings.creds.user);
				components::input_text_with_hint("Proxy Password", "passw0rd", settings.creds.password);
			}
		}

		if (components::button("Test Current Setup"))
		{
			g_thread_pool->push([] {
				const auto response = g_http_client.get("https://github.com/YimMenu/YimMenu/raw/master/metadata.json");
				try
				{
					const auto j = nlohmann::json::parse(response.text);
					LOG(INFO) << j.dump(4);
					g_notification_service->push_success("Proxy Settings", "Current setup works correctly.");
				}
				catch (const std::exception& e)
				{
					g_notification_service->push_error("Proxy Settings", "Test failed, incorrect proxy host, username or password.");
				}
			});
		}
		if (components::button("Reset"))
		{
			settings = {};
			g_http_client.proxy_mgr().reset();
		}
		ImGui::SameLine();
		if (components::button("Update Proxy Settings"))
		{
			if (settings.protocol == ProxyProtocol::NONE)
				settings = {};

			if (settings.creds.uses_creds)
				g_http_client.proxy_mgr().update(settings.proxy_host, settings.proxy_port, settings.protocol, settings.creds.user, settings.creds.password);
			else
				g_http_client.proxy_mgr().update(settings.proxy_host, settings.proxy_port, settings.protocol);

			g_notification_service->push("Proxy Settings", "Successfully updated proxy settings.");
		}
	}
}