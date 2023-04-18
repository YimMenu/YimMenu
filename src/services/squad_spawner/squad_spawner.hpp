#pragma once

#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{

	struct squad_member
	{
		Ped handle;
		CPed* ptr;

		Vector3 get_pos()
		{
			rage::fvector3* pos{};
			if (ptr && ptr->m_navigation && ptr->m_navigation->get_position())
				pos = ptr->m_navigation->get_position();
			else
				return {};
			return {pos->x, pos->y, pos->z};
		}

		bool is_ped_alive()
		{
			if (ptr)
			{
				return ptr->m_health > 0;
			}
			return false;
		}
	};

	enum class eSquadSpawnDistance : int
	{
		CUSTOM,
		ON_TARGET,
		CLOSEBY,
		MODERATELY_DISTANCED,
		FAR_AWAY
	};

	/*
    This struct is ambiguous in its employment, hence the division of its content.
    It serves as a template for the UI and an active object to track and modify dynamically.
    The constuctor is only meant to initialize its static variables and increment the Id.
    */
	struct squad
	{
		int m_internal_id;
		//Static variables
		char m_name[32];
		char m_description[500];
		char m_ped_model[32];
		char m_weapon_model[32];
		char m_vehicle_model[32];
		bool m_ped_invincibility;
		bool m_veh_invincibility;
		bool m_ped_proofs[5]; // 0 headshot, 1 bullet, 2 flame, 3 melee, 4 explosion
		float m_ped_health;   //Leave at 0 to default
		float m_ped_armor;    //Leave at 0 to default
		float m_ped_accuracy;
		float m_spawn_distance;
		int m_squad_size;
		eSquadSpawnDistance m_spawn_distance_mode;
		eCombatAbilityLevel m_combat_ability_level;
		bool m_stay_in_veh;
		bool m_spawn_behind_same_velocity; //Spawns behind a moving target with the same velocity as the targets vehicle
		bool m_disperse; //Spawns attackers that are on foot on seperate positions
		/*
		Leave vehicle_model empty to spawn a squad on foot
		Ped proofs array is indexed as follows; 0 headshot, 1 bullet, 2 flame, 3 melee, 4 explosion
		Leave health and armor at 0 to default
		Leave spawn_distance at 0 to let the spawn_distance_mode to handle it
		*/
		squad(){};
		squad(const char* name, const char* ped_model, const char* weapon_model, const char* vehicle_model, int squad_size, bool ped_invincibility = false, bool veh_invincibility = false, bool ped_proofs[5] = {}, float ped_health = 0, float ped_armor = 0, float spawn_distance = 0, float ped_accuracy = 50.f, eSquadSpawnDistance spawn_distance_mode = eSquadSpawnDistance::CLOSEBY, eCombatAbilityLevel combat_ability_level = eCombatAbilityLevel::AVERAGE, bool stay_in_veh = false, bool spawn_behind_same_velocity = false, const char* description = "", bool disperse = false)
		{
			m_internal_id = ++m_instance_count;

			strcpy(m_name, name);
			strcpy(m_description, description);
			strcpy(m_ped_model, ped_model);
			strcpy(m_weapon_model, weapon_model);
			strcpy(m_vehicle_model, vehicle_model);
			m_squad_size = squad_size;

			m_ped_invincibility = ped_invincibility;
			m_veh_invincibility = veh_invincibility;

			for (int i = 0; i < 5; i++)
				m_ped_proofs[i] = ped_proofs[i];

			m_ped_health                 = ped_health;
			m_ped_armor                  = ped_armor;
			m_spawn_distance             = spawn_distance;
			m_ped_accuracy               = ped_accuracy;
			m_spawn_distance_mode        = spawn_distance_mode;
			m_combat_ability_level       = combat_ability_level;
			m_stay_in_veh                = stay_in_veh;
			m_spawn_behind_same_velocity = spawn_behind_same_velocity;
			m_disperse                   = disperse;
		}

		int get_id() const
		{
			return m_internal_id;
		}

		bool does_squad_have_description()
		{
			return !std::string(m_description).empty();
		}

		bool does_squad_have_vehicle()
		{
			return !std::string(m_vehicle_model).empty();
		}

		bool should_override_health()
		{
			if (m_ped_health > 0)
				return true;
			return false;
		}

		bool should_override_armor()
		{
			if (m_ped_armor > 0)
				return true;
			return false;
		}

		bool should_override_spawn_distance()
		{
			if (m_spawn_distance > 0)
				return true;
			return false;
		}

		bool has_squad_spawned()
		{
			return m_members.size() > 0;
		}

		bool is_squad_alive()
		{
			bool alive = false;
			for (auto& p : m_members)
				if (!ENTITY::IS_ENTITY_DEAD(p.handle, false))
					alive = true;
			return alive;
		}

		squad_member get_a_member_thats_alive()
		{
			for (auto& p : m_members)
				if (!ENTITY::IS_ENTITY_DEAD(p.handle, false))
					return p;
			return {};
		}

		//Dynamic variables
		std::vector<squad_member> m_members{};
		player_ptr target;
		Ped current_target_ped;
		Vehicle m_veh_handle;
		CVehicle* m_veh_ptr;
		Vector3 m_spawn_pos;
		float m_spawn_heading;

		Vector3 get_veh_pos()
		{
			rage::fvector3* pos{};
			if (m_veh_ptr && m_veh_ptr->m_navigation && m_veh_ptr->m_navigation->get_position())
				pos = m_veh_ptr->m_navigation->get_position();
			else
				return {};
			return {pos->x, pos->y, pos->z};
		}

	private:
		inline static int m_instance_count;
	};

	class squad_spawner
	{
	public:
		std::vector<squad> m_templates;
		std::vector<squad> m_active_squads;

		squad_spawner()
		{
			load_default_templates();
		}

	private:
		bool find_suitable_spawn_pos(squad&);
		squad_member spawn_squad_member(squad);
		std::pair<Vehicle, CVehicle*> spawn_squad_vehicle(squad);


	public:
		void load_default_templates();
		std::filesystem::path get_file_path();
		bool spawn_squad(squad, player_ptr target_player, bool override_spawn_pos, Vector3 custom_pos);
		nlohmann::json to_json(squad s);
		squad from_json(nlohmann::json j);
		bool save_squad(squad);
		bool delete_squad(squad);
		bool fetch_squads();

		void tick();


		void terminate_squads();
		void update_squad_target(squad& s, Ped target_ped);
	};

	inline squad_spawner g_squad_spawner_service;
}