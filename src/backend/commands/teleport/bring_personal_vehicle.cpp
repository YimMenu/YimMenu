#include "backend/command.hpp"
#include "natives.hpp"
#include "util/mobile.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class bring_personal_vehicle : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			Vehicle veh = mobile::mechanic::get_personal_vehicle();
			vehicle::bring(veh, self::pos);
		}
	};

	bring_personal_vehicle g_bring_personal_vehicle("bringpv", "Bring Personal Vehicle", "Teleports your PV near you", 0);
}