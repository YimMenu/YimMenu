#include "hooking.hpp"

#include <pointers.hpp>

namespace big
{
	bool hooks::fix_some_train_crash(size_t index_into_array, float* i)
	{
		if (index_into_array < 0)
			return 0;

		constexpr size_t sizeof_some_struct = 592;
		size_t obj_offset                   = sizeof_some_struct * index_into_array;

		if (*((byte*)&g_pointers->m_gta.m_some_train_array + obj_offset + 5))
		{
			float exit_cond = *(float*)((byte*)&g_pointers->m_gta.m_some_train_array + obj_offset + 32);
			if (exit_cond <= 0)
			{
				return 0;
			}
		}

		return g_hooking->get_original<hooks::fix_some_train_crash>()(index_into_array, i);
	}
}
