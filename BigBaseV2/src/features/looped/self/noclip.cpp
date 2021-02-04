#include "features.hpp"

namespace big
{
	static const int controls[] = { 21, 32, 33, 34, 35, 36 };
	static const float speed = 20.f;
	static const float headingSpeed = 3.f;

	static bool bLastNoClip;

	void features::noclip()
	{
		bool bNoclip = g_settings.options["noclip"]["enabled"];
		float fHorizontal = g_settings.options["noclip"]["horizontal"];
		float fVertical = g_settings.options["noclip"]["vertical"];

		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId);
		bool inVehicle = PED::IS_PED_IN_ANY_VEHICLE(ent, true);
		if (inVehicle) ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

		if (bNoclip)
		{
			func::take_control_of_entity(ent);

			ENTITY::SET_ENTITY_COLLISION(ent, false, false);

			for (int control : controls)
				PAD::DISABLE_CONTROL_ACTION(0, control, true);

			Vector3 cur_pos = ENTITY::GET_ENTITY_COORDS(ent, true);
			Vector3 vel = { 0.f, 0.f, 0.07f };
			float heading = 0.f;

			// Left Shift
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 21))
				vel.z += speed;
			// Left Control
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 36))
				vel.z -= speed;
			// Forward
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 32))
				vel.y += speed;
			// Backward
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 33))
				vel.y -= speed;
			// Left
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 34))
			{
				if (inVehicle) heading += headingSpeed;
				vel.x -= speed;
			}
			// Right
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 35))
			{
				if (inVehicle) heading -= headingSpeed;
				vel.x += speed;
			}

			Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, vel.x, vel.y, 0.f);
			vel.x = offset.x - cur_pos.x;
			vel.y = offset.y - cur_pos.y;

			ENTITY::SET_ENTITY_ROTATION(ent, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(ent) + heading, 0, true);

			ENTITY::SET_ENTITY_VELOCITY(ent, vel.x * fHorizontal, vel.y * fHorizontal, vel.z * fVertical);
		}
		else if (!bNoclip && bNoclip != bLastNoClip)
		{
			func::take_control_of_entity(ent);

			ENTITY::SET_ENTITY_COLLISION(ent, true, true);
		}

		bLastNoClip = bNoclip;
	}
}