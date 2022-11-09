#include "hooking.hpp"

namespace big
{
	int hooks::get_pool_type()
	{
		return g->spoofing.pool_type;
	}
}