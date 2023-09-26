#include "http_client/http_client.hpp"
#include "views/view.hpp"

namespace big
{
	void view::proxy_settings()
	{
		ImGui::TextWrapped("Proxy settings are used for people who are having troubles communicating with certain sites. This is handy for people behind a firewall be it in your local network or your country.");

		auto& settings = g_http_client.settings();
		if (ImGui::BeginCombo("Proxy Protocol", g_http_client.protocol().data()))
		{
			for (const auto [key, protocol] : g_http_client.protocols())
			{
				if (ImGui::Selectable(protocol.data(), key == settings.protocol))
				{
					settings.protocol = key;
                    LOG(INFO) << "Updated proxy type to: " << protocol;
				}
			}
		    ImGui::EndCombo();
		}

		if (settings.protocol != ProxyProtocol::NONE)
		{
            components::input_text_with_hint("Proxy Host", "example.com", settings.proxy_host);
            components::input_text_with_hint("Proxy Username", "user", settings.user);
            components::input_text_with_hint("Proxy Password", "passw0rd", settings.password);
		}

		if (components::button("Update Proxy Settings"))
		{
			g_http_client.update_proxy(settings);
			g_http_client.save();

            g_notification_service->push("Proxy Settings", "Successfully updated proxy settings.");
		}
	}
}
