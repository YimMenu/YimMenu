#include "sys.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"

namespace big
{
	static bool busy = false;

	void sys::loop()
	{
		if (busy) return;
		busy = true;

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			update_player_structs();
			update_screen_sizes();

			busy = false;
		}QUEUE_JOB_END_CLAUSE
	}
}