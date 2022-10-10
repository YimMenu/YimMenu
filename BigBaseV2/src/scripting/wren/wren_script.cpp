#include "wren_script.hpp"

namespace big
{
	wren_script::wren_script()
	{

	}

	wren_script::wren_script(WrenVM* vm, const std::string& module_name, const std::filesystem::file_time_type& last_write_time, bool has_tick_function) :
		m_vm(vm),
		m_module_name(module_name),
		m_last_write_time(last_write_time),
		m_has_tick_function(has_tick_function)
	{
		if (m_has_tick_function)
		{
			wrenEnsureSlots(m_vm, 1);
			wrenGetVariable(m_vm, m_module_name.c_str(), "Script", 0);
			m_script_class_handle = wrenGetSlotHandle(m_vm, 0);

			m_script_tick_fn_handle = wrenMakeCallHandle(vm, "tick()");
		}
	}

	wren_script::~wren_script()
	{
		if (m_has_tick_function)
		{
			wrenReleaseHandle(m_vm, m_script_tick_fn_handle);

			wrenReleaseHandle(m_vm, m_script_class_handle);
		}
	}

	void wren_script::tick()
	{
		if (m_has_tick_function)
		{
			wrenSetSlotHandle(m_vm, 0, m_script_class_handle);
			wrenCall(m_vm, m_script_tick_fn_handle);
		}
	}

	const std::filesystem::file_time_type& wren_script::last_write_time() const
	{
		return m_last_write_time;
	}
}
