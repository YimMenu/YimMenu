#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class mobile_radio : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline mobile_radio g_mobile_radio("mobileradio", "Mobile Radio", "Allows you to listen to the radio on foot", g.self.mobile_radio);
	}
}
