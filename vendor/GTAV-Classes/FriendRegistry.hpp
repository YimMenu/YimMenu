#pragma once
#include "FriendInfo.hpp"

class FriendList
{
public:
	class FriendInfo m_data[250]; //0x0000
}; //Size: 0x1F400
static_assert(sizeof(FriendList) == 0x1F400);

#pragma pack(push, 4)
class FriendRegistry
{
public:
	uint32_t m_friend_count; //0x0000
	char pad_0004[8]; //0x0004
	class FriendList *m_friends_list; //0x000C
}; //Size: 0x0014
static_assert(sizeof(FriendRegistry) == 0x14);
#pragma pack(pop)
