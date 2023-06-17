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
		int task_sequence_progress = -1;
		int task_sequence          = 0;

		~squad_member()
		{
			TASK::CLEAR_SEQUENCE_TASK(&task_sequence);
		}

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
			return ENTITY::DOES_ENTITY_EXIST(handle) && !ENTITY::IS_ENTITY_DEAD(handle, false);
		}
	};

	enum class eSquadSpawnDistance
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
		//Static variables
		std::string m_name;
		std::string m_description;
		std::string m_ped_model;
		std::string m_weapon_model;
		std::string m_vehicle_model;
		std::string m_persistent_vehicle = "None"; //The connection to persistent vehicle is done by the file name
		bool m_ped_invincibility;
		bool m_veh_invincibility;
		bool m_ped_proofs[5]; // 0 headshot, 1 bullet, 2 flame, 3 melee, 4 explosion
		float m_ped_health;   //Leave at 0 to default
		float m_ped_armor;    //Leave at 0 to default
		float m_ped_accuracy = 50.f;
		float m_spawn_distance;
		int m_squad_size = 1;
		eSquadSpawnDistance m_spawn_distance_mode  = eSquadSpawnDistance::CLOSEBY;
		eCombatAbilityLevel m_combat_ability_level = eCombatAbilityLevel::AVERAGE;
		bool m_stay_in_veh;
		bool m_spawn_behind_same_velocity; //Spawns behind a moving target with the same velocity as the targets vehicle
		bool m_disperse;                   //Spawns attackers that are on foot on seperate positions
		bool m_spawn_ahead;
		bool m_favour_roads;
		bool m_max_vehicle;

		/*
		Leave vehicle_model empty to spawn a squad on foot
		Ped proofs array is indexed as follows; 0 headshot, 1 bullet, 2 flame, 3 melee, 4 explosion
		Leave health and armor at 0 to default
		Leave spawn_distance at 0 to let the spawn_distance_mode to handle it
		*/
		squad(){};
		squad(std::string name, std::string ped_model, std::string weapon_model, std::string vehicle_model, int squad_size, bool ped_invincibility = false, bool veh_invincibility = false, bool ped_proofs[5] = {}, float ped_health = 0, float ped_armor = 0, float spawn_distance = 0, float ped_accuracy = 50.f, eSquadSpawnDistance spawn_distance_mode = eSquadSpawnDistance::CLOSEBY, eCombatAbilityLevel combat_ability_level = eCombatAbilityLevel::AVERAGE, bool stay_in_veh = false, bool spawn_behind_same_velocity = false, std::string description = "", bool disperse = false, bool spawn_ahead = false, bool favour_roads = false, bool max_vehicle = false, std::string persistent_vehicle = "None")
		{
			m_internal_id = ++m_instance_count;

			m_name               = name;
			m_description        = description;
			m_ped_model          = ped_model;
			m_weapon_model       = weapon_model;
			m_vehicle_model      = vehicle_model;
			m_persistent_vehicle = persistent_vehicle;
			m_squad_size         = squad_size;

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
			m_spawn_ahead                = spawn_ahead;
			m_favour_roads               = favour_roads;
			m_max_vehicle                = max_vehicle;
		}

		int get_id() const
		{
			return m_internal_id;
		}

		bool does_squad_have_description()
		{
			return !m_description.empty();
		}

		bool does_squad_have_vehicle()
		{
			return !m_vehicle_model.empty() || does_squad_have_persistent_vehicle();
		}

		bool does_squad_have_persistent_vehicle()
		{
			return m_persistent_vehicle != "None";
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
			for (auto& p : m_members)
				if (p.is_ped_alive())
					return true;
			return false;
		}

		squad_member get_a_member_thats_alive()
		{
			for (auto& p : m_members)
				if (p.is_ped_alive())
					return p;
			return {};
		}

		//Dynamic variables
		std::vector<squad_member> m_members{};
		player_ptr target      = nullptr;
		Ped current_target_ped = 0;
		Vehicle m_veh_handle   = 0;
		CVehicle* m_veh_ptr    = nullptr;
		Vector3 m_spawn_pos{};
		float m_spawn_heading = 0;

		int m_internal_id = 0;

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

	NLOHMANN_JSON_SERIALIZE_ENUM(eSquadSpawnDistance, {{eSquadSpawnDistance::CUSTOM, "custom"}, {eSquadSpawnDistance::ON_TARGET, "on target"}, {eSquadSpawnDistance::CLOSEBY, "closeby"}, {eSquadSpawnDistance::MODERATELY_DISTANCED, "moderately distanced"}, {eSquadSpawnDistance::FAR_AWAY, "far away"}})

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(squad, m_name, m_description, m_ped_model, m_weapon_model, m_vehicle_model, m_ped_invincibility, m_veh_invincibility, m_ped_proofs, m_ped_health, m_ped_armor, m_ped_accuracy, m_spawn_distance, m_squad_size, m_spawn_distance_mode, m_combat_ability_level, m_stay_in_veh, m_spawn_behind_same_velocity, m_disperse, m_spawn_ahead, m_favour_roads, m_max_vehicle, m_persistent_vehicle);

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
		bool save_squad(squad);
		bool delete_squad(squad);
		bool fetch_squads();
		void tick();

		void terminate_squads();
		void terminate_squad(squad*);
		void build_and_perform_sequence(squad&, int member);
	};

	inline squad_spawner g_squad_spawner_service;
}