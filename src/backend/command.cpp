#include "command.hpp"
#include "fiber_pool.hpp"

namespace big
{
	command::command(const std::string& name, std::uint8_t num_args, bool fiber_pool) :
		m_name(name),
		m_num_args(num_args),
		m_fiber_pool(fiber_pool)
	{
		g_commands[rage::joaat(name)] = this;
	}

	void command::call(const std::vector<std::uint64_t>& args)
	{
		if (args.size() != m_num_args)
		{
			LOG(WARNING) << "Command " << m_name << " called with the wrong number of arguments. Expected " << m_num_args << ", got " << args.size();
			return;
		}

		if (m_fiber_pool)
			g_fiber_pool->queue_job([this, args] { execute(args); });
		else
			execute(args);
	}

	command* command::get(rage::joaat_t command)
	{
		return g_commands[command];
	}

	void command::call(rage::joaat_t command, const std::vector<std::uint64_t>& args)
	{
		g_commands[command]->call(args);
	}
}