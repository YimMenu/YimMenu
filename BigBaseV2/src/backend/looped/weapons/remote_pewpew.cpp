#include "backend/looped/looped.hpp"
#include "util/math.hpp"
#include "util/vehicle.hpp"
#include "gui.hpp"

namespace big
{
	static auto last_time = std::chrono::steady_clock::now();

	void looped::weapons_remote_pewpew()
	{
		const auto time_now = std::chrono::steady_clock::now();

		const auto elapsed_time_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - last_time).count();

		if (g->self.free_cam == true &&
			g->weapons.remote_pewpew &&
			!g_gui.m_opened &&
			elapsed_time_in_ms >= 100
			&& !HUD::IS_PAUSE_MENU_ACTIVE())
		{
			if (!g->weapons.force_crosshairs) {
				g->weapons.force_crosshairs = true;
				g->self.pew_pew_crosshair = true;
			}
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK)) {
				Vector3 location = self::pos;

				constexpr int rotation_order = 0;
				
				Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(rotation_order);
				float pitch = math::deg_to_rad(rot.x); // vertical
				float yaw = math::deg_to_rad(rot.z); // horizontal
				Vector3 GameplayCamDirection = math::rotation_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0));
				Vector3 StartCoords = CAM::GET_CAM_COORD(CAM::GET_RENDERING_CAM());
				Vector3 EndCoords = math::addVec(StartCoords, math::MulVec(GameplayCamDirection, 500.0f));

				float dist = 5.f;
				location.x += dist * cos(pitch) * cos(yaw);
				location.y += dist * sin(yaw) * cos(pitch);
				location.z += dist * sin(pitch);
				Hash weaponhash;
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);
				WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, false);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(StartCoords.x, StartCoords.y, StartCoords.z, EndCoords.x, EndCoords.y, EndCoords.z, 50, true, weaponhash, PLAYER::PLAYER_PED_ID(), true, false, 0xbf80);

				dist = 150.f;
				Vector3 velocity
				{
					dist * cos(pitch) * cos(yaw),
					dist * sin(yaw) * cos(pitch),
					dist * sin(pitch)
				};
				last_time = time_now;
			}
		}
		else if (g->self.pew_pew_crosshair && !g->weapons.remote_pewpew) {
			g->weapons.force_crosshairs = false;
			g->self.pew_pew_crosshair = false;
		}
	}
}
