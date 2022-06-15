#include "api/api.hpp"
#include "backend/looped/looped.hpp"

namespace big
{
	void looped::api_login_session()
	{
		if (g_local_player == nullptr || api::util::signed_in())
			return;

		api::auth::create_session();
	}
}