#include "backend/looped/looped.hpp"
#include "pointers.hpp"

namespace big
{
	void looped::system_disable_model_spawn_bypass()
	{
		if (*(unsigned short*)g_pointers->m_model_spawn_bypass == 0x9090) 
		{
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
			LOG(WARNING) << "stop vehicle bypass";
		}
	}
}
