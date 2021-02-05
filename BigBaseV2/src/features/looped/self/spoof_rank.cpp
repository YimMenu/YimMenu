#include "features/self.hpp"
#include "features/functions.hpp"
#include "script_global.hpp"

namespace big
{
	void self::spoof_rank()
	{
		bool bSpoofRank = g_settings.options["spoof_rank"].get<bool>();

		if (bSpoofRank)
			func::spoof_rank(g_settings.options["rank"].get<int>());
	}
}