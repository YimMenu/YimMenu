#include "hooking.hpp"

namespace big
{
	int hooks::nt_query_virtual_memory(void* _this, HANDLE handle, PVOID base_addr, int info_class, MEMORY_BASIC_INFORMATION* info, int size, size_t* return_len)
	{
		// LOG(INFO) << "Reached here, base addr: " << base_addr;
		return 1;
	}
}
