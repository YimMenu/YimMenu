#include "backend/looped_command.hpp"
#include "services/tunables/tunables_service.hpp"

namespace big
{
	class bypass_dupe_detector : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (auto tunable = g_tunables_service->get_tunable<PBOOL>("ENABLED_DOZER_DETECTOR"_J)) [[likely]]
			{
				if (*tunable == TRUE) [[unlikely]]
					*tunable = FALSE;
			}
		}
	};

	bool always_on = true;
	bypass_dupe_detector g_bypass_dupe_detector("dupedetector", "DUPE_DETECTOR", "", always_on);
}