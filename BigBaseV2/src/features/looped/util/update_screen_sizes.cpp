#include "features.hpp"

namespace big
{
	void features::update_screen_sizes()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);
		}QUEUE_JOB_END_CLAUSE
	}
}