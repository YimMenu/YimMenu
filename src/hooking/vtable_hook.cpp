#include "vtable_hook.hpp"

namespace big
{
	vtable_hook::vtable_hook(void** vft, std::size_t num_funcs) :
	    m_num_funcs(num_funcs),
	    m_table(vft),
	    m_backup_table(std::make_unique<void*[]>(m_num_funcs)),
	    m_hook_table(std::make_unique<void*[]>(m_num_funcs))
	{
		std::memcpy(m_backup_table.get(), m_table, m_num_funcs * sizeof(void*));
		std::memcpy(m_hook_table.get(), m_table, m_num_funcs * sizeof(void*));
	}

	vtable_hook::~vtable_hook()
	{
		disable();
	}

	void vtable_hook::hook(std::size_t index, void* func)
	{
		m_hook_table[index] = func;
	}

	void vtable_hook::unhook(std::size_t index)
	{
		m_hook_table[index] = m_backup_table[index];
	}

	void vtable_hook::enable()
	{
		std::memcpy(m_table, m_hook_table.get(), m_num_funcs * sizeof(void*));
	}

	void vtable_hook::disable()
	{
		std::memcpy(m_table, m_backup_table.get(), m_num_funcs * sizeof(void*));
	}
}
