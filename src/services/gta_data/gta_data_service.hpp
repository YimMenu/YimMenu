#pragma once
#include "cache_file.hpp"
#include "ped_item.hpp"
#include "vehicle_item.hpp"
#include "weapon_item.hpp"

namespace big
{
	enum class eGtaDataUpdateState
	{
		IDLE,
		NEEDS_UPDATE,
		WAITING_FOR_SINGLE_PLAYER,
		WAITING_FOR_ONLINE,
		UPDATING
	};

	using ped_map     = std::map<std::string, ped_item>;
	using vehicle_map = std::map<std::string, vehicle_item>;
	using weapon_map  = std::map<std::string, weapon_item>;
	using string_vec  = std::vector<std::string>;

	class gta_data_service final
	{
	public:
		gta_data_service();
		~gta_data_service();

		bool cache_needs_update() const;
		eGtaDataUpdateState state() const;
		void update_in_online();
		void update_now();

		const ped_item& ped_by_hash(std::uint32_t hash);
		const vehicle_item& vehicle_by_hash(std::uint32_t hash);
		const weapon_item& weapon_by_hash(std::uint32_t hash);

		string_vec& ped_types();
		string_vec& vehicle_classes();
		string_vec& weapon_types();

		ped_map& peds()
		{
			return m_peds;
		}
		vehicle_map& vehicles()
		{
			return m_vehicles;
		}
		weapon_map& weapons()
		{
			return m_weapons;
		}

	private:
		bool is_cache_up_to_date();

		void load_data();
		void load_peds();
		void load_vehicles();
		void load_weapons();

		void rebuild_cache();

	private:
		cache_file m_peds_cache;
		cache_file m_vehicles_cache;
		cache_file m_weapons_cache;

		// std::map is free sorting algo
		ped_map m_peds;
		vehicle_map m_vehicles;
		weapon_map m_weapons;

		string_vec m_ped_types;
		string_vec m_vehicle_classes;
		string_vec m_weapon_types;

		eGtaDataUpdateState m_update_state;

	private:
		static constexpr ped_item empty_ped{};
		static constexpr vehicle_item empty_vehicle{};
		static constexpr weapon_item empty_weapon{};
	};

	inline gta_data_service* g_gta_data_service{};
}
