#pragma once
#include "CPed.hpp"

class CPedFactory
{
public:
	char pad_0000[8]; //0x0000
	class CPed* m_local_ped; //0x0008
}; //Size: 0x0010
static_assert(sizeof(CPedFactory) == 0x10);
