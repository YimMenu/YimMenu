#include "backend/looped/looped.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/entity.hpp"

namespace big
{
	static const int controls[] = { 21, 32, 33, 34, 35, 36 };
	static float speed = 20.f;
	static float mult = 0.f;

	static bool bLastNoclip = false;

	static Entity prev = -1;
	static Vector3 rot{};

	void looped::self_noclip() {
		bool bNoclip = g->self.noclip;

		Entity ent = PLAYER::PLAYER_PED_ID();
		bool bInVehicle = PED::IS_PED_IN_ANY_VEHICLE(ent, true);
		if (bInVehicle) ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

		// cleanup when changing entities
		if (prev != ent)
		{
			ENTITY::FREEZE_ENTITY_POSITION(prev, false);
			ENTITY::SET_ENTITY_COLLISION(prev, true, true);

			prev = ent;
		}

		if (bNoclip)
		{
			for (int control : controls)
				PAD::DISABLE_CONTROL_ACTION(0, control, true);

			Vector3 cur_pos = ENTITY::GET_ENTITY_COORDS(ent, true);
			Vector3 vel = { 0.f, 0.f, 0.f };
			float heading = 0.f;

			// Left Shift
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 21))
				vel.z += speed / 2;
			// Left Control
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 36))
				vel.z -= speed / 2;
			// Forward
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 32))
				vel.y += speed;
			// Backward
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 33))
				vel.y -= speed;
			// Left
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 34))
				vel.x -= speed;
			// Right
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 35))
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

				Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, vel.x, vel.y, 0.f);
				vel.x = offset.x - cur_pos.x;
				vel.y = offset.y - cur_pos.y;

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