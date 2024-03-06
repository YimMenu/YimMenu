#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "gui.hpp"
#include "util/math.hpp"
#include "util/vehicle.hpp"
#include "util/ped.hpp"
#include <numbers>

namespace big
{
	static auto last_time = std::chrono::steady_clock::now();

	inline Entity e_shark;
	void looped::weapons_shark_gun()
	{
		const bool is_shark_gun_selected = g.weapons.custom_weapon == CustomWeapon::SHARK_GUN;

		const auto time_now = std::chrono::steady_clock::now();

		const auto elapsed_time_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - last_time);

		if (is_shark_gun_selected && !g_gui->is_open() && elapsed_time_in_ms >= 100ms && PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK)
		    && (!g.self.custom_weapon_stop || WEAPON::IS_PED_ARMED(self::ped, 4 | 2)))
		{
				Vector3 location = self::pos;


				constexpr int rotation_order = 2;

				Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(rotation_order);
				float pitch = math::deg_to_rad(rot.x); // vertical
				//float roll = rot.y;
				float yaw = math::deg_to_rad(rot.z + 90); // horizontal

				float dist = 10.f;
				location.x += dist * cos(pitch) * cos(yaw);
				location.y += dist * sin(yaw) * cos(pitch);
				location.z += dist * sin(pitch);

				//Hash shark_model = rage::joaat("a_c_sharkhammer");
			
				Ped animal = ped::spawn(PED_TYPE_ANIMAL, rage::joaat(g.weapons.animal.data()), 0, location, ENTITY::GET_ENTITY_HEADING(self::ped), 1);

				dist = 150.f;
				Vector3 velocity{dist * cos(pitch) * cos(yaw), dist * sin(yaw) * cos(pitch), dist * sin(pitch)};

				ENTITY::SET_ENTITY_HEALTH(animal, 0, 0, 0);
			    ENTITY::SET_ENTITY_ROTATION(animal, rot.x, rot.y, rot.z, rotation_order, 1);
			    ENTITY::SET_ENTITY_VELOCITY(animal, velocity.x, velocity.y, velocity.z);

				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(animal);

				last_time = time_now;
		}
	}
}
