#include "wren_script.hpp"

namespace big
{
	wren_script::wren_script()
	{

	}

	wren_script::wren_script(WrenVM* vm, const std::string& module_name, const std::filesystem::file_time_type& last_write_time) :
		m_vm(vm),
		m_module_name(module_name),
		m_last_write_time(last_write_time)
	{

	}

	wren_script::~wren_script()
	{

	}

	const std::filesystem::file_time_type& wren_script::last_write_time() const
	{
		return m_last_write_time;
	}
}
