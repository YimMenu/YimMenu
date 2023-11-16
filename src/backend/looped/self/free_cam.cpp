#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/math.hpp"

namespace big
{
	static const ControllerInputs controls[] = {ControllerInputs::INPUT_LOOK_LR, ControllerInputs::INPUT_LOOK_UD, ControllerInputs::INPUT_LOOK_UP_ONLY, ControllerInputs::INPUT_LOOK_DOWN_ONLY, ControllerInputs::INPUT_LOOK_LEFT_ONLY, ControllerInputs::INPUT_LOOK_RIGHT_ONLY, ControllerInputs::INPUT_LOOK_LEFT, ControllerInputs::INPUT_LOOK_RIGHT, ControllerInputs::INPUT_LOOK_UP, ControllerInputs::INPUT_LOOK_DOWN};

	class free_cam : looped_command
	{
		using looped_command::looped_command;

		float speed = 0.5f;
		float mult  = 0.f;

		Cam camera = -1;
		Vector3 position;
		Vector3 rotation;

		inline bool can_update_location()
		{
			return !(g.cmd_executor.enabled || g.self.noclip);
		}

		void spawn_bullet(Vector3 start, Vector3 direction)
		{
			Hash weaponHash = MISC::GET_HASH_KEY("WEAPON_PISTOL"); // for test

			Hash groupHash = PLAYER::GET_PLAYER_GROUP(self::ped);

			Vector3 end = {start.x + direction.x * 1000.0f, start.y + direction.y * 1000.0f, start.z + direction.z * 1000.0f};

			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(start.x,
			    start.y,
			    start.z,
			    end.x,
			    end.y,
			    end.z,
			    100,  // damage
			    true, 
			    weaponHash,
			    self::ped,
			    true,
			    false,
			    -1.0f);
		}

		virtual void on_enable() override
		{
			camera = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 0);

			position = CAM::GET_GAMEPLAY_CAM_COORD();
			rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);

			ENTITY::FREEZE_ENTITY_POSITION(self::veh, true);

			CAM::SET_CAM_COORD(camera, position.x, position.y, position.z);
			CAM::SET_CAM_ROT(camera, rotation.x, rotation.y, rotation.z, 2);
			CAM::SET_CAM_ACTIVE(camera, true);
			CAM::RENDER_SCRIPT_CAMS(true, true, 500, true, true, 0);
		}

		virtual void on_tick() override
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);

			for (const auto& control : controls)
				PAD::ENABLE_CONTROL_ACTION(0, static_cast<int>(control), true);

			Vector3 vecChange = {0.f, 0.f, 0.f};

			if (can_update_location())
			{
				// Left Shift
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT))
					vecChange.z += speed / 2;
				// Left Control
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_DUCK))
					vecChange.z -= speed / 2;
				// Forward
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
					vecChange.y += speed;
				// Backward
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
					vecChange.y -= speed;
				// Left
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
					vecChange.x -= speed;
				// Right
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
					vecChange.x += speed;
			}

			if (vecChange.x == 0.f && vecChange.y == 0.f && vecChange.z == 0.f)
				mult = 0.f;
			else if (mult < 10)
				mult += 0.15f;

			Vector3 rot = CAM::GET_CAM_ROT(camera, 2);
			//float pitch = math::deg_to_rad(rot.x); // vertical
			//float roll = rot.y;
			float yaw = math::deg_to_rad(rot.z); // horizontal

			position.x += (vecChange.x * cos(yaw) - vecChange.y * sin(yaw)) * mult;
			position.y += (vecChange.x * sin(yaw) + vecChange.y * cos(yaw)) * mult;
			position.z += vecChange.z * mult;

			CAM::SET_CAM_COORD(camera, position.x, position.y, position.z);
			STREAMING::SET_FOCUS_POS_AND_VEL(position.x, position.y, position.z, 0.f, 0.f, 0.f);

			rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
			CAM::SET_CAM_ROT(camera, rotation.x, rotation.y, rotation.z, 2);

			if (PAD::GET_DISABLED_CONTROL_NORMAL(0, (int)ControllerInputs::INPUT_ATTACK) && g.self.free_cam.weapon)
			{

				Vector3 camPosition = CAM::GET_CAM_COORD(camera);
				Vector3 camRotation = CAM::GET_CAM_ROT(camera, 2);

				// Convert rotation to radians
				float pitch = math::deg_to_rad(camRotation.x);
				float yaw   = math::deg_to_rad(camRotation.z);

				// Calculate direction vector
				Vector3 direction = {
				    -sin(yaw) * cos(pitch), // Left/right movement
				    cos(yaw) * cos(pitch),  // Up/down movement
				    sin(pitch)              // Diagonal movement
				};

				// Normalize vector
				float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
				if (length > 0.0f)
				{
					direction.x /= length;
					direction.y /= length;
					direction.z /= length;
				}


				spawn_bullet(position, direction);

			}
		}

		virtual void on_disable() override
		{
			CAM::SET_CAM_ACTIVE(camera, false);
			CAM::RENDER_SCRIPT_CAMS(false, true, 500, true, true, 0);
			CAM::DESTROY_CAM(camera, false);
			STREAMING::CLEAR_FOCUS();

			ENTITY::FREEZE_ENTITY_POSITION(self::veh, false);
		}
	};

	free_cam g_free_cam("freecam", "FREECAM", "FREECAM_DESC", g.self.free_cam.enabled);
	bool_command g_free_cam_weaponn("freecamweapon", "WEAPON_IN_FREECAM", "BACKEND_LOOPED_SELF_WEAPON_IN_FREECAM_DESC", g.self.free_cam.weapon);
}
