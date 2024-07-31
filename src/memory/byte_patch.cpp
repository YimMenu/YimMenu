#include "byte_patch.hpp"

namespace memory
{
	byte_patch::~byte_patch()
	{
		restore();
	}

	void byte_patch::apply() const
	{
		DWORD old_protect;
		VirtualProtect(m_address, m_size, PAGE_EXECUTE_READWRITE, (PDWORD)&old_protect);

		memcpy(m_address, m_value.get(), m_size);

		DWORD unused;
		VirtualProtect(m_address, m_size, old_protect, &unused);
	}

	void byte_patch::restore() const
	{
		DWORD old_protect;
		VirtualProtect(m_address, m_size, PAGE_EXECUTE_READWRITE, (PDWORD)&old_protect);

		memcpy(m_address, m_original_bytes.get(), m_size);

		DWORD unused;
		VirtualProtect(m_address, m_size, old_protect, &unused);
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
