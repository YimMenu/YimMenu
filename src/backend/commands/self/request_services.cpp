#include "request_services.hpp"

#include "script_global.hpp"
#include "util/mobile.hpp"

namespace big
{
	void boat_pickup::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		mobile::merry_weather::request_boat_pickup();
	}

	void ballistic_armor::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		mobile::ceo_abilities::request_ballistic_armor();
	}
}
