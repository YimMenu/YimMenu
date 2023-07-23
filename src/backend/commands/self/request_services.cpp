#include "backend/command.hpp"
#include "script_global.hpp"
#include "util/mobile.hpp"

namespace big
{
	class boat_pickup : command
	{
		using command::command;

		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			mobile::merry_weather::request_boat_pickup();
		}
	};

	class ballistic_armor : command
	{
		using command::command;

		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			mobile::ceo_abilities::request_ballistic_armor();
		}
	};

	class request_avenger : command
	{
		using command::command;

		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			mobile::services::request_avenger();
		}
	};

	class request_kosatka : command
	{
		using command::command;

		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			mobile::services::request_kosatka();
		}
	};

	class request_moc : command
	{
		using command::command;

		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			mobile::services::request_mobile_operations_center();
		}
	};

	class request_terrorbyte : command
	{
		using command::command;

		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			mobile::services::request_terrorbyte();
		}
	};

	class request_acidlab : command
	{
		using command::command;

		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			mobile::services::request_acidlab();
		}
	};

	class request_acidlab_bike : command
	{
		using command::command;

		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			mobile::services::request_acidlab_bike();
		}
	};

	class request_taxi : command
	{
		using command::command;

		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			mobile::mobile_misc::request_taxi();
		}
	};

	boat_pickup g_boat_pickup("boatpickup", "Request Boat Pickup", "Request a boat pickup", 0);
	ballistic_armor g_ballistic_armor("ballisticarmor", "Request Ballistic Equipment", "Requests ballistic equipment which includes ballistic armor and an minigun", 0);
	request_avenger g_request_avenger("avenger", "Request Avenger", "Requests the Avenger", 0);
	request_kosatka g_request_kosatka("kosatka", "Request Kosatka", "Requests the Kosatka", 0);
	request_moc g_request_moc("moc", "Request M.O.C", "Requests the Mobile Operations Center", 0);
	request_terrorbyte g_request_terrorbyte("terrorbyte", "Request Terrorbyte", "Requests the terrorbyte", 0);
	request_acidlab g_request_acidlab("acidlab", "Request Acid Lab", "Requests the Acid Lab", 0);
	request_acidlab_bike g_request_acidlab_bike("acidbike", "Request Acid Bike", "Requests the Acid Lab Delivery Bike", 0);
	request_taxi g_request_taxi("taxi", "Request Taxi", "Requests a taxi to give you a ride", 0);
}