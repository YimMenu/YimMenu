#include "lua_patch.hpp"

#include "memory/byte_patch.hpp"

namespace big
{
	lua_patch::lua_patch(memory::byte_patch* patch) :
	    m_byte_patch(patch)
	{
	}

	lua_patch::~lua_patch()
	{
		m_byte_patch->restore();
		m_byte_patch->remove();
	}

	void lua_patch::apply()
	{
		m_byte_patch->apply();
	}

	void lua_patch::restore()
	{
		m_byte_patch->restore();
	}
}