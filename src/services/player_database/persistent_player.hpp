#pragma once
#include "core/data/infractions.hpp"
#include "json_util.hpp"

#include <unordered_set>

namespace big
{
	enum class PlayerOnlineStatus
	{
		UNKNOWN,
		OFFLINE,
		ONLINE
	};

	struct persistent_player
	{
		std::string name;
		std::uint64_t rockstar_id = 0;
		bool block_join           = false;
		int block_join_reason     = 1;
		bool is_modder            = false;
		std::unordered_set<int> infractions;
		std::optional<CommandAccessLevel> command_access_level = std::nullopt;
		PlayerOnlineStatus online_state                        = PlayerOnlineStatus::UNKNOWN;
	};

	static void to_json(nlohmann::json& j, const persistent_player& player)
	{
		j = nlohmann::json{{"name", player.name},
		    {"rockstar_id", player.rockstar_id},
		    {"block_join", player.block_join},
		    {"block_join_reason", player.block_join_reason},
		    {"is_modder", player.is_modder},
		    {"infractions", player.infractions}};

		if (player.command_access_level.has_value())
			j["command_access_level"] = player.command_access_level.value();
	};

	static void from_json(const nlohmann::json& j, persistent_player& player)
	{
		set_from_key_or_default(j, "name", player.name);
		set_from_key_or_default(j, "rockstar_id", player.rockstar_id);
		set_from_key_or_default(j, "block_join", player.block_join);
		set_from_key_or_default(j, "block_join_reason", player.block_join_reason);
		set_from_key_or_default(j, "is_modder", player.is_modder);
		set_from_key_or_default(j, "infractions", player.infractions);

		if (j.contains("command_access_level") && j["command_access_level"].is_string())
			player.command_access_level = j["command_access_level"].get<CommandAccessLevel>();
	}
};
