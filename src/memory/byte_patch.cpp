#include "byte_patch.hpp"

namespace memory
{
	byte_patch::~byte_patch()
	{
		restore();
	}

	void byte_patch::apply() const
	{
		memcpy(m_address, m_value.get(), m_size);
	}

	void byte_patch::restore() const
	{
		memcpy(m_address, m_original_bytes.get(), m_size);
	}

	void byte_patch::remove() const
	{
		if (const auto it = std::find(m_patches.begin(), m_patches.end(), this); it != m_patches.end())
		{
			m_patches.erase(it);
		}
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
