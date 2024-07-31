#include "hooking/hooking.hpp"
#include "util/fuzzer.hpp"

namespace big
{
	bool hooks::read_bits_single(void* data, int* out_value, int size, int offset)
	{
		auto orig = g_hooking->get_original<hooks::read_bits_single>()(data, out_value, size, offset);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(out_value, sizeof(int), __FUNCTION__);
			*out_value = fuzzer::fuzz_bits(*out_value, size);
			return true;
		}

		return orig;
	}
}