#include "backend/command.hpp"
#include "natives.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"

namespace big
{
	class teleport_to_personal_vehicle : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx)
		{
			Vehicle veh = mobile::mechanic::get_personal_vehicle();
			teleport::into_vehicle(veh);
		}
	};

	teleport_to_personal_vehicle g_teleport_to_personal_vehicle("pvtp", "Teleport To Personal Vehicle", "Teleports you into your PV", 0);
}