#pragma once
#include "core/enums.hpp"

namespace big
{
	inline std::unordered_map<CommandAccessLevel, const char*> COMMAND_ACCESS_LEVELS = {
	    {CommandAccessLevel::NONE, "None"},
	    {CommandAccessLevel::FRIENDLY, "Friendly"},
	    {CommandAccessLevel::AGGRESSIVE, "Aggressive"},
	    {CommandAccessLevel::TOXIC, "Toxic"},
	    {CommandAccessLevel::ADMIN, "Admin (!)"},
	};
}