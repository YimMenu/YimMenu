#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class infinite_range : public looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;
		float og_range                 = 0.0f;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline infinite_range g_infinite_range("infrange", "Infinite Range", "Kill anything at any distance", g.weapons.infinite_range);
	}
}
