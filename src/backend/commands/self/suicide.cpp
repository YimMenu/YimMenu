#include "suicide.hpp"

#include "natives.hpp"

namespace big
{
	void suicide::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		ENTITY::SET_ENTITY_HEALTH(self::ped, 0, 0);
	}
}
