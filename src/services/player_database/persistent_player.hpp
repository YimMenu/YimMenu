#pragma once
#include "core/data/infractions.hpp"
#include <unordered_set>
#include "json_util.hpp"

namespace big
{
	struct persistent_player
	{
		std::string name;
		std::uint64_t rockstar_id = 0;
		bool block_join = false;
		int block_join_reason = 1;
		bool force_allow_join = 0;
		bool is_modder = false;
		bool is_rockstar_admin = false;
		std::unordered_set<int> infractions;
	};

	static void to_json(nlohmann::json& j, const persistent_player& player)
	{
		j = nlohmann::json{
			{ "name", player.name },
			{ "rockstar_id", player.rockstar_id },
			{ "block_join", player.block_join },
			{ "block_join_reason", player.block_join_reason },
			{ "force_allow_join", player.force_allow_join },
			{ "is_modder", player.is_modder },
			{ "is_rockstar_admin", player.is_rockstar_admin },
			{ "infractions", player.infractions },
		};
	};

	static void from_json(const nlohmann::json& j, persistent_player& player)
	{
		set_from_key_or_default(j, "name", player.name);
		set_from_key_or_default(j, "rockstar_id", player.rockstar_id);
		set_from_key_or_default(j, "block_join", player.block_join);
		set_from_key_or_default(j, "block_join_reason", player.block_join_reason);
		set_from_key_or_default(j, "force_allow_join", player.force_allow_join);
		set_from_key_or_default(j, "is_modder", player.is_modder);
		set_from_key_or_default(j, "is_rockstar_admin", player.is_rockstar_admin);
		set_from_key_or_default(j, "infractions", player.infractions);
	}
};
