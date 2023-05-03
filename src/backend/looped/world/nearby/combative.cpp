#include "combative.hpp"

#include "natives.hpp"

namespace big
{
	void combative::on_enable()
	{
		MISC::SET_RIOT_MODE_ENABLED(true);
	}

	void combative::on_tick()
	{
	}

	void on_disable()
	{
		MISC::SET_RIOT_MODE_ENABLED(false);
	}
}
