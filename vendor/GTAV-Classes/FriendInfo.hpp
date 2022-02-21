#pragma once

#pragma pack(push, 1)
class FriendInfo
{
public:
	char pad_0000[128]; //0x0000
	char m_name[20]; //0x0080
	char pad_0094[36]; //0x0094
	uint64_t m_rockstar_id; //0x00B8
	uint8_t unk_0xC0; //0x00C0
	char pad_00C1[3]; //0x00C1
	uint32_t m_friend_state; //0x00C4
	char pad_00C8[304]; //0x00C8
	uint32_t m_is_joinable; //0x01F8
	char pad_01FC[4]; //0x01FC
}; //Size: 0x0200
static_assert(sizeof(FriendInfo) == 0x200);
#pragma pack(pop)
