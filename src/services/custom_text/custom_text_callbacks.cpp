#include "hooking/hooking.hpp"
#include "pointers.hpp"

namespace big
{
	const char* respawn_label_callback(const char* label)
	{
		if (g.self.god_mode)
			return "~r~Dying with god mode, how?";

		return nullptr;
	}

	const char* do_ceo_name_resize(const char* label)
	{
		auto original = g_hooking->get_original<hooks::get_label_text>()(g_pointers->m_gta.m_ctext_file_ptr, label);
		if (auto pos = strstr((char*)original, "15"))
		{
			pos[0] = '4';
			pos[1] = '1';
		}
		return original;
	}
}
