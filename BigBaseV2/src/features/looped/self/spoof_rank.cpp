#include "features.hpp"
#include "script_global.hpp"

namespace big
{
	void features::spoof_rank()
	{
		bool bSpoofRank = g_settings.options["spoof_rank"].get<bool>();

		if (bSpoofRank)
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				func::spoof_rank(g_settings.options["rank"].get<int>());
			}QUEUE_JOB_END_CLAUSE
		}
	}
}