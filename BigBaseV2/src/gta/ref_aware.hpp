#pragma once
#include "base.hpp"

namespace rage
{
	template <typename T>
	class fwRefAwareBaseImpl : public T
	{
	private:
		void *m_ref; // 0x08
	};

	class fwRefAwareBase : public fwRefAwareBaseImpl<datBase>
	{
	};

	static_assert(sizeof(fwRefAwareBase) == 0x10);
}
