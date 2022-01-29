#pragma once
#include "CNetGamePlayer.hpp"

#ifndef PLAYER_STRUCT
#define PLAYER_STRUCT

namespace big
{
	struct CPlayer
	{
		int32_t id;
		char name[20];

		bool is_friend = false;
		bool is_online = false;

		CNetGamePlayer* net_player;

		bool operator < (const CPlayer& another) const
		{
			char temp[20], temp2[20];

			for (uint8_t i = 0; i < 20; i++)
			{
				temp[i] = tolower(this->name[i]);
				temp2[i] = tolower(another.name[i]);
			}

			return strcmp(temp, temp2) < 0;
		}
	};
}

#endif