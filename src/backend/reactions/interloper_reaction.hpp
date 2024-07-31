#pragma once
#include "reaction.hpp"

namespace big
{
	class interloper_reaction : public reaction
	{
	public:
		interloper_reaction(const char* event_name, const char* notify_message, const char* announce_message, bool blockable, bool karmaable);

		bool block = true;
		bool karma = false;

		bool m_blockable;
		bool m_karmaable;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(interloper_reaction, announce_in_chat, is_team_only, notify, log, add_to_player_db, block_joins, block_join_reason, kick, block, karma, timeout) // json doesn't serialize parent fields automatically

		virtual void process(player_ptr attacker, player_ptr victim);
	};
}