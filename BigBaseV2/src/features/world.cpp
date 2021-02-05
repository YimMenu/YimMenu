#include "world.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"

namespace big
{
	static bool busy = false;

	void world::loop()
	{
		if (busy) return;
		busy = true;

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			population_modifiers();

			busy = false;
		}QUEUE_JOB_END_CLAUSE
	}
}