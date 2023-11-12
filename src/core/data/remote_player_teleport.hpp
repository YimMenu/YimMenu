#pragma once

namespace big
{
	struct remote_player_teleport
	{
		std::int16_t m_player_net_id;
		rage::fvector3 m_position;
	};

	inline std::unordered_map<uint16_t, remote_player_teleport> m_remote_player_teleports;
}