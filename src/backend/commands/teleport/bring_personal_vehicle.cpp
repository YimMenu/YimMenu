#include "bring_personal_vehicle.hpp"

#include "natives.hpp"
#include "util/mobile.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void bring_personal_vehicle::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		Vehicle veh = mobile::mechanic::get_personal_vehicle();
		vehicle::bring(veh, self::pos);
	}
}
