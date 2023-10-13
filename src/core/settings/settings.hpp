#pragma once

namespace big
{
	inline struct g_settings_t
	{
		struct hotkeys
		{
			int menu_toggle = VK_INSERT;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(hotkeys, menu_toggle)
		} hotkeys{};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_settings_t, hotkeys)
	} g_settings{};
}