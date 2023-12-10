#pragma once

namespace lua::script
{
	// Lua API: Class
	// Name: script_util
	// Class for gta script utils, the instance is usually given to you.
	class script_util
	{
	public:
		// We keep the two functions below yield and sleep for backcompat.
		// The idea of exposing big::script::get_current()->yield directly to lua
		// on the surface looks like it could works but it doesnt, the lua stack end up exploding.

		// Lua API: Function
		// Class: script_util
		// Name: yield
		// Yield execution.
		int yield();

		// Lua API: Function
		// Class: script_util
		// Name: sleep
		// Param: ms: integer: The amount of time in milliseconds that we will sleep for.
		// Sleep for the given amount of time, time is in milliseconds.
		int sleep(int ms);
	};

	void bind(sol::state& state);
}