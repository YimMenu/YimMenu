#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class npcs_ignore : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			std::vector<Entity> p_nearbyPeds;

			p_nearbyPeds.clear();

			INT i, offsettedID, count = 100;
			Ped* peds = new Ped[count * 2 + 2];
			INT nearby_found = PED::GET_PED_NEARBY_PEDS(self::ped, (Any*)peds, -1);
			for (i = 0; i < nearby_found; i++)
			{
				offsettedID = i * 2 + 2;
				if (!ENTITY::DOES_ENTITY_EXIST(peds[offsettedID]))
					continue;

				p_nearbyPeds.push_back(peds[offsettedID]);
			}
			delete[] peds;
			
			for (auto& ped : p_nearbyPeds)
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ped);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
				PED::SET_PED_FLEE_ATTRIBUTES(ped, 0, 0);
				PED::SET_PED_COMBAT_ATTRIBUTES(ped, 17, 1);
			}

			PLAYER::SET_POLICE_IGNORE_PLAYER(self::id, 1);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(self::id, 1);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(self::id, 0);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(self::id, 1);
		}

		virtual void on_disable() override
		{
			PLAYER::SET_POLICE_IGNORE_PLAYER(self::id, 0);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(self::id, 0);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(self::id, 1);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(self::id, 0);
		}
	};

	npcs_ignore g_npcs_ignore("npcsignore", "NPCs Ignore", "NPCs doesnt react to your actions (Only Nearby NPCs)", g.self.npcs_ignore);
}
