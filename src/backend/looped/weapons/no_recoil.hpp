#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class no_recoil : public looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;
		float og_recoil_value          = 0.0f;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline no_recoil g_no_recoil("norecoil", "No Recoil", "Removes weapon recoil when shooting", g.weapons.no_recoil);
	}
}
