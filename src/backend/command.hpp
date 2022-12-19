#pragma once
#include "gta/joaat.hpp"

namespace big
{
	class command
	{
	protected:
		std::string m_name;
		std::uint8_t m_num_args;
		bool m_fiber_pool;
		virtual void execute(const std::vector<std::uint64_t>& args) = 0;

	public:
		command(const std::string& name, std::uint8_t num_args, bool fiber_pool = true);
		void call(const std::vector<std::uint64_t>& args);
		static command* get(rage::joaat_t command);
		static void call(rage::joaat_t command, const std::vector<std::uint64_t>& args);
	};

    inline std::unordered_map<rage::joaat_t, command*> g_commands;
}