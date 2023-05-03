#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class infinite_mag : public looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;
		float og_recoil_value          = 0.0f;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline infinite_mag
		    g_infinite_mag("infclip", "Infinite Clip", "Shoot forever without needing to reload", g.weapons.infinite_mag);
	}
}
