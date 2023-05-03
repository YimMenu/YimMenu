#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class no_spread : public looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;
		float og_spread_value          = 0.0f;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline no_spread g_no_spread("nospread", "No Spread", "Removes weapon spread when shooting", g.weapons.no_spread);
	}
}
