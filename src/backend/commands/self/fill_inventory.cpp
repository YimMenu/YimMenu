#include "backend/command.hpp"
#include "natives.hpp"
#include "util/local_player.hpp"

namespace big
{
	class fill_inventory : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			std::string mpPrefix = local_player::get_mp_prefix();
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "NO_BOUGHT_YUM_SNACKS"), 30, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "NO_BOUGHT_HEALTH_SNACKS"), 15, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "NO_BOUGHT_EPIC_SNACKS"), 5, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_1_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_2_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_3_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_4_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_5_COUNT"), 10, true);
		}
	};

	fill_inventory g_fill_inventory("fillsnacks", "Fill Inventory", "Refills snacks and armor", 0);
}