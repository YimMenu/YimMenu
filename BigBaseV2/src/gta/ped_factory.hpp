#pragma once
#include "fwddec.hpp"

class CPedFactory
{
public:
	virtual ~CPedFactory() = default;
	CPed *m_local_ped;
};
