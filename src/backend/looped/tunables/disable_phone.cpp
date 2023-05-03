#include "disable_phone.hpp"

#include "core/scr_globals.hpp"
#include "natives.hpp"

namespace big
{
	void disable_phone::on_tick()
	{
		*script_global(20366).as<bool*>() = true;
	}

	void disable_phone::on_disable()
	{
		*script_global(20366).as<bool*>() = false;
	}
}
