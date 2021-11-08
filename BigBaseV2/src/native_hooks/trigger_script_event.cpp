#include "native_hooks.hpp"
#include "pointers.hpp"

namespace big::native_hook
{
	void TRIGGER_SCRIPT_EVENT(rage::scrNativeCallContext* src)
	{
		int event_group = src->get_arg<int>(0);
		Any* event_data = src->get_arg<Any*>(1);
		int event_size = src->get_arg<int>(3);
		int player_bits = src->get_arg<int>(4);

		if (event_group)
		{
			Hash event_hash = event_data[0];

			LOG(INFO) << "Event hash: " << event_hash;
			for (size_t i = 1; i < std::min(event_size, 200); i++)
				LOG(INFO) << "Arg[#" << i << "] : " << event_data[i];
		}

		SCRIPT::TRIGGER_SCRIPT_EVENT(event_group, event_data, event_size, player_bits);
	}
}