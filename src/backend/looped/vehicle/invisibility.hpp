#pragma once

#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class vehinvisibility : public looped_command
	{
		using looped_command::looped_command;

		bool last_driving = false;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline vehinvisibility
		    g_vehinvisibility("invisveh", "Vehicle Invisiblity", "Makes your car invisible", g.vehicle.vehinvisibility);

		inline bool_command g_localveh_visibility("localinvisveh", "Visible Locally", "Makes your car visible to yourself, other players will still not be able to see it",
		    g.vehicle.localveh_visibility);
	}
}
