#pragma once

#define SOL_SAFE_USERTYPE 1
#define SOL_SAFE_REFERENCES 1
#define SOL_SAFE_FUNCTION 1
#define SOL_SAFE_NUMERICS 1
#define SOL_SAFE_GETTER 1
#define SOL_NO_CHECK_NUMBER_PRECISION 1

// This is intended to be disabled.
// Allow functions to be called without giving all of its args.
// Enabling it would make current usage of native functions like
// local r, g, b = VEHICLE.GET_VEHICLE_COLOR(spawnedVehicle)
// much more annoying due to how pointer args are handled,
// there is no way to know unless by hardcoding manually all of them that
// a pointer arg is an in or out parameter.
//
// #define SOL_SAFE_FUNCTION_CALLS

#include "lua/sol.hpp"