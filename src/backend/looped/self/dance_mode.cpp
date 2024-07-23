#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "script_function.hpp"
#include "services/script_patcher/script_patcher_service.hpp"
#include "util/scripts.hpp"

namespace big
{
	bool bLastDanceMode = false;
	void looped::self_dance_mode()
	{
		if (g.self.dance_mode && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_J) > 0)
			g.self.dance_mode = false;

		if (g.self.dance_mode && g.self.dance_mode != bLastDanceMode)
		{
			g_script_patcher_service->update();
			scripts::request_script("am_mp_nightclub"_J);
			if (!scripts::wait_till_loaded("am_mp_nightclub"_J))
				return;

			auto thread = SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH("am_mp_nightclub"_J, 19400 /*PROPERTY_INT*/);
			SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED("am_mp_nightclub"_J);

			if (!thread)
				return;

			g.m_dance_thread  = gta_util::find_script_thread_by_id(thread);
			g.m_dance_program = gta_util::find_script_program("am_mp_nightclub"_J);

			g.m_dance_thread->m_context.m_state = rage::eThreadState::unk_3;

			// perform initial setup
			gta_util::execute_as_script(g.m_dance_thread, [] {
				NETWORK::NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(32, true, 32);
				scr_functions::init_nightclub_script({});
			});

			scr_functions::dance_loop.populate_ip();
			bLastDanceMode = true;
			return;
		}

		if (!g.self.dance_mode && g.self.dance_mode != bLastDanceMode)
		{
			if (g.m_dance_thread)
				g.m_dance_thread->kill();

			g.m_dance_thread  = nullptr;
			g.m_dance_program = nullptr;

			g_script_patcher_service->update();
			bLastDanceMode = false;
			return;
		}

		if (g.self.dance_mode && g.m_dance_thread->m_handler)
		{
			*scr_globals::dance_state.as<PINT>() = TRUE; //Never once do the scripts read this as a boolean. It seems to be some kind of state the player is in. Runs from 4 to 35.
			scr_functions::dance_loop.call(g.m_dance_thread, g.m_dance_program, {});
		}
	}
}
