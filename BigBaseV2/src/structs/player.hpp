#pragma once

namespace big
{
	struct player
	{
		Player id = -1;

		char name[64] = "";
		bool is_friend = false;
		bool is_online = false;

		bool operator < (const player& another) const
		{
			char temp[64], temp2[64];

			for (uint8_t i = 0; i < 64; i++)
			{
				temp[i] = tolower(this->name[i]);
				temp2[i] = tolower(another.name[i]);
			}

			return strcmp(temp, temp2) < 0;
		}
	};
}