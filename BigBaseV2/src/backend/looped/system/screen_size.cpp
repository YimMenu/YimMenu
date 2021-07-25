#include "backend/looped/looped.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	void looped::system_screen_size()
	{
		GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&g.window.x, &g.window.y);
	}
}