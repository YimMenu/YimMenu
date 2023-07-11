#pragma once
#include "fiber_pool.hpp"
#include "lua/lua_manager.hpp"
#include "lua/lua_module.hpp"
#include "script_mgr.hpp"

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

		// Lua API: Function
		// Class: script_util
		// Name: sleep
		// Param: ms: integer: The amount of time in milliseconds that we will sleep for.
		// Sleep for the given amount of time, time is in milliseconds.
	};
	static script_util dummy_script_util;

	// Lua API: Table
	// Name: script
	// Table containing helper functions related to gta scripts.

	// Lua API: Function
	// Table: script
	// Name: register_looped
	// Param: name: string: name of your new looped script
	// Param: func: function: function that will be executed in a forever loop.
	// Registers a function that will be looped as a gta script.
	// **Exemple Usage:**
	// ```lua
	// script.register_looped("nameOfMyLoopedScript", function (script)
	//     -- sleep until next game frame
	//     script:yield()
	//
	//     local ModelHash = joaat("adder")
	//     if not STREAMING.IS_MODEL_IN_CDIMAGE(ModelHash) then return end
	//     STREAMING.REQUEST_MODEL(ModelHash) -- Request the model
	//     while not STREAMING.HAS_MODEL_LOADED(ModelHash) do -- Waits for the model to load
	//         script:yield()
	//     end
	//     local myPed = PLAYER.PLAYER_PED_ID()
	//     local myCoords = ENTITY.GET_ENTITY_COORDS(myPed, true)
	//     -- Spawns a networked vehicle on your current coords
	//     local spawnedVehicle = VEHICLE.CREATE_VEHICLE(ModelHash, myCoords.x, myCoords.y, myCoords.z, ENTITY.GET_ENTITY_HEADING(myPed), true, false)
	//     -- removes model from game memory as we no longer need it
	//     STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash)
	//     -- sleep for 2s
	//     script:sleep(2000)
	//     ENTITY.DELETE_ENTITY(spawnedVehicle)
	// end)
	// ```
	static void register_looped(const std::string& name, sol::coroutine func, sol::this_state state)
	{
		auto module = sol::state_view(state)["!this"].get<big::lua_module*>();

		module->m_registered_scripts.push_back(big::g_script_mgr.add_script(std::make_unique<big::script>(
		    [func] () mutable {
			    while (big::g_running)
			    {
				    auto res = func(dummy_script_util);

				    if (!res.valid())
					    big::g_lua_manager->handle_error(res, res.lua_state());

					if (func.runnable())
					{
					    big::script::get_current()->yield(std::chrono::milliseconds(res.return_count() ? res[0] : 0));
					}
					else
					{
					    big::script::get_current()->yield();
					}
			    }
		    },
		    name)));
	}

	// Lua API: Function
	// Table: script
	// Name: run_in_fiber
	// Param: func: function: function that will be executed once in the fiber pool.
	// Executes a function once inside the fiber pool, you can call natives inside it and yield or sleep.
	// **Exemple Usage:**
	// ```lua
	// script.run_in_fiber(function (script)
	//     -- sleep until next game frame
	//     script:yield()
	// 
	//     local ModelHash = joaat("adder")
    //     if not STREAMING.IS_MODEL_IN_CDIMAGE(ModelHash) then return end
    //     STREAMING.REQUEST_MODEL(ModelHash) -- Request the model
    //     while not STREAMING.HAS_MODEL_LOADED(ModelHash) do -- Waits for the model to load
    //         script:yield()
    //     end
    //     local myPed = PLAYER.PLAYER_PED_ID()
    //     local myCoords = ENTITY.GET_ENTITY_COORDS(myPed, true)
    //     -- Spawns a networked vehicle on your current coords
    //     local spawnedVehicle = VEHICLE.CREATE_VEHICLE(ModelHash, myCoords.x, myCoords.y, myCoords.z, ENTITY.GET_ENTITY_HEADING(myPed), true, false) 
    //     -- removes model from game memory as we no longer need it
    //     STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash)
	//     -- sleep for 2s
    //     script:sleep(2000)
    //     ENTITY.DELETE_ENTITY(spawnedVehicle)
	// end)
	// ```
	static void run_in_fiber(sol::coroutine func)
	{
		big::g_fiber_pool->queue_job([func] () mutable {
			while (big::g_running)
			{
				auto res = func(dummy_script_util);

				if (!res.valid())
					big::g_lua_manager->handle_error(res, res.lua_state());

				// Still runnable, meaning that the user function yielded
				// and that there is more code to run still.
				if (func.runnable())
				{
					big::script::get_current()->yield(std::chrono::milliseconds(res.return_count() ? res[0] : 0));
				}
				else
				{
					break;
				}
			}
		});
	}

	static void bind(sol::state& state)
	{
		auto ns               = state["script"].get_or_create<sol::table>();
		ns["register_looped"] = register_looped;
		ns["run_in_fiber"]    = run_in_fiber;

		sol::function lua_coroutine_yield = state["coroutine"]["yield"];

		//clang-format off
		state.new_usertype<script_util>("script_util",
		    "yield", lua_coroutine_yield,
		    "sleep", lua_coroutine_yield);
		//clang-format on
	}
}