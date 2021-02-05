#include "features/sys.hpp"
#include "fiber_pool.hpp"

namespace big
{
	void sys::update_screen_sizes()
	{
		g_fiber_pool->queue_job([]
		{
			GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);
		});
	}
}