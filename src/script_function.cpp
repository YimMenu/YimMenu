#include "script_function.hpp"

namespace big
{
	script_function::script_function(const std::string& name, const rage::joaat_t script, const std::string& pattern) :
	    m_name(name),
	    m_script(script),
	    m_pattern(pattern),
	    m_ip(0)
	{
	}

	void script_function::populate_ip()
	{
		if (m_ip == 0)
		{
			auto program = gta_util::find_script_program(m_script);

			if (!program)
				return;

			auto location = scripts::get_code_location_by_pattern(program, m_pattern);

			if (!location)
				LOG(FATAL) << "Failed to find pattern " << m_name << " in script " << program->m_name;
			else
				LOG(VERBOSE) << "Found pattern " << m_name << " at " << HEX_TO_UPPER(location.value()) << " in script " << program->m_name;

			m_ip = location.value();
		}
	}
}