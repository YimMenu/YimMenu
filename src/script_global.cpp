#include "script_global.hpp"
#include "pointers.hpp"

namespace big
{
	void* script_global::get() const
	{
		return g_pointers->m_gta.m_script_globals[m_index >> 0x12 & 0x3F] + (m_index & 0x3FFFF);
	}
}
