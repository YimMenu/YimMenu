#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::tunables_mobileradio() {
		if (g->tunables.mobileradio){
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(1);
	}
		else
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(0);
	}
}