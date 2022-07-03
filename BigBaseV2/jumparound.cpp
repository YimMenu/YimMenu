#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	const int ElementAmount = 10;
	const int ArrSize = ElementAmount * 2 + 2;
	

	Vehicle* vehs = new Vehicle[ArrSize];
	//vehs[0] = ElementAmount;
	int VehFound = PED::GET_PED_NEARBY_VEHICLES(self::ped, vehs);

	void jumparound() {
		
		for (int i = 0; i < VehFound; i++)
		{
			int OffsetID = i * 2 + 2;
			if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(self::ped, false))
			{
				if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehs[OffsetID]))
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(vehs[OffsetID], 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0);
				}
			}
		}
	}
}