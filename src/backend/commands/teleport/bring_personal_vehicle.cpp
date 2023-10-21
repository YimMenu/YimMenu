#include "backend/command.hpp"
#include "natives.hpp"
#include "util/mobile.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class bring_personal_vehicle : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			Vehicle veh = mobile::mechanic::get_personal_vehicle();
			vehicle::bring(veh, self::pos);
		}
	};

	bring_personal_vehicle g_bring_personal_vehicle("bringpv", "BRING_PV", "BACKEND_BRING_PERSONAL_VEHICLE_DESC", 0);
}