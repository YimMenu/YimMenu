#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"

namespace big
{

	void looped::session_slowmotion() {
			if (g->session.slowmotion)
				MISC::SET_TIME_SCALE(0.2f);
	
			else
				MISC::SET_TIME_SCALE(1.f);
	}
}