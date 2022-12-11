#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastMobileRadio = false;

	void looped::self_mobile_radio()
	{
		const bool bMobileRadio = g->self.mobile_radio;

		if (bMobileRadio)
		{
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(true);
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
		}
		else if (bMobileRadio != bLastMobileRadio)
		{
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(false);
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
		}

		bLastMobileRadio = bMobileRadio;
	}
}
