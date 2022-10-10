#pragma once
#include "wren.hpp"

namespace big
{
	class wren_script
	{
		WrenVM* m_vm = nullptr;
		std::string m_module_name{};
		std::filesystem::file_time_type m_last_write_time{};

		bool m_has_tick_function = false;
		WrenHandle* m_script_class_handle = nullptr;
		WrenHandle* m_script_tick_fn_handle = nullptr;

	public:
		wren_script();
		wren_script(WrenVM* vm, const std::string& module_name, const std::filesystem::file_time_type& last_write_time, bool has_tick_function);
		~wren_script();

		void tick();

		const std::filesystem::file_time_type& last_write_time() const;
	};
}
