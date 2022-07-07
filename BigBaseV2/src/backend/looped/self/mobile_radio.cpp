#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"

namespace big
{

	void looped::self_mobileradio() {
		if (g->self.mobileradio)
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(1);
		else
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(0);
		
	}
}