#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "gui.hpp"
#include "util/math.hpp"
#include "util/vehicle.hpp"

namespace big
{
	static auto last_time = std::chrono::steady_clock::now();

	void looped::weapons_vehicle_gun()
	{
		const bool is_vehicle_gun_selected = g.weapons.custom_weapon == CustomWeapon::VEHICLE_GUN;

		const auto time_now = std::chrono::steady_clock::now();

		const auto elapsed_time_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - last_time).count();

		if (is_vehicle_gun_selected && !g_gui->is_open() && elapsed_time_in_ms >= 100 && PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
		{
			Vector3 location = self::pos;

			constexpr int rotation_order = 2;

			Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(rotation_order);
			float pitch = math::deg_to_rad(rot.x);// vertical
			//float roll = rot.y;
			float yaw = math::deg_to_rad(rot.z + 90);// horizontal

			float dist = 10.f;
			location.x += dist * cos(pitch) * cos(yaw);
			location.y += dist * sin(yaw) * cos(pitch);
			location.z += dist * sin(pitch);
			Vehicle veh = vehicle::spawn(rage::joaat(g.weapons.vehicle_gun_model.data()), location, ENTITY::GET_ENTITY_HEADING(self::ped));

			dist = 150.f;
			Vector3 velocity{dist * cos(pitch) * cos(yaw), dist * sin(yaw) * cos(pitch), dist * sin(pitch)};

			ENTITY::SET_ENTITY_ROTATION(veh, rot.x, rot.y, rot.z, rotation_order, 1);
			ENTITY::SET_ENTITY_VELOCITY(veh, velocity.x, velocity.y, velocity.z);

			// flagging the veh as no longer needed so that the game can remove it
			// when reaching the maximum vehicle limit,
			// allowing the vehicle gun to keep working
			ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);

			last_time = time_now;
		}
	}
}
