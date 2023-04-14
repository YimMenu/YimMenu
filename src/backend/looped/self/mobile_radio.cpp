#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class mobile_radio : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(true);
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
		}

		virtual void on_disable() override
		{
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(false);
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
		}
	};

	mobile_radio g_mobile_radio("mobileradio", "Mobile Radio", "Allows you to listen to the radio on foot", g.self.mobile_radio);
}
