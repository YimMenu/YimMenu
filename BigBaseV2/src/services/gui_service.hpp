#pragma once
#include "views/view.hpp"

namespace big
{
	enum class tabs {
		DEBUG,
		MOBILE,
		NONE,
		NETWORK,
		PLAYER,
		SELF,
		SESSION,
		SETTINGS,
		SPAWN,
		SPOOFING,
		TELEPORT,
		VEHICLE,
		WEAPONS,
	};

	struct navigation_struct
	{
		const char name[32] = "";
		std::function<void()> func = nullptr;
		std::unordered_map<tabs, navigation_struct> sub_nav{};
	};

	class gui_service final
	{
		std::vector<tabs> current_tab{ tabs::SELF, tabs::WEAPONS };
		bool switched_view = true;

		std::unordered_map<tabs, navigation_struct> nav = {
			{
				tabs::SELF,
				{
					"Self",view::self, {
						{ tabs::WEAPONS, {"Weapons", view::weapons}},
					}
				}
			},
			{tabs::NETWORK, { "Network", nullptr, {
				{tabs::SPOOFING, { "Spoofing", view::spoofing }},
				{tabs::SESSION, { "Session", view::session }},
			}}},
		};
	public:
		gui_service();
		virtual ~gui_service();

		navigation_struct get_selected();
		std::vector<tabs> get_selected_tab();
		bool has_switched_view();
		void set_selected(tabs);
		std::unordered_map<tabs, navigation_struct> get_navigation();
	};

	inline gui_service* g_gui_service{};
}
