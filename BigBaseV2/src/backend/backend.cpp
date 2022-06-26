#include "api/api.hpp"
#include "backend.hpp"
#include "looped/looped.hpp"
#include "thread_pool.hpp"

namespace big
{
	void backend::loop()
	{
		g->attempt_save();
		looped::system_self_globals();
		looped::system_update_pointers();

		if (g_local_player != nullptr && !api::util::signed_in())
		{
			g_thread_pool->push([]
			{
				looped::api_login_session();
			});
		}
	}
}
