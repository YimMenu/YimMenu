#include "teleport_to_waypoint.hpp"

#include "natives.hpp"
#include "util/teleport.hpp"

namespace big
{
	void teleport_to_waypoint::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		teleport::to_waypoint();
	}
}
