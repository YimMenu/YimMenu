#include "features/custom_text.hpp"
#include "hooking.hpp"
#include "natives.hpp"

namespace big
{
	const char* hooks::get_label_text(void* unk, const char* label)
	{
		if (g_running)
			if (auto text = custom_text::get_text(rage::joaat(label)))
				return text;

		return g_hooking->m_get_label_text_hook.get_original<decltype(&get_label_text)>()(unk, label);
	}
}