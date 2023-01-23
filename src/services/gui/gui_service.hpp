#pragma once
#include "views/view.hpp"

namespace big
{
	enum class tabs {
		NONE,

		SELF,
		WEAPONS,
		TELEPORT,
		MOBILE,

		VEHICLE,
		HANDLING,
		HANDLING_SEARCH,
		HANDLING_SAVED_PROFILE,
		HANDLING_MY_PROFILES,
		HANDLING_CURRENT_PROFILE,
		LSC,
		SPAWN_VEHICLE,
		PV,
		PERSIST_CAR,
		FUN_VEHICLE,

		WORLD,
		SPAWN_PED,
		TIME_AND_WEATHER,
		CREATOR,
		TRAIN,
		WATER,

		NETWORK,
		SESSION,
		MISSIONS,
		SPOOFING,
		PLAYER_DATABASE,
		SESSION_BROWSER,

		SETTINGS,
		STAT_EDITOR,
		CONTEXT_MENU_SETTINGS,
		ESP_SETTINGS,
		GUI_SETTINGS,
		HOTKEY_SETTINGS,
		REACTION_SETTINGS,
		PROTECTION_SETTINGS,
		TRANSLATION_SETTINGS,
		DEBUG,

		PLAYER
	};

	struct navigation_struct
	{
		const char name[32] = "";
		std::function<void()> func = nullptr;
		std::map<tabs, navigation_struct> sub_nav{};
	};

	class gui_service final
	{
		std::vector<tabs> current_tab{};
		bool switched_view = true;

		std::map<tabs, navigation_struct> nav = {
			{tabs::SELF, { "Self",view::self, {
				{ tabs::WEAPONS, { "Weapons", view::weapons }},
				{ tabs::MOBILE, {"Mobile", view::mobile}},
				{ tabs::TELEPORT, {"Teleport", view::teleport}},
			}}},
			{tabs::VEHICLE, { "Vehicle", view::vehicle, {
				{ tabs::HANDLING, {"Handling", view::handling_current_profile, {
					{ tabs::HANDLING_CURRENT_PROFILE, {"Current Profile", view::handling_current_profile } },
					{ tabs::HANDLING_SAVED_PROFILE, {"Saved Profiles", view::handling_saved_profiles } },
				}}},
				{ tabs::LSC, { "LS Customs", view::lsc }},
				{ tabs::SPAWN_VEHICLE, { "Spawn Vehicle", view::spawn_vehicle }},
				{ tabs::PV, { "Personal Vehicle", view::pv }},
				{ tabs::PERSIST_CAR, { "Persist Car", view::persist_car }},
				{ tabs::FUN_VEHICLE, { "Fun Features", view::fun_vehicle }},
			}}},
			{ tabs::WORLD, { "World", nullptr, {
				{ tabs::SPAWN_PED, { "Spawn Ped", view::spawn_ped }},
				{ tabs::TIME_AND_WEATHER, { "Time And Weather", view::time_and_weather }},
				{ tabs::CREATOR, { "Creator", view::creator }},
				{ tabs::TRAIN, { "Train", view::train }},
				{ tabs::WATER, { "Water", view::water }},
		}}},
			{tabs::NETWORK, { "Network", nullptr, {
				{ tabs::SPOOFING, { "Spoofing", view::spoofing }},
				{ tabs::SESSION, { "Session", view::session }},
				{ tabs::MISSIONS, { "Missions", view::missions }},
				{ tabs::PLAYER_DATABASE, { "Player Database", view::player_database }},
				{ tabs::SESSION_BROWSER, { "Session Browser", view::session_browser }},
			}}},
			{tabs::SETTINGS, { "Settings", view::settings, {
				{ tabs::STAT_EDITOR, { "Stat Editor", view::stat_editor}},
				{ tabs::CONTEXT_MENU_SETTINGS, { "Context Menu", view::context_menu_settings}},
				{ tabs::ESP_SETTINGS, { "ESP", view::esp_settings}},
				{ tabs::GUI_SETTINGS, { "GUI", view::gui_settings}},
				{ tabs::HOTKEY_SETTINGS, { "Hotkeys", view::hotkey_settings }},
				{ tabs::REACTION_SETTINGS, { "Reactions", view::reaction_settings}},
				{ tabs::PROTECTION_SETTINGS, { "Protection", view::protection_settings}},
				{ tabs::TRANSLATION_SETTINGS, { "Translation", view::translation_settings}},
				{ tabs::DEBUG, { "Debug", nullptr }},
			}}},
			{tabs::PLAYER, {"", view::view_player}}
		};
	public:
		gui_service();
		virtual ~gui_service();

		int nav_ctr = 0;

		navigation_struct* get_selected();
		std::vector<tabs>& get_selected_tab();
		bool has_switched_view();
		void set_selected(tabs);
		void set_nav_size(int);
		void increment_nav_size();
		void reset_nav_size();
		std::map<tabs, navigation_struct>& get_navigation();
	};

	inline gui_service* g_gui_service{};
}
