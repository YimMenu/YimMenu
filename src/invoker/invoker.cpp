#include "invoker.hpp"
#include "crossmap.hpp"
#include "pointers.hpp"

namespace big
{
	void NativeInvoker::CacheHandlers()
	{
		if (m_AreHandlersCached)
			return;

		for (int i = 0; i < g_Crossmap.size(); i++)
		{
			m_Handlers[i] = g_pointers->(Pointers.NativeRegistrationTable, g_Crossmap[i]);
		}

		m_AreHandlersCached = true;
	}
}
