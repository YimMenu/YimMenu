#include "flying_vehicle.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
	void flying_vehicle::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
		{
			g_notification_service->push_warning("Toxic", "Target player is not in any vehicle.");
		}
		else
		{
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, 1, 0.f, 0.f, 50000.f, 0.f, 0.f, 0.f, 0, 0, 1, 1, 0, 1);
			}
		}
	}
}
