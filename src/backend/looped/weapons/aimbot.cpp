#include "backend/int_command.hpp"
#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "util/misc.hpp"

#include <numbers>
namespace big
{
	bool_command g_aimbot_only_on_player("aimonlyatplayer", "PLAYER", "BACKEND_LOOPED_WEAPONS_AIM_ONLY_AT_PLAYER_DESC",
	    g.weapons.aimbot.only_on_player);

	bool_command g_aimbot_only_on_enemy("aimonlyatenemy", "BACKEND_LOOPED_WEAPONS_AIM_ONLY_AT_ENEMY", "BACKEND_LOOPED_WEAPONS_AIM_ONLY_AT_ENEMY_DESC",
	    g.weapons.aimbot.only_on_enemy);

	class aimbot : looped_command
	{
		using looped_command::looped_command;

		CPed* m_target{};

		static bool is_a_ped_type_we_dont_care_about(const Ped ped_handle)
		{
			const auto ped_type = PED::GET_PED_TYPE(ped_handle);

			auto config_value = (uint64_t*)&g.weapons.aimbot.only_on_ped_type;

			if (ped_type == ePedType::PED_TYPE_PLAYER_0 && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_PLAYER_0))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_PLAYER_1 && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_PLAYER_1))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_NETWORK_PLAYER && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_NETWORK_PLAYER))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_PLAYER_2 && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_PLAYER_2))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_CIVMALE && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_CIVMALE))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_CIVFEMALE && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_CIVFEMALE))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_COP && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_COP))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_ALBANIAN && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_ALBANIAN))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_BIKER_1 && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_BIKER_1))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_BIKER_2 && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_BIKER_2))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_ITALIAN && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_ITALIAN))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_RUSSIAN && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_RUSSIAN))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_RUSSIAN_2 && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_RUSSIAN_2))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_IRISH && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_IRISH))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_JAMAICAN && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_JAMAICAN))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_AFRICAN_AMERICAN && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_AFRICAN_AMERICAN))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_KOREAN && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_KOREAN))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_CHINESE_JAPANESE && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_CHINESE_JAPANESE))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_GANG_PUERTO_RICAN && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_GANG_PUERTO_RICAN))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_DEALER && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_DEALER))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_MEDIC && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_MEDIC))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_FIREMAN && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_FIREMAN))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_CRIMINAL && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_CRIMINAL))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_BUM && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_BUM))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_PROSTITUTE && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_PROSTITUTE))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_SPECIAL && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_SPECIAL))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_MISSION && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_MISSION))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_SWAT && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_SWAT))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_ANIMAL && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_ANIMAL))
			{
				return true;
			}
			if (ped_type == ePedType::PED_TYPE_ARMY && !misc::has_bits_set(config_value, (uint64_t)ePedTypeFlag::PED_TYPE_ARMY))
			{
				return true;
			}

			return false;
		}

		static rage::fvector3 get_camera_position()
		{
			uintptr_t cam_gameplay_director = *g_pointers->m_gta.m_cam_gameplay_director;
			uintptr_t cam_follow_ped_camera = *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x2'C8);
			return *reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x60);
		}

		static rage::fvector3 get_camera_aim_direction()
		{
			uintptr_t cam_gameplay_director = *g_pointers->m_gta.m_cam_gameplay_director;
			uintptr_t cam_follow_ped_camera = *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x2'C8);

			uintptr_t cam_follow_ped_camera_metadata = *reinterpret_cast<uintptr_t*>(cam_follow_ped_camera + 0x10);
			bool is_first_person = *reinterpret_cast<float*>(cam_follow_ped_camera_metadata + 0x30) == 0.0f;
			if (is_first_person)
			{
				return reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x40)->normalize();
			}
			else
			{
				return reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x3'D0)->normalize();
			}
		}

		static bool is_in_fov(const rage::fvector3& object_position)
		{
			const auto camera_position = get_camera_position();
			auto camera_aim_direction  = get_camera_aim_direction();

			const auto direction_to_object = object_position - camera_position;

			const float dot_product = camera_aim_direction.dot_product(direction_to_object);

			const float camera_aim_magnitude          = camera_aim_direction.magnitude();
			const float direction_to_object_magnitude = direction_to_object.magnitude();

			const float angle = std::acos(dot_product / (camera_aim_magnitude * direction_to_object_magnitude));

			return angle <= math::deg_to_rad(g.weapons.aimbot.fov);
		}

		void find_best_target(CPed* self_ped, const rage::fvector3& self_pos)
		{
			m_target = nullptr;

			float current_best_distance = g.weapons.aimbot.distance * g.weapons.aimbot.distance;

			for (rage::CEntity* ped_ : pools::get_all_peds())
			{
				CPed* ped = (CPed*)ped_;

				if (ped == self_ped)
				{
					continue;
				}

				const auto ped_handle = g_pointers->m_gta.m_ptr_to_handle(ped);

				if (ENTITY::IS_ENTITY_DEAD(ped_handle, 0))
				{
					continue;
				}

				const auto is_not_a_player_and_we_target_only_players = g_aimbot_only_on_player.is_enabled() && !ped->m_player_info;
				if (is_not_a_player_and_we_target_only_players)
				{
					continue;
				}

				const auto relation             = PED::GET_RELATIONSHIP_BETWEEN_PEDS(ped_handle, self::ped);
				constexpr auto dislike_relation = 4;
				constexpr auto hate_relation    = 5;
				const auto is_not_an_enemy_and_we_target_only_enemies = g_aimbot_only_on_enemy.is_enabled() && (relation != dislike_relation && relation != hate_relation);
				if (is_not_an_enemy_and_we_target_only_enemies)
				{
					continue;
				}

				if (is_a_ped_type_we_dont_care_about(ped_handle))
				{
					continue;
				}

				constexpr int trace_flags = eTraceFlags::IntersectWorld | eTraceFlags::IntersectVehicle | eTraceFlags::IntersectObject;
				if (!ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(g_pointers->m_gta.m_ptr_to_handle(self_ped), ped_handle, trace_flags))
				{
					continue;
				}

				const auto ped_position = *ped->get_position();

				if (!is_in_fov(ped_position))
				{
					continue;
				}

				float distance_to_ped = self_pos.distance(ped_position);
				if (current_best_distance > distance_to_ped)
				{
					current_best_distance = distance_to_ped;
					m_target              = ped;
				}
			}
		}

		// Not sure at this point what this even do
		static void reset_aim_vectors(uintptr_t camera)
		{
			uintptr_t camera_params = *(uintptr_t*)(camera + 0x10);
			{
				if (g_local_player->m_vehicle)
				{
					if (*(float*)(camera_params + 0x2'AC) == -2.0f)
					{
						*(float*)(camera_params + 0x2'AC) = 0.0f;
						*(float*)(camera_params + 0x2'C0) = 111.0f;
						*(float*)(camera_params + 0x2'C4) = 111.0f;
					}
				}
				else
				{
					if (*(float*)(camera_params + 0x1'30) == 8.0f)
					{
						*(float*)(camera_params + 0x1'30) = 111.0f; // def 8.0f
						*(float*)(camera_params + 0x1'34) = 111.0f; // def 10.0f
						*(float*)(camera_params + 0x4'CC) = 0.0f;   // def 4.0f

						if (*(float*)(camera_params + 0x4'9C) == 1.0f)
						{
							*(float*)(camera_params + 0x4'9C) = 0.0f; // def 1.0f
						}

						*(float*)(camera_params + 0x2'AC) = 0.0f; // def -3.0f
						*(float*)(camera_params + 0x2'B0) = 0.0f; // def -8.0f
					}
				}
			}
		}

		void compute_aim_direction_and_set_gameplay_cam(const rage::fvector3& target_bone_position)
		{
			uintptr_t cam_gameplay_director = *g_pointers->m_gta.m_cam_gameplay_director;


			uintptr_t cam_follow_ped_camera = *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x2'C8);

			const auto aim_direction = (target_bone_position - get_camera_position()).normalize();

			if (!g_local_player->m_vehicle)
			{
				reset_aim_vectors(cam_follow_ped_camera);

				uintptr_t cam_follow_ped_camera_metadata = *reinterpret_cast<uintptr_t*>(cam_follow_ped_camera + 0x10);
				bool is_first_person = *reinterpret_cast<float*>(cam_follow_ped_camera_metadata + 0x30) == 0.0f;
				if (is_first_person)
				{
					*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x40) = aim_direction;
				}
				else
				{
					*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x3'D0) = aim_direction;
				}
			}
			else
			{
				uintptr_t cam_follow_ped_camera2 = *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x2'C0);
				uintptr_t cam_follow_ped_camera3 = *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x3'C0);

				reset_aim_vectors(cam_follow_ped_camera);
				reset_aim_vectors(cam_follow_ped_camera2);
				reset_aim_vectors(cam_follow_ped_camera3);

				*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x40)   = aim_direction;
				*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x3'D0) = aim_direction;

				*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera2 + 0x40)   = aim_direction;
				*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera2 + 0x3'D0) = aim_direction;

				*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera3 + 0x40)   = aim_direction;
				*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera3 + 0x3'D0) = aim_direction;
			}
		}

		void adjust_position_for_target_velocity(rage::fvector3& target_position)
		{
			const auto delta_time = ImGui::GetIO().DeltaTime;

			rage::fvector3 velocity;
			if (m_target->m_vehicle)
			{
				const auto scr_velocity = ENTITY::GET_ENTITY_VELOCITY(g_pointers->m_gta.m_ptr_to_handle(m_target->m_vehicle));
				velocity = rage::fvector3(scr_velocity.x, scr_velocity.y, scr_velocity.z);
			}
			else
			{
				velocity = m_target->m_velocity;
			}

			target_position += velocity * delta_time * g.weapons.aimbot.adjust_position_scalar_for_velocity_value;

			// Unsure if that's even "physically" correct to do this? But it seems to works very well when we drive at high speed.
			if (g_local_player->m_vehicle)
			{
				const auto scr_velocity = ENTITY::GET_ENTITY_VELOCITY(g_pointers->m_gta.m_ptr_to_handle(g_local_player->m_vehicle));
				const auto my_velocity = rage::fvector3(scr_velocity.x, scr_velocity.y, scr_velocity.z);

				target_position -= my_velocity * delta_time * g.weapons.aimbot.adjust_position_scalar_for_velocity_value;
			}
		}

		virtual void on_tick() override
		{
			if (!PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				return;
			}

			CPed* self_ped = g_local_player;
			if (!self_ped)
			{
				return;
			}

			rage::fvector3 self_pos = *self_ped->get_position();

			find_best_target(self_ped, self_pos);

			if (!m_target)
			{
				return;
			}

			rage::fvector3 target_bone_position = m_target->get_bone_coords((ePedBoneType)g.weapons.aimbot.selected_bone);

			// Take into account the target velocity.
			adjust_position_for_target_velocity(target_bone_position);

			compute_aim_direction_and_set_gameplay_cam(target_bone_position);
		}
	};

	aimbot g_aimbot("aimbot", "VIEW_OVERLAY_AIMBOT", "BACKEND_LOOPED_WEAPONS_AIMBOT_DESC", g.weapons.aimbot.enable);


}
