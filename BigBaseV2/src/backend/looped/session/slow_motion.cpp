#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"

namespace big
{

	void looped::session_slowmotion() {
		static float slow_mo;
		slow_mo = g->session.slow_mo;

			if (g->session.slowmotion)
				MISC::SET_TIME_SCALE(slow_mo);
	
			else
				MISC::SET_TIME_SCALE(1.f);
	}
}