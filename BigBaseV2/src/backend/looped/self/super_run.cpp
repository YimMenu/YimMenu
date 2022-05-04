#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/math.hpp"

namespace big
{
	static float run_speed = 10.f;
	static float run_cap = 100.f;
	static bool super_run_state = false;

	void looped::self_super_run()
	{
		if (g->self.super_run && PAD::IS_CONTROL_PRESSED(0, 21))
		{
			if (run_speed < run_cap) run_speed += .5f;

			Ped player = PLAYER::PLAYER_PED_ID();

			Vector3 pos = ENTITY::GET_ENTITY_COORDS(player, true);

			//Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
			Vector3 rot = ENTITY::GET_ENTITY_ROTATION(player, 2);
			float yaw = math::deg_to_rad(rot.z + 90);

			Vector3 offset;
			offset.x = pos.x + (run_speed * cos(yaw));
			offset.y = pos.y + (run_speed * sin(yaw));
			offset.z = pos.z + .2f;

			float groundZ;
			MISC::GET_GROUND_Z_FOR_3D_COORD(offset.x, offset.y, 1000.f, &groundZ, false, false);
			if (groundZ < pos.z)
				offset.z = groundZ;

			Vector3 vel = offset - pos;

			ENTITY::SET_ENTITY_VELOCITY(player, vel.x, vel.y, vel.z);

			g_local_player->m_player_info->m_run_speed = .7f;
		}
		else if (!g->self.super_run && g->self.super_run != super_run_state)
		{
			g_local_player->m_player_info->m_run_speed = 1.f;
		}
		else if (PAD::IS_CONTROL_JUST_RELEASED(0, 21))
		{
			run_speed = 10.f;
			g_local_player->m_player_info->m_run_speed = 1.f;
		}

		super_run_state = g->self.super_run;
	}
}