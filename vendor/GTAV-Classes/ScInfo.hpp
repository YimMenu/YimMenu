#pragma once

#pragma pack(push, 1)
class ScInfo
{
public:
	char m_ticket[256]; //0x0000
	char pad_0100[256]; //0x0100
	char m_auth_token[128]; //0x0200
	uint32_t m_nonce; //0x0280
	char pad_0284[12]; //0x0284
	uint64_t m_peer_id; //0x0290
	char pad_0298[132]; //0x0298
	char m_country_code[3]; //0x031C
	char pad_031F[32]; //0x031F
	char m_email[78]; //0x033F
	char pad_038D[24]; //0x038D
	char m_language_code[8]; //0x03A5
	char pad_03AD[2]; //0x03AD
	char m_name[20]; //0x03AF
	char pad_03C3[2813]; //0x03C3
}; //Size: 0x0EC0
static_assert(sizeof(ScInfo) == 0xEC0);
#pragma pack(pop)
