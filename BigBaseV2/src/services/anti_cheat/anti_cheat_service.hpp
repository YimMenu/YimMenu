#pragma once
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "util/anti_cheat.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	struct modder_player {
		std::string player_name;
		uint64_t rid;
		int score;
		std::string detections;
	};
	using modders = std::vector<modder_player>;


	using anti_cheat_callback = std::function<const char* (const char*)>;
	class anti_cheat_service final
	{
		modders m_modders;

	public:
		anti_cheat_service();
		~anti_cheat_service();

		anti_cheat_service(const anti_cheat_service&) = delete;
		anti_cheat_service(anti_cheat_service&&) noexcept = delete;
		anti_cheat_service& operator=(const anti_cheat_service&) = delete;
		anti_cheat_service& operator=(anti_cheat_service&&) noexcept = delete;

		bool is_player_in_moddb(uint64_t rid);
		bool mark_as_modder(Player player, int score, std::string detection);
		bool add_score_to_modder(uint64_t rid, int score_to_add, std::string detection);
		int get_moddb_player_from_rid(uint64_t rid);
		int modder_check(Player player);

		modders& modders()
		{
			return m_modders;
		}
	};

	inline anti_cheat_service* g_anti_cheat_service;
}