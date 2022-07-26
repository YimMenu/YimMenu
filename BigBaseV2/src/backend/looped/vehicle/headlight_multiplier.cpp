#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{

	void looped::vehicle_headlightmul() {
		static float headlightmul_val;
		headlightmul_val = g->vehicle.headlightmul_val;

		if (g->vehicle.headlightmul)
			VEHICLE::SET_VEHICLE_LIGHT_MULTIPLIER(self::veh, headlightmul_val);

		else
			VEHICLE::SET_VEHICLE_LIGHT_MULTIPLIER(self::veh, 1.f);
	}
}