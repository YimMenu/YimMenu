#pragma once
#include "wren.hpp"

namespace big
{
	class wren_script
	{
		WrenVM* m_vm = nullptr;
		std::string m_module_name{};
		std::filesystem::file_time_type m_last_write_time{};

	public:
		wren_script();
		wren_script(WrenVM* vm, const std::string& module_name, const std::filesystem::file_time_type& last_write_time);
		~wren_script();

		const std::filesystem::file_time_type& last_write_time() const;
	};
}
