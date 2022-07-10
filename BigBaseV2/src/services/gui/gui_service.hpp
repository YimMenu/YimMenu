#pragma once
#include "views/view.hpp"

namespace big
{
	enum class tabs {
		ESP_SETTINGS,
		CONTEXT_MENU_SETTINGS,
		GUI_SETTINGS,
		HANDLING_SEARCH,
		HANDLING_SAVED_PROFILE,
		HANDLING_MY_PROFILES,
		HANDLING_CURRENT_PROFILE,
		LSC,
		NOTIFICATION_SETTINGS,
		PROTECTION_SETTINGS,
		DEBUG,
		MOBILE,
		NONE,
		NETWORK,
		PLAYER,
		SELF,
		SESSION,
		SETTINGS,
		SPAWN,
		PV,
		VEHICLE_FUN,
		SPOOFING,
		TELEPORT,
		VEHICLE,
		WEAPONS,
		HANDLING,
	};

	struct navigation_struct
	{
		const char name[32] = "";
		std::function<void()> func = nullptr;
		std::unordered_map<tabs, navigation_struct> sub_nav{};
	};

	class gui_service final
	{
		std::vector<tabs> current_tab{};
		bool switched_view = true;

		std::unordered_map<tabs, navigation_struct> nav = {
			{tabs::SELF, { "Self",view::self, {
				{ tabs::WEAPONS, { "Weapons", view::weapons }},
				{ tabs::MOBILE, {"Mobile", view::mobile}},
				{ tabs::TELEPORT, {"Teleport", view::teleport}},
			}}},
			{tabs::VEHICLE, { "Vehicle", view::vehicle, {
				{ tabs::HANDLING, {"Handling", view::handling_current_profile, {
					{ tabs::HANDLING_CURRENT_PROFILE, {"Current Profile", view::handling_current_profile } },
					{ tabs::HANDLING_MY_PROFILES, {"My Profiles", view::handling_my_profiles } },
					{ tabs::HANDLING_SAVED_PROFILE, {"Saved Profiles", view::handling_saved_profiles } },
					{ tabs::HANDLING_SEARCH, {"Search Handling", view::handling_search } },
				}}},
				{ tabs::LSC, { "LS Customs", view::lsc }},
				{ tabs::SPAWN, { "Spawn", view::spawn }},
				{ tabs::PV, { "Personal Vehicle", view::pv }},
				{ tabs::VEHICLE_FUN, { "Fun Features", view::vehicle_fun }},
			}}},
			{tabs::NETWORK, { "Network", nullptr, {
				{ tabs::SPOOFING, { "Spoofing", view::spoofing }},
				{ tabs::SESSION, { "Session", view::session }},
			}}},
			{tabs::SETTINGS, { "Settings", view::settings, {
				{ tabs::CONTEXT_MENU_SETTINGS, { "Context Menu", view::context_menu_settings}},
				{ tabs::ESP_SETTINGS, { "ESP", view::esp_settings}},
				{ tabs::GUI_SETTINGS, { "GUI", view::gui_settings}},
				{ tabs::NOTIFICATION_SETTINGS, { "Notifications", view::notification_settings}},
				{ tabs::PROTECTION_SETTINGS, { "Protection", view::protection_settings}},
				{ tabs::DEBUG, { "Debug", view::debug }},
			}}},
			{tabs::PLAYER, {"", view::view_player}}
		};
	public:
		gui_service();
		virtual ~gui_service();

		int nav_ctr = 0;

		navigation_struct* get_selected();
		std::vector<tabs> get_selected_tab();
		bool has_switched_view();
		void set_selected(tabs);
		void set_nav_size(int);
		void increment_nav_size();
		void reset_nav_size();
		std::unordered_map<tabs, navigation_struct> get_navigation();
	};

	inline gui_service* g_gui_service{};
}
