#include "self.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "script.hpp"

namespace big
{
	static bool busy = false;

	void self::loop()
	{
		g_local_ped = gta_util::get_local_ped();

		if (busy) return;
		busy = true;

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			god_mode();
			never_wanted();
			no_ragdoll();
			noclip();
			off_radar();
			spoof_rank();
			frame_flags();
			super_sprint();

			busy = false;
		}QUEUE_JOB_END_CLAUSE
	}
}