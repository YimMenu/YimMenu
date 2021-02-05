#include "vehicle.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"

namespace big
{
	static bool busy = false;

	void vehicle::loop()
	{
		if (busy) return;
		busy = true;

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			handling();
			no_bike_fall();
			speedo_meter();
			sticky_tyres();

			busy = false;
		}QUEUE_JOB_END_CLAUSE
	}
}