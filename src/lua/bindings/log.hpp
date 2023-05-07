#pragma once

namespace lua::log
{
	static void info(const std::string& data, sol::this_state state)
	{
		LOG(INFO) << sol::state_view(state)["!module_name"].get<std::string>() << ": " << data;
	}

	static void warning(const std::string& data, sol::this_state state)
	{
		LOG(WARNING) << sol::state_view(state)["!module_name"].get<std::string>() << ": " << data;
	}

	static void debug(const std::string& data, sol::this_state state)
	{
		LOG(VERBOSE) << sol::state_view(state)["!module_name"].get<std::string>() << ": " << data;
	}

	static void bind(sol::state& state)
	{
		auto ns       = state["log"].get_or_create<sol::table>();
		ns["info"]    = info;
		ns["warning"] = warning;
		ns["debug"]   = debug;
	}
}