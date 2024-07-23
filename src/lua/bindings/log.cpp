#pragma once

namespace lua::log
{
	// Lua API: Table
	// Name: log
	// Table containing functions for printing to console / log file.

	// Lua API: Function
	// Table: log
	// Name: info
	// Param: data: string
	// Logs an informational message.
	static void info(const std::string& data, sol::this_state state)
	{
		LOG(INFO) << sol::state_view(state)["!module_name"].get<std::string>() << ": " << data;
	}

	// Lua API: Function
	// Table: log
	// Name: warning
	// Param: data: string
	// Logs a warning message.
	static void warning(const std::string& data, sol::this_state state)
	{
		LOG(WARNING) << sol::state_view(state)["!module_name"].get<std::string>() << ": " << data;
	}

	// Lua API: Function
	// Table: log
	// Name: debug
	// Param: data: string
	// Logs a debug message.
	static void debug(const std::string& data, sol::this_state state)
	{
		LOG(VERBOSE) << sol::state_view(state)["!module_name"].get<std::string>() << ": " << data;
	}

	void bind(sol::state& state)
	{
		auto ns       = state["log"].get_or_create<sol::table>();
		ns["info"]    = info;
		ns["warning"] = warning;
		ns["debug"]   = debug;
	}
}