#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "services/orbital_drone/orbital_drone.hpp"
#include "util/entity.hpp"

namespace big
{
	static constexpr ControllerInputs controls[] = {ControllerInputs::INPUT_SPRINT, ControllerInputs::INPUT_MOVE_UP_ONLY, ControllerInputs::INPUT_MOVE_DOWN_ONLY, ControllerInputs::INPUT_MOVE_LEFT_ONLY, ControllerInputs::INPUT_MOVE_RIGHT_ONLY, ControllerInputs::INPUT_DUCK};

	static constexpr float speed = 1.0f;

	class noclip : looped_command
	{
		using looped_command::looped_command;

		Entity m_entity;
		float m_speed_multiplier;

		inline bool can_update_location()
		{
			return !(g.cmd_executor.enabled || g.self.free_cam);
		}

		virtual void on_tick() override
		{
			if (g_orbital_drone_service.initialized())
				return;

			for (const auto& control : controls)
				PAD::DISABLE_CONTROL_ACTION(0, static_cast<int>(control), true);

			const auto location = self::pos;
			const Entity ent = (self::veh != 0 && g_local_player->m_ped_task_flag & (int)ePedTask::TASK_DRIVING) ? self::veh : self::ped;

			// cleanup when changing entities
			if (m_entity != ent)
			{
				ENTITY::FREEZE_ENTITY_POSITION(m_entity, false);
				ENTITY::SET_ENTITY_COLLISION(m_entity, true, false);

				m_entity = ent;
			}

			Vector3 vel{};

			if (can_update_location())
			{
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
			}

			auto rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
			ENTITY::SET_ENTITY_ROTATION(ent, 0.f, rot.y, rot.z, 2, 0);
			ENTITY::SET_ENTITY_COLLISION(ent, false, false);
			if (vel.x == 0.f && vel.y == 0.f && vel.z == 0.f)
			{
				// freeze entity to prevent drifting when standing still
				ENTITY::FREEZE_ENTITY_POSITION(ent, true);
				m_speed_multiplier = 0.f;
			}
			else
			{
				if (m_speed_multiplier < 20.f)
					m_speed_multiplier += 0.15f;

				ENTITY::FREEZE_ENTITY_POSITION(ent, false);

				const auto is_aiming = PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM);
				if (is_aiming || CAM::GET_FOLLOW_PED_CAM_VIEW_MODE() == CameraMode::FIRST_PERSON)
				{
					vel = vel * g.self.noclip_aim_speed_multiplier;

					const auto offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, vel.x * m_speed_multiplier, vel.y * m_speed_multiplier, vel.z * m_speed_multiplier);

					ENTITY::SET_ENTITY_VELOCITY(ent, 0, 0, 0);
					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, offset.x, offset.y, offset.z, true, true, true);
				}
				else
				{
					vel = vel * g.self.noclip_speed_multiplier;

					const auto offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, vel.x, vel.y, 0.f);
					vel.x             = offset.x - location.x;
					vel.y             = offset.y - location.y;

					ENTITY::SET_ENTITY_MAX_SPEED(ent, 999999999999);
					ENTITY::SET_ENTITY_VELOCITY(ent, vel.x * m_speed_multiplier, vel.y * m_speed_multiplier, vel.z * m_speed_multiplier);
				}
			}
		}

		virtual void on_disable() override
		{
			if (entity::take_control_of(m_entity))
			{
				ENTITY::FREEZE_ENTITY_POSITION(m_entity, false);
				ENTITY::SET_ENTITY_COLLISION(m_entity, true, false);
			}
		}
	};

	noclip g_noclip("noclip", "NO_CLIP", "NO_CLIP_DESC", g.self.noclip);
}
