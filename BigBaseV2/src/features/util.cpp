#include "util.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"

namespace big
{
	static bool busy = false;

	void util::loop()
	{
		if (busy) return;
		busy = true;

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			spectate_player();

			busy = false;
		}QUEUE_JOB_END_CLAUSE
	}
}