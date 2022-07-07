#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	void looped::session_jumparound() {
		const int ElementAmount = 10;
		const int ArrSize = ElementAmount * 2 + 2;
		if (g->session.jumparound) {
			Vehicle* vehs = new Vehicle[ArrSize];
			Ped* peds = new Ped[ArrSize];
			vehs[0] = ElementAmount;
			peds[0] = ElementAmount;
			int VehFound = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);
			int PedFound = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1);

			for (int i = 0; i < VehFound; i++)
			{
				int OffsetID = i * 2 + 2;
				if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true))
				{
					if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehs[OffsetID]))
					{
						ENTITY::APPLY_FORCE_TO_ENTITY(vehs[OffsetID], 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0);
						ENTITY::APPLY_FORCE_TO_ENTITY(peds[OffsetID], 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0);
					}
				}
			}
		}

	}
}