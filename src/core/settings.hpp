#pragma once

#include "settings/context_menu.hpp"
#include "settings/esp.hpp"
#include "settings/notifications.hpp"
#include "settings/protections.hpp"
#include "settings/self.hpp"
#include "settings/session.hpp"
#include "settings/session_browser.hpp"
#include "settings/settings.hpp"
#include "settings/window.hpp"

namespace big
{
	class menu_settings
	{
	public:
		void init(const file& save_file);

		void attempt_save();
		bool load();
		bool write_default_config();

	private:
		bool deep_compare(nlohmann::json& current_settings, const nlohmann::json& default_settings, bool compare_value = false);
		bool save();

	private:
		file m_save_file;

		nlohmann::json m_default_options;
		nlohmann::json m_options;

	public:
		g_notifications_t& notifications     = g_notifications;
		g_protections_t& protections         = g_protections;
		g_self_t& self                       = g_self;
		g_session_t& session                 = g_session;
		g_settings_t& settings               = g_settings;
		g_window_t& window                   = g_window;
		g_context_menu_t& context_menu       = g_context_menu;
		g_esp_t& esp                         = g_esp;
		g_session_browser_t& session_browser = g_session_browser;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(menu_settings, notifications, protections, self, session, settings, window, context_menu, esp, session_browser)
	};

	inline auto g_menu_settings = menu_settings();
}
