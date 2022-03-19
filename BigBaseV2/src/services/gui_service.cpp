#include "gui_service.hpp"

namespace big
{
	gui_service::gui_service()
	{
		g_gui_service = this;
	}

	gui_service::~gui_service()
	{
		g_gui_service = nullptr;
	}

	navigation_struct gui_service::get_selected() {
		if (current_tab.at(0) == tabs::NONE)
			return { "", nullptr };
		navigation_struct current_nav = nav.at(current_tab.at(0));
		if (current_tab.size() > 1) {
			if (auto opt = nav.find(current_nav.sub_nav.at()); opt != nav.end()) {
				current_nav = opt->first;
			}
		}
		return current_nav;
	}

	std::vector<tabs> gui_service::get_selected_tab()
	{
		return current_tab;
	}

	bool gui_service::has_switched_view()
	{
		return switched_view;
	}

	void gui_service::set_selected(tabs tab)
	{
		current_tab = tab;
	}

	std::unordered_map<tabs, navigation_struct> gui_service::get_navigation()
	{
		return nav;
	}


}
