#include "protections.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"

namespace big
{
	static bool busy = false;

	void protections::loop()
	{
		if (busy) return;
		busy = true;

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			replay_interface();

			busy = false;
		}QUEUE_JOB_END_CLAUSE
	}
}