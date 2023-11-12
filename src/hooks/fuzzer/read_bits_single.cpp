#include "hooking.hpp"
#include "natives.hpp"

namespace big
{
	bool hooks::read_bits_single(void* data, int* out_value, int size, int offset)
	{
		return g_hooking->get_original<hooks::read_bits_single>()(data, out_value, size, offset);
	}
}