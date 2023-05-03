#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class seatbelt : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline seatbelt g_seatbelt("seatbelt", "Seatbelt", "Prevent you from falling off bikes or flying through the windshield",
		    g.vehicle.seatbelt);
	}
}
