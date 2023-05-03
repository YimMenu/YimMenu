#include "repair_vehicle.hpp"

#include "util/vehicle.hpp"


namespace big
{
	void repairpv::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		vehicle::repair(self::veh);
	}
}
