#include "custom_guns.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"

namespace big
{
	static bool busy = false;

	void custom_guns::loop()
	{
		if (busy) return;
		busy = true;
		
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			cage_gun();
			delete_gun();
			gravity_gun();
			money_gun();
			repair_gun();
			vehicle_gun();

			busy = false;
		}QUEUE_JOB_END_CLAUSE
	}
}