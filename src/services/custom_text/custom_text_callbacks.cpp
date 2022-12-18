#include "custom_text_callbacks.hpp"

namespace big
{
	const char* respawn_label_callback(const char* label)
	{
		if (g.self.god_mode)
			return "~r~Dying with god mode, how?";

		return nullptr;
	}
}
