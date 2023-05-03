#pragma once

#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class noclip : public looped_command
	{
		using looped_command::looped_command;

		Entity m_entity;
		float m_speed_multiplier;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline noclip g_noclip("noclip", "No Clip", "Allows you to fly through the map", g.self.noclip);
	}
}
