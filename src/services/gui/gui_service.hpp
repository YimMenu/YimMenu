#pragma once
#include "views/view.hpp"

namespace big
{
	enum class tabs
	{
		NONE,

		SELF,
		WEAPONS,
		TELEPORT,
		CUSTOM_TELEPORT,
		OUTFIT_EDITOR,
		ANIMATIONS,
		SCENARIOS,
		CASINO,
		PTFX_EFFECTS,

		VEHICLE,
		LSC,
		SPAWN_VEHICLE,

		WORLD,
		SPAWNED_VEHICLES,
		SPAWN_OBJECTS,

		NETWORK,
		SESSION_BROWSER,
		BAD_PLAYERS,
		CHAT,

		SETTINGS,
		CONTEXT_MENU_SETTINGS,
		ESP_SETTINGS,
		GTA_CACHE_SETTINGS,
		GUI_SETTINGS,
		REACTION_SETTINGS,
		PROTECTION_SETTINGS,
		DEBUG,

		PLAYER
	};

	struct navigation_struct
	{
		char name[48]              = "";
		std::function<void()> func = nullptr;
		std::map<tabs, navigation_struct> sub_nav{};
		rage::joaat_t hash = rage::joaat(name);
	};


	class gui_service final
	{
		std::vector<tabs> current_tab{};

		std::map<tabs, navigation_struct> nav = {
		    {
		        tabs::SELF,
		        {
		            "Self",
		            view::self,
		            {
		                {tabs::WEAPONS, {"Weapons", view::weapons}},
		                {tabs::TELEPORT, {"Teleport", view::teleport, {{tabs::CUSTOM_TELEPORT, {"Custom Teleport", view::custom_teleport}}}}},
		                {tabs::OUTFIT_EDITOR, {"Outfit Editor", view::outfit_editor}},
		                {tabs::ANIMATIONS, {"Animations", view::animations}},
		                {tabs::SCENARIOS, {"Scenarios", view::scenarios}},
		                {tabs::PTFX_EFFECTS, {"Ptfx Effects", view::ptfx_effects}},
		            },
		        },
		    },
		    {
		        tabs::VEHICLE,
		        {
		            "Vehicle",
		            view::vehicle,
		            {
		                {tabs::LSC, {"LSC", view::lsc}},
		                {tabs::SPAWN_VEHICLE, {"Spawn Vehicle", view::spawn_vehicle}},
		            },
		        },
		    },
		    {
		        tabs::WORLD,
		        {
		            "World",
		            view::world,
		            {
		                {tabs::CASINO, {"Casino", view::casino}},
		                {tabs::SPAWNED_VEHICLES, {"Spawned Vehicles", view::spawned_vehicles}},
		                {tabs::SPAWN_OBJECTS, {"Spawn Objects", view::spawn_objects}},
		            },
		        },
		    },
		    {
		        tabs::NETWORK,
		        {
		            "Network",
		            view::network,
		            {
		                {tabs::SESSION_BROWSER, {"Session Browser", view::session_browser}},
		                {tabs::BAD_PLAYERS, {"Bad Players", view::bad_players}},
		                {tabs::CHAT, {"Chat", view::chat}},
		            },
		        },
		    },
		    {
		        tabs::SETTINGS,
		        {
		            "Settings",
		            [this] {
			            this->set_selected(tabs::ESP_SETTINGS);
		            },
		            {
		                {tabs::ESP_SETTINGS, {"ESP", view::esp_settings}},
		                {tabs::GTA_CACHE_SETTINGS, {"GTA Cache", view::gta_cache}},
		                {tabs::GUI_SETTINGS, {"GUI", view::gui_settings}},
		                {tabs::REACTION_SETTINGS, {"Reactions", view::reaction_settings}},
		                {tabs::PROTECTION_SETTINGS, {"Protection", view::protection_settings}},
		                {tabs::DEBUG, {"Debug", view::debug}},
		            },
		        },
		    },
		    {
		        tabs::PLAYER,
		        {"", view::view_player},
		    },
		};

		void remove_from_nav_internal(std::map<big::tabs, big::navigation_struct>& nav, big::tabs existing_tab_id);

	public:
		gui_service();
		virtual ~gui_service();

		int nav_ctr = 0;

		navigation_struct* get_selected();
		std::vector<tabs>& get_selected_tab();
		void set_selected(tabs);
		void set_nav_size(int);
		void increment_nav_size();
		void reset_nav_size();
		std::map<tabs, navigation_struct>& get_navigation();
		void remove_from_nav(tabs existing_tab_id);
	};

	inline gui_service* g_gui_service{};
}