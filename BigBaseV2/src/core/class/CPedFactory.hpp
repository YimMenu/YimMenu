#pragma once
#include "CPed.hpp"

#pragma pack(push, 1)
// Created with ReClass.NET 1.2 by KN4CK3R

class CPedFactory
{
public:
	char pad_0000[8]; //0x0000
	class CPed* m_local_ped; //0x0008
}; //Size: 0x0010
static_assert(sizeof(CPedFactory) == 0x10);

#pragma pack(pop)