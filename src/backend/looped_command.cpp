#include "looped_command.hpp"

#include "fiber_pool.hpp"

namespace big
{
	looped_command::looped_command(const std::string& name, const std::string& label, const std::string& description, bool& toggle) :
	    bool_command(name, label, description, toggle)
	{
		g_looped_commands.push_back(this);
	}

	void looped_command::enable()
	{
		if (!m_toggle)
		{
			m_toggle       = true;
			m_last_enabled = true;
			g_fiber_pool->queue_job([this] {
				on_enable();
			});
		}
	}

	void looped_command::disable()
	{
		if (m_toggle)
		{
			m_toggle       = false;
			m_last_enabled = false;
			g_fiber_pool->queue_job([this] {
				disable();
			});
		}
	}

	void looped_command::refresh()
	{
		if (m_toggle && !m_last_enabled)
		{
			m_last_enabled = true;
			g_fiber_pool->queue_job([this] {
				on_enable();
			});
		}
		else if (!m_toggle && m_last_enabled)
		{
			m_last_enabled = false;
			g_fiber_pool->queue_job([this] {
				on_disable();
			});
		}
	}
}