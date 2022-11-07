#include "backend/looped/looped.hpp"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	static const ControllerInputs controls[] =
	{
		ControllerInputs::INPUT_SPRINT,
		ControllerInputs::INPUT_MOVE_UP_ONLY,
		ControllerInputs::INPUT_MOVE_DOWN_ONLY,
		ControllerInputs::INPUT_MOVE_LEFT_ONLY,
		ControllerInputs::INPUT_MOVE_RIGHT_ONLY,
		ControllerInputs::INPUT_DUCK
	};

	static float speed = 20.f;
	static float mult = 0.f;

	static bool bLastNoclip = false;

	static Entity prev = -1;
	static Vector3 rot{};

	void looped::self_noclip_disable_control_action()
	{
		if (g->self.noclip)
		{
			for (const auto& control : controls)
				PAD::DISABLE_CONTROL_ACTION(0, static_cast<int>(control), true);
		}
	}

	void looped::self_noclip()
	{
		const auto bNoclip = g->self.noclip;

		const auto location = self::pos;
		const Entity ent = (self::veh != 0 && g_local_player->m_ped_task_flag & (int)ePedTask::TASK_DRIVING) ? self::veh : self::ped;

		// cleanup when changing entities
		if (prev != ent)
		{
			ENTITY::FREEZE_ENTITY_POSITION(prev, false);
			ENTITY::SET_ENTITY_COLLISION(prev, true, true);

			prev = ent;
		}

		if (bNoclip)
		{
			Vector3 vel = { 0.f, 0.f, 0.f };

			// Left Shift
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT))
				vel.z += speed / 2;
			// Left Control
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_DUCK))
				vel.z -= speed / 2;
			// Forward
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
				vel.y += speed;
			// Backward
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
				vel.y -= speed;
			// Left
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
				vel.x -= speed;
			// Right
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
				vel.x += speed;

			rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
			ENTITY::SET_ENTITY_ROTATION(ent, 0.f, rot.y, rot.z, 2, 0);
			ENTITY::SET_ENTITY_COLLISION(ent, false, false);
			if (vel.x == 0.f && vel.y == 0.f && vel.z == 0.f)
			{
				// freeze entity to prevent drifting when standing still
				ENTITY::FREEZE_ENTITY_POSITION(ent, true);

				mult = 0.f;
			}
			else
			{
				if (mult < 20.f)
					mult += 0.15f;

				ENTITY::FREEZE_ENTITY_POSITION(ent, false);

				const auto offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, vel.x, vel.y, 0.f);
				vel.x = offset.x - location.x;
				vel.y = offset.y - location.y;

				ENTITY::SET_ENTITY_VELOCITY(ent, vel.x * mult, vel.y * mult, vel.z * mult);
			}
		}
		else if (bNoclip != bLastNoclip)
		{
			if (entity::take_control_of(ent))
			{
				ENTITY::FREEZE_ENTITY_POSITION(ent, false);
				ENTITY::SET_ENTITY_COLLISION(ent, true, false);
			}
		}

		bLastNoclip = bNoclip;
	}
}
