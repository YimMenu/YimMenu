#include "pointers.hpp"
#include "backend/looped/looped.hpp"

namespace big
{
	// reference: https://github.com/Yimura/YimMenu/issues/180
	void looped::system_anticheat_bypass()
	{
		*g_pointers->m_some_anticheat_thing = 0;
	}
}