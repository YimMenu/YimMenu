#include "custom_text_callbacks.hpp"
#include "core/settings/self.hpp"

namespace big
{
	const char* respawn_label_callback(const char* label)
	{
		if (g_self.god_mode)
			return "~r~Dying with god mode, how?";

		return nullptr;
	}
}
