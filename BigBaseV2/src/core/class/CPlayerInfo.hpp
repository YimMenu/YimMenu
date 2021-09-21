#pragma once

#pragma warning(push)
#pragma warning(disable : 4201) // nonstandard extension used: nameless struct/union
union netAddress
{
	std::uint32_t m_raw;
	struct
	{
		std::uint8_t m_field4;
		std::uint8_t m_field3;
		std::uint8_t m_field2;
		std::uint8_t m_field1;
	};
};
#pragma warning(pop)
#pragma pack(push, 1)

class CPlayerInfo
{
public:
	char pad_0000[32]; //0x0000
	netAddress m_internal_ip; //0x0020
	uint16_t m_internal_port; //0x0024
	char pad_0026[2]; //0x0026
	uint64_t m_rockstar_id; //0x0028
	char pad_0030[60]; //0x0030
	netAddress m_external_ip; //0x006C
	uint16_t m_external_port; //0x0070
	char pad_0072[30]; //0x0072
	uint64_t m_rockstar_id2; //0x0090
	char pad_0098[12]; //0x0098
	char m_name[20]; //0x00A4
	char pad_00B8[184]; //0x00B8
	float m_swim_speed; //0x0170
	char pad_0174[20]; //0x0174
	uint32_t m_water_proof; //0x0188
	char pad_018C[92]; //0x018C
	class CPed* m_ped; //0x01E8
	char pad_01F0[40]; //0x01F0
	uint32_t m_frame_flags; //0x0218
	char pad_021C[52]; //0x021C
	uint32_t m_player_controls; //0x0250
	char pad_0254[1256]; //0x0254
	float m_wanted_can_change; //0x073C
	char pad_0740[304]; //0x0740
	uint32_t m_npc_ignore; //0x0870
	char pad_0874[12]; //0x0874
	bool m_is_wanted; //0x0880
	char pad_0881[7]; //0x0881
	uint32_t m_wanted_level; //0x0888
	uint32_t m_wanted_level_display; //0x088C
	char pad_0890[1120]; //0x0890
	float m_run_speed; //0x0CF0
	float m_stamina; //0x0CF4
	float m_stamina_regen; //0x0CF8
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