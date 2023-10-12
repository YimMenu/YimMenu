#pragma once

#include <rage/vector.hpp>

namespace big
{
	struct remote_player_teleport
	{
		std::int16_t m_player_net_id;
		rage::fvector3 m_position;
	};
}