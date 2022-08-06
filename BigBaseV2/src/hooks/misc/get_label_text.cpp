#include "hooking.hpp"
#include "services/custom_text/custom_text_service.hpp"

namespace big
{
	const char* hooks::get_label_text(void* unk, const char* label)
	{
		if (const auto text = g_custom_text_service->get_text(label); text)
			return text;

		return g_hooking->m_get_label_text.get_original<decltype(&get_label_text)>()(unk, label);
	}
}
