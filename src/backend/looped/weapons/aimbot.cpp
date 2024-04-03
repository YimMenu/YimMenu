#include "backend/int_command.hpp"
#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "hooking/hooking.hpp"
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

	public:
		static inline CPed* m_target{};

		static inline bool should_aimbot = false;

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

		static uintptr_t get_cam_follow_ped_camera()
		{
			uintptr_t cam_gameplay_director = *g_pointers->m_gta.m_cam_gameplay_director;
			return *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x3C0);
		}

		static rage::fvector3 get_camera_position()
		{
			return *reinterpret_cast<rage::fvector3*>(get_cam_follow_ped_camera() + 0x60);
		}

		static rage::fvector3 get_camera_aim_direction()
		{
			uintptr_t cam_gameplay_director = *g_pointers->m_gta.m_cam_gameplay_director;
			uintptr_t cam_follow_ped_camera = get_cam_follow_ped_camera();

			uintptr_t cam_follow_ped_camera_metadata = *reinterpret_cast<uintptr_t*>(cam_follow_ped_camera + 0x10);
			bool is_first_person = *reinterpret_cast<float*>(cam_follow_ped_camera_metadata + 0x30) == 0.0f;
			if (is_first_person)
			{
				return reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x40)->normalize();
			}
			else
			{
				return reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x3D0)->normalize();
			}
		}

		static float get_fov(const rage::fvector3& object_position)
		{
			const auto camera_position = get_camera_position();
			auto camera_aim_direction  = get_camera_aim_direction();

			const auto direction_to_object = object_position - camera_position;

			const float angle =
			    std::atan2(camera_aim_direction.cross_product(direction_to_object).magnitude(), camera_aim_direction.dot_product(direction_to_object));

			return angle;
		}

		static void find_best_target(CPed* self_ped, const rage::fvector3& self_pos)
		{
			m_target = nullptr;

			float best_fov      = math::deg_to_rad(g.weapons.aimbot.fov);
			float best_distance = g.weapons.aimbot.distance;

			for (rage::CEntity* ped_ : pools::get_all_peds())
			{
				CPed* ped = (CPed*)ped_;

				if (ped == self_ped)
				{
					continue;
				}

				if (ped->m_health <= 0)
				{
					continue;
				}

				const auto is_not_a_player_and_we_target_only_players = g_aimbot_only_on_player.is_enabled() && !ped->m_player_info;
				if (is_not_a_player_and_we_target_only_players)
				{
					continue;
				}

				const auto ped_handle = g_pointers->m_gta.m_ptr_to_handle(ped);

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

				constexpr int trace_flags = eTraceFlags::IntersectWorld | eTraceFlags::IntersectObject;
				if (!ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(self::ped, ped_handle, trace_flags))
				{
					continue;
				}

				const auto head_position = ped->get_bone_coords((ePedBoneType)g.weapons.aimbot.selected_bone);

				const auto fov = get_fov(head_position);

				const auto distance_to_ped = self_pos.distance(head_position);
				if (fov < best_fov && distance_to_ped < best_distance)
				{
					best_fov      = fov;
					best_distance = distance_to_ped;
					m_target      = ped;
				}
			}
		}

		// Make aimbot works when driving a vehicle.
		static void reset_aim_vectors(uintptr_t camera)
		{
			uintptr_t camera_params = *(uintptr_t*)(camera + 0x10);
			{
				if (g_local_player->m_vehicle)
				{
					if (*(float*)(camera_params + 0x2AC) == -2.0f)
					{
						*(float*)(camera_params + 0x2AC) = 0.0f;
						*(float*)(camera_params + 0x2C0) = 111.0f;
						*(float*)(camera_params + 0x2C4) = 111.0f;
					}
				}
				else
				{
					if (*(float*)(camera_params + 0x130) == 8.0f)
					{
						*(float*)(camera_params + 0x130) = 111.0f; // def 8.0f
						*(float*)(camera_params + 0x134) = 111.0f; // def 10.0f
						*(float*)(camera_params + 0x4CC) = 0.0f;   // def 4.0f

						if (*(float*)(camera_params + 0x49C) == 1.0f)
						{
							*(float*)(camera_params + 0x49C) = 0.0f; // def 1.0f
						}

						*(float*)(camera_params + 0x2AC) = 0.0f; // def -3.0f
						*(float*)(camera_params + 0x2B0) = 0.0f; // def -8.0f
					}
				}
			}
		}

		static void compute_aim_direction_and_set_gameplay_cam(const rage::fvector3& target_bone_position)
		{
			uintptr_t cam_follow_ped_camera = get_cam_follow_ped_camera();

			const auto aim_direction = (target_bone_position - get_camera_position()).normalize();

			reset_aim_vectors(cam_follow_ped_camera);

			*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x40)  = aim_direction;
			*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x3D0) = aim_direction;
		}

		static inline CPed* last_target_pos_target{};
		static inline rage::fvector3 last_target_pos{};

		static inline rage::fvector3 last_my_pos{};

		static rage::fvector3 get_velocity(CPed* ped)
		{
			if (ped == g_local_player)
			{
				const auto velocity = *ped->get_position() - last_my_pos;
				last_my_pos         = *ped->get_position();

				return velocity;
			}

			if (ped == last_target_pos_target)
			{
				const auto velocity = *ped->get_position() - last_target_pos;
				last_target_pos     = *ped->get_position();

				return velocity;
			}
			else
			{
				last_target_pos_target = ped;
				last_target_pos        = *ped->get_position();

				return {};
			}
		}

		static void adjust_position_for_target_velocity(rage::fvector3& target_position)
		{
			const auto target_velocity = get_velocity(m_target);
			const auto my_velocity     = get_velocity(g_local_player);

			target_position += (target_velocity - my_velocity);
		}

		virtual void on_tick() override
		{
			should_aimbot = PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM);

			if (!should_aimbot)
			{
				return;
			}

			CAM::STOP_SCRIPT_GLOBAL_SHAKING(true);
			CAM::SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(0);
		}
	};

	aimbot g_aimbot("aimbot", "VIEW_OVERLAY_AIMBOT", "BACKEND_LOOPED_WEAPONS_AIMBOT_DESC", g.weapons.aimbot.enable);

	bool hooks::aimbot_cam_gameplay_director_update(uintptr_t this_)
	{
		const auto res = big::hooking::get_original<hooks::aimbot_cam_gameplay_director_update>()(this_);

		CPed* self_ped;
		rage::fvector3 self_pos;

		rage::fvector3 target_bone_position;

		if (!aimbot::should_aimbot)
		{
			goto exit;
		}

		self_ped = g_local_player;
		if (!self_ped)
		{
			goto exit;
		}

		self_pos = *self_ped->get_position();

		aimbot::find_best_target(self_ped, self_pos);
		if (!aimbot::m_target)
		{
			goto exit;
		}

		target_bone_position = aimbot::m_target->get_bone_coords((ePedBoneType)g.weapons.aimbot.selected_bone);

		// Take into account the target velocity.
		aimbot::adjust_position_for_target_velocity(target_bone_position);

		aimbot::compute_aim_direction_and_set_gameplay_cam(target_bone_position);

	exit:
		return res;
	}
}
