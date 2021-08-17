#pragma once

#pragma pack(push, 1)

class CPlayerInfo
{
public:
	char pad_0000[40]; //0x0000
	uint64_t m_rockstar_id; //0x0028
	char pad_0030[8]; //0x0030
	uint32_t m_internal_ip; //0x0038
	uint16_t m_internal_port; //0x003C
	char pad_003E[2]; //0x003E
	uint32_t m_relay_ip; //0x0040
	uint16_t m_relay_port; //0x0044
	char pad_0046[2]; //0x0046
	uint32_t m_external_ip; //0x0048
	uint16_t m_external_port; //0x004C
	char pad_004E[66]; //0x004E
	uint64_t m_rockstar_id2; //0x0090
	char pad_0098[12]; //0x0098
	char m_name[20]; //0x00A4
	char pad_00B8[184]; //0x00B8
	float m_swim_speed; //0x0170
	char pad_0174[20]; //0x0174
	uint32_t m_water_proof; //0x0188
	char pad_018C[92]; //0x018C
	class CPed* m_ped; //0x01E8
	char pad_01F0[41]; //0x01F0
	uint32_t m_frame_flags; //0x0219
	char pad_021D[51]; //0x021D
	uint32_t m_player_controls; //0x0250
	char pad_0254[1256]; //0x0254
	float m_wanted_can_change; //0x073C
	char pad_0740[304]; //0x0740
	uint32_t m_npc_ignore; //0x0870
	char pad_0874[12]; //0x0874
	bool m_is_wanted; //0x0880
	char pad_0881[7]; //0x0881
	uint32_t m_wanted_level; //0x0888
	char pad_088C[1124]; //0x088C
	float m_run_speed; //0x0CF0
	float m_stamina; //0x0CF4
	float m_stamina_max; //0x0CF8
	char pad_0CFC[16]; //0x0CFC
	float m_weapon_damage_mult; //0x0D0C
	float m_weapon_defence_mult; //0x0D10
	char pad_0D14[4]; //0x0D14
	float m_melee_weapon_damage_mult; //0x0D18
	float m_melee_damage_mult; //0x0D1C
	float m_melee_defence_mult; //0x0D20
	char pad_0D24[8]; //0x0D24
	float m_melee_weapon_defence_mult; //0x0D2C
}; //Size: 0x0D30
static_assert(sizeof(CPlayerInfo) == 0xD30);

#pragma pack(pop)