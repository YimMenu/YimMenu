#include "super_run.hpp"

#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/math.hpp"

namespace big
{
	void super_run::on_tick()
	{
		if (g_local_player)
		{
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT))
			{
				if (run_speed < run_cap)
					run_speed += .5f;

				Vector3 location = self::pos;
				Ped ped          = self::ped;

				Vector3 rot = ENTITY::GET_ENTITY_ROTATION(ped, 2);
				float yaw   = math::deg_to_rad(rot.z + 90);

				Vector3 offset;
				offset.x = location.x + (run_speed * cos(yaw));
				offset.y = location.y + (run_speed * sin(yaw));
				offset.z = location.z + .2f;

				float groundZ;
				MISC::GET_GROUND_Z_FOR_3D_COORD(offset.x, offset.y, 1000.f, &groundZ, false, false);
				if (groundZ < location.z)
					offset.z = groundZ;

				Vector3 vel = offset - location;

				ENTITY::SET_ENTITY_VELOCITY(ped, vel.x, vel.y, vel.z);

				g_local_player->m_player_info->m_run_speed = .7f;
			}
			else if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_SPRINT))
			{
				run_speed                                  = 10.f;
				g_local_player->m_player_info->m_run_speed = 1.f;
			}
		}
	}

	void super_run::on_disable()
	{
		if (g_local_player)
		{
			run_speed                                  = 10.f;
			g_local_player->m_player_info->m_run_speed = 1.f;
		}
	}
}
