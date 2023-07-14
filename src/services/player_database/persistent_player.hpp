#pragma once
#include "core/data/infractions.hpp"
#include "json_util.hpp"

#include <unordered_set>

namespace nlohmann
{
	template<typename T>
	struct adl_serializer<std::optional<T>>
	{
		static void to_json(json& j, const std::optional<big::CommandAccessLevel>& opt)
		{
			if (opt == std::nullopt)
			{
				j = nullptr;
			}
			else
			{
				j = *opt;
			}
		}

		static void from_json(const json& j, std::optional<big::CommandAccessLevel>& opt)
		{
			if (j.is_null())
			{
				opt = std::nullopt;
			}
			else
			{
				opt = j.get<big::CommandAccessLevel>();
			}
		}
	};
}

enum class GSType : int32_t;

namespace big
{
	struct persistent_player
	{
		std::string name;
		std::uint64_t rockstar_id = 0;
		bool block_join           = false;
		int block_join_reason     = 1;
		bool is_modder            = false;
		bool notify_online        = false;
		std::unordered_set<int> infractions;
		std::string notes                                      = "";
		std::optional<CommandAccessLevel> command_access_level = std::nullopt;
		GSType session_type                                    = GSType(-2);
		int64_t session_id                                     = -1;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(persistent_player, name, rockstar_id, block_join, block_join_reason, is_modder, notify_online, infractions, notes, command_access_level)
	};

};
