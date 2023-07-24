#include "byte_patch.hpp"

namespace memory
{
	byte_patch::~byte_patch()
	{
		restore();
	}

	void byte_patch::apply()
	{
		if (!m_is_active)
		{
			m_is_active = true;

			VirtualProtect(m_address, m_size, PAGE_EXECUTE_READWRITE, (PDWORD)&m_old_protect);
			memcpy(m_address, m_value.get(), m_size);
		}
	}

	void byte_patch::restore()
	{
		if (m_is_active)
		{
			DWORD temp;
			VirtualProtect(m_address, m_size, m_old_protect, &temp);
			memcpy(m_address, m_original_bytes.get(), m_size);
		
			m_is_active = false;
		}
	}

	void byte_patch::remove() const
	{
		std::erase_if(m_patches, [this](auto& el) {
			return el.get() == this;
		});
	}

	void byte_patch::restore_all()
	{
		m_patches.clear();
	}

	bool operator==(const std::unique_ptr<byte_patch>& a, const byte_patch* b)
	{
		return a->m_address == b->m_address;
	}
}
