#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/math.hpp"

namespace big
{
	static bool bLastFreeCam = false;

	static float speed = 0.5f;
	static float mult = 0.f;

	static Cam cCam = -1;
	static Vector3 vecPosition;
	static Vector3 vecRot;

	void looped::self_free_cam()
	{
		if (g_local_player == nullptr) return;

		Entity ent = PLAYER::PLAYER_PED_ID();
		if (!g->self.free_cam && !bLastFreeCam) return;

		if (g->self.free_cam && !bLastFreeCam)
		{
			cCam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 0);

			vecPosition = CAM::GET_GAMEPLAY_CAM_COORD();
			vecRot = CAM::GET_GAMEPLAY_CAM_ROT(2);

			CAM::SET_CAM_COORD(cCam, vecPosition.x, vecPosition.y, vecPosition.z);
			CAM::SET_CAM_ROT(cCam, vecRot.x, vecRot.y, vecRot.z, 2);
			CAM::SET_CAM_ACTIVE(cCam, true);
			CAM::RENDER_SCRIPT_CAMS(true, true, 500, true, true, 0);

			bLastFreeCam = true;
		}
		else if (!g->self.free_cam && bLastFreeCam)
		{
			CAM::SET_CAM_ACTIVE(cCam, false);
			CAM::RENDER_SCRIPT_CAMS(false, true, 500, true, true, 0);
			CAM::DESTROY_CAM(cCam, false);
			STREAMING::SET_FOCUS_ENTITY(PLAYER::PLAYER_PED_ID());

			bLastFreeCam = false;

			return;
		}

		PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		const int controls[] = { 1, 2, 3, 4, 5, 6, 270, 271, 272, 273 };
		for (int control : controls)
			PAD::ENABLE_CONTROL_ACTION(2, control, true);

		Vector3 vecChange = { 0.f, 0.f, 0.f };

		// Left Shift
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 21))
			vecChange.z += speed / 2;
		// Left Control
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 36))
			vecChange.z -= speed / 2;
		// Forward
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 32))
			vecChange.y += speed;
		// Backward
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 33))
			vecChange.y -= speed;
		// Left
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 34))
			vecChange.x -= speed;
		// Right
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 35))
			vecChange.x += speed;

		if (vecChange.x == 0.f && vecChange.y == 0.f && vecChange.z == 0.f)
			mult = 0.f;
		else if (mult < 10)
			mult += 0.15f;

		Vector3 rot = CAM::GET_CAM_ROT(cCam, 2);
		//float pitch = math::deg_to_rad(rot.x); // vertical
		//float roll = rot.y;
		float yaw = math::deg_to_rad(rot.z); // horizontal

		vecPosition.x += (vecChange.x * cos(yaw) - vecChange.y * sin(yaw)) * mult;
		vecPosition.y += (vecChange.x * sin(yaw) + vecChange.y * cos(yaw)) * mult;
		vecPosition.z += vecChange.z * mult;

		CAM::SET_CAM_COORD(cCam, vecPosition.x, vecPosition.y, vecPosition.z);
		STREAMING::SET_FOCUS_POS_AND_VEL(vecPosition.x, vecPosition.y, vecPosition.z, 0.f, 0.f, 0.f);

		vecRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		CAM::SET_CAM_ROT(cCam, vecRot.x, vecRot.y, vecRot.z, 2);
	}
}