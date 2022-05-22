#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/math.hpp"

namespace big
{
	static float run_speed = 10.f;
	static float run_cap = 100.f;
	static bool super_run_state = false;

	void looped::self_super_run()
	{
		if (g->self.super_run && PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT))
		{
			if (run_speed < run_cap) run_speed += .5f;

			Vector3 location = self::pos;
			Ped ped = self::ped;

			//Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
			Vector3 rot = ENTITY::GET_ENTITY_ROTATION(ped, 2);
			float yaw = math::deg_to_rad(rot.z + 90);

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
		else if (!g->self.super_run && g->self.super_run != super_run_state)
		{
			g_local_player->m_player_info->m_run_speed = 1.f;
		}
		else if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_SPRINT))
		{
			run_speed = 10.f;
			g_local_player->m_player_info->m_run_speed = 1.f;
		}

		super_run_state = g->self.super_run;
	}
}