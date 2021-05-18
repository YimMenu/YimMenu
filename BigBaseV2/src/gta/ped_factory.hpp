#pragma once
#include "fwddec.hpp"

#pragma pack(push, 1)
class CPed
{
public:
	char m_padding[0x10B8];
	CPlayerInfo *m_playerinfo;
};
#pragma pack(pop)

class CPedFactory
{
public:
	virtual ~CPedFactory() = default;
	CPed *m_local_ped;
};
