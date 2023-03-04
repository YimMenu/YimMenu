#include "hooking.hpp"
#include "pointers.hpp"

namespace big
{
	void* hooks::infinite_train_crash(void* carriage)
	{
		void* current_carriage = carriage;
		int count              = 0;

		while (g_pointers->m_get_next_carriage(current_carriage))
		{
			if (++count > 20)
				return nullptr;

			current_carriage = g_pointers->m_get_next_carriage(current_carriage);
		}

		return current_carriage;
	}
}