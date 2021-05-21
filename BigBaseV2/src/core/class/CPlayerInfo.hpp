#pragma once

#pragma pack(push, 4)
class CPlayerInfo
{
public:
	char pad_0000[52]; //0x0000
	uint32_t m_internal_ip; //0x0034
	uint16_t m_internal_port; //0x0038
	char pad_003A[2]; //0x003A
	uint32_t m_relay_ip; //0x003C
	uint16_t m_relay_port; //0x0040
	char pad_0042[2]; //0x0042
	uint32_t m_external_ip; //0x0044
	uint16_t m_external_port; //0x0048
	char pad_004A[38]; //0x004A
	uint64_t m_rockstar_id; //0x0070
	char pad_0078[12]; //0x0078
	char m_name[20]; //0x0084
	char pad_0098[180]; //0x0098
	float m_swim_speed; //0x014C
	float m_run_speed; //0x0150
	char pad_0154[81]; //0x0154
	bool m_is_rockstar_dev; //0x01A5
	char pad_01A6[1]; //0x01A6
	bool m_is_cheater; //0x01A7
	char pad_01A8[11]; //0x01A8
	bool m_is_online; //0x01B3
	char pad_01B4[20]; //0x01B4
	class CPed* m_ped; //0x01C8
	char pad_01D0[40]; //0x01D0
	uint32_t m_frame_flags; //0x01F8
	char pad_01FC[28]; //0x01FC
	uint32_t m_player_controls; //0x0218
	char pad_021C[1588]; //0x021C
	uint32_t m_npc_ignore; //0x0850
	char pad_0854[12]; //0x0854
	bool m_is_wanted; //0x0860
	char pad_0861[3]; //0x0861
	int8_t m_wanted_level_display; //0x0864
	char pad_0865[3]; //0x0865
	int8_t m_wanted_level; //0x0868
	char pad_0869[1131]; //0x0869
	float m_stamina; //0x0CD4
	float m_max_stamina; //0x0CD8
}; //Size: 0x0CDC
static_assert(sizeof(CPlayerInfo) == 0xCDC);

#pragma pack(pop)