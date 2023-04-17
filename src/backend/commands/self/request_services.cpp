#include "backend/command.hpp"
#include "script_global.hpp"
#include "util/mobile.hpp"

namespace big
{
	class boat_pickup : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			mobile::merry_weather::request_boat_pickup();
		}
	};

	class ballistic_armor : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			mobile::ceo_abilities::request_ballistic_armor();
		}
	};

	boat_pickup g_boat_pickup("boatpickup", "Request Boat Pickup", "Request a boat pickup", 0);
	ballistic_armor g_ballistic_armor("ballisticarmor", "Request Ballistic Equipment", "Requests ballistic equipment which includes ballistic armor and an minigun", 0);
}