#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_global.hpp"
#include "util/scripts.hpp"
#include "script.hpp"
#include "core/enums.hpp"
#include "gta/joaat.hpp"

namespace big
{
	void looped::script_starter()
	{
		/*if (g->tunables.ambiant_ufos)
		{
            Hash hash = rage::joaat("ufo");
			if (!scripts::is_running(hash) && NETWORK::NETWORK_IS_GAME_IN_PROGRESS())
            {
                scripts::request_script(hash);
                if (scripts::wait_till_loaded(hash))
                {
                    scripts::start_script(hash, 1424);

                    scripts::wait_till_running(hash);
                }
            }
		}
        if (g->tunables.ambiant_blimp)
        {
            Hash hash = rage::joaat("blimp");
            if (!scripts::is_running(hash))
            {
                scripts::request_script(hash);
                if (scripts::wait_till_loaded(hash))
                {
                    scripts::start_script(hash, 1424);

                    scripts::wait_till_running(hash);
                }
            }
        }*/
        if (((self::pos.x >= -800.f && self::pos.y >= 5300.f) && self::pos.x <= 640.f) && self::pos.y <= 5800.f)
        {
            LOG(G3LOG_DEBUG) << "trying to start cablecar1";
            Hash hash = rage::joaat("cablecar");
            if (!scripts::is_running(hash))
            {
                LOG(G3LOG_DEBUG) << "trying to start cablecar2";
                scripts::request_script(hash);
                if (scripts::wait_till_loaded(hash))
                {
                    scripts::start_script(hash, 1424);

                    scripts::wait_till_running(hash);
                }
            }
        }
	}
}