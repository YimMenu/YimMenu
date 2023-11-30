#pragma once
#include "base/HashTable.hpp"
#include "function_types.hpp"
#include "gta/fwddec.hpp"
#include "gta_pointers.hpp"
#include "memory/module.hpp"
#include "sc_pointers.hpp"
#include "services/gta_data/cache_file.hpp"
#include "socialclub/ScInfo.hpp"
#include "util/compile_time_helpers.hpp"

namespace big
{
	class pointers
	{
	private:
		static void get_gta_batch(memory::module region);
		static void get_sc_batch(memory::module region);

	public:
		explicit pointers();
		~pointers();

	public:
		HWND m_hwnd{};

		gta_pointers m_gta;
		socialclub_pointers m_sc;
	};

	inline pointers* g_pointers{};
}
