#include "auto_tp_to_waypoint.hpp"

#include "natives.hpp"
#include "util/teleport.hpp"

namespace big
{
	void auto_tp_to_waypoint::on_tick()
	{
		//this is a hack to prevent the warning notify..
		if (!teleport::to_blip((int)BlipIcons::Waypoint))
			return;

		teleport::to_waypoint();
	}
}
