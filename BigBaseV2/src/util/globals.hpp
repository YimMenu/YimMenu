#pragma once
#include "script_global.hpp"

namespace big::globals
{
	inline Vehicle get_personal_vehicle()
	{
		return *script_global(2810287).at(298).as<Vehicle*>();
	}
}