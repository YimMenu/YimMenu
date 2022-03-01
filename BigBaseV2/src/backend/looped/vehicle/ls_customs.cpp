#include "backend/looped/looped.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "util/math.hpp"
#include "util/scripts.hpp"

namespace big
{
	static bool state = false;
	static bool busy = false;

	void looped::vehicle_ls_customs()
	{
		if (busy) return;
		busy = true;

		constexpr int hash = RAGE_JOAAT("carmod_shop");
		if (g->vehicle.ls_customs && g->vehicle.ls_customs == state)
		{
			if (
				auto carmod_shop_thread = gta_util::find_script_thread(hash);
				carmod_shop_thread &&
				*script_local(carmod_shop_thread, 726).at(11).as<int*>() != 4
				)
			{
				g->vehicle.ls_customs = false;

				*script_local(carmod_shop_thread, 726).as<int*>() = 1; // cleanup
			}
		}

		if (g->vehicle.ls_customs && g->vehicle.ls_customs != state)
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			if (!ENTITY::DOES_ENTITY_EXIST(veh) || ENTITY::IS_ENTITY_DEAD(veh, false))
			{
				busy = false;
				g->vehicle.ls_customs = false;

				g_notification_service->push_warning("LS Customs", "You aren't in a vehicle.");

				return;
			}

			scripts::request_script(hash);
			if (scripts::wait_till_loaded(hash))
			{
				int args[] = { 45, 0, 9 };
				scripts::start_script_with_args(hash, args, 3, 3600);

				scripts::wait_till_running(hash);
			}

			if (scripts::is_running(hash))
			{
				if (auto carmod_shop_thread = gta_util::find_script_thread(hash); carmod_shop_thread)
				{
					*script_local(carmod_shop_thread, 726).at(406).as<int*>() = veh;
					*script_local(carmod_shop_thread, 2110).as<bool*>() = false; // skips cutscene that's invisible

					*script_local(carmod_shop_thread, 726).at(11).as<int*>() = 4;
				}
			}
		}

		busy = false;
		state = g->vehicle.ls_customs;
	}
}