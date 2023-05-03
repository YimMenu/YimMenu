#include "clean_player.hpp"

namespace big
{
 void clean_player::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			entity::clean_ped(self::ped);
		}
}