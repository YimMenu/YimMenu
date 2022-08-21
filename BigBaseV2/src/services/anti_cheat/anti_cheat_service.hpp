#pragma once
#include "natives.hpp"
#include "gta/joaat.hpp"
#include "util/anti_cheat.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	struct modder_player {
		const char* player_name;
		uint64_t rid;
		int score;
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
		bool mark_as_modder(Player player, int score);
		int modder_check(Player player);
	};

	inline anti_cheat_service* g_anti_cheat_service;
}