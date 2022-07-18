#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	void looped::session_rainbowtraffic() {
		const int ElementAmount = 10;
		const int ArrSize = ElementAmount * 2 + 2;
		if (g->session.rainbowtraffic) {
			Vehicle* vehs = new Vehicle[ArrSize];
			vehs[0] = ElementAmount;
			int VehFound = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);

			for (int i = 0; i < VehFound; i++)
			{
				int OffsetID = i * 2 + 2;
				if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true))
				{
					if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehs[OffsetID]))
					{
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehs[OffsetID], g->rgb.r, g->rgb.g, g->rgb.b);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehs[OffsetID], g->rgb.r, g->rgb.g, g->rgb.b);
						VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(vehs[OffsetID], 0, 1);
						VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(vehs[OffsetID], 1, 1);
						VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(vehs[OffsetID], 2, 1);
						VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(vehs[OffsetID], 3, 1);
						VEHICLE::SET_VEHICLE_NEON_LIGHTS_COLOUR_(vehs[OffsetID], g->rgb.r, g->rgb.g, g->rgb.b);
					}
				}
			}
		}

	}
}