#include "backend/looped_command.hpp"
#include "services/tunables/tunables_service.hpp"

namespace big
{
	class allow_weapons_in_interiors : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (auto tunable = g_tunables_service->get_tunable<PBOOL>("KICK_OUT_OF_NIGHTCLUB_WITH_WEAPON"_J)) [[likely]]
			{
				if (*tunable == TRUE) [[unlikely]]
					*tunable = FALSE;
			}
		}

		virtual void on_disable() override
		{
			if (auto tunable = g_tunables_service->get_tunable<PBOOL>("KICK_OUT_OF_NIGHTCLUB_WITH_WEAPON"_J)) [[likely]]
			{
				*tunable = TRUE;
			}
		}
	};

	allow_weapons_in_interiors g_allow_weaps_inside("allowwepsinside", "VIEW_WEAPON_ALLOW_WEAPONS_IN_INTERIORS", "", g.weapons.interior_weapon);
}
