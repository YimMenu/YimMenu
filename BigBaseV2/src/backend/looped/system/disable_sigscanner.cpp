#include "backend/looped/looped.hpp"
#include "pointers.hpp"

namespace big
{
	// credits: @brunph
	void looped::system_disable_sigscanner()
	{
		if (g_pointers->m_tunables->isValid())
		{
			if (const auto ptr = g_pointers->m_tunables->getInstance(); ptr)
			{
				// sets the signature counter to 0
				// preventing the array from being looped
				// this is just an alternative protection
				// to the one found in pointers.cpp
				ptr->m_bCount = 0;
			}
		}
	}
}
