#include "mobile_radio.hpp"

#include "natives.hpp"

namespace big
{
	void mobile_radio::on_tick()
	{
		AUDIO::SET_MOBILE_PHONE_RADIO_STATE(true);
		AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
	}

	void mobile_radio::on_disable()
	{
		AUDIO::SET_MOBILE_PHONE_RADIO_STATE(false);
		AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
	}
}
