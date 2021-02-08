#include "features/self.hpp"
#include "features/functions.hpp"
#include "script_global.hpp"

namespace big
{
	void self::spoof_rank()
	{
		auto& spoofing = g_settings.options["spoofing"]["rank"];

		bool bSpoofRank = spoofing["enabled"].get<bool>();

		if (bSpoofRank)
			func::spoof_rank(spoofing["value"].get<int>());
	}
}