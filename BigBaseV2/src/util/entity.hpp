#pragma once
#include "natives.hpp"
#include "script.hpp"

namespace big::entity
{
	inline bool take_control_of(Entity ent)
	{
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent)) return true;
		for (uint8_t i = 0; !NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent) && i < 5; i++)
		{
			bool in_spectator = NETWORK::NETWORK_IS_IN_SPECTATOR_MODE();
			if (in_spectator) NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(0, PLAYER::PLAYER_PED_ID());

			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ent);

			if (in_spectator) NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(1, PLAYER::PLAYER_PED_ID());

			script::get_current()->yield();
		}
		if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent)) return false;

		int netHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, true);

		return true;
	}
}