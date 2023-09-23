#include "backend/command.hpp"
#include "natives.hpp"

namespace big
{
	class fill_inventory : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			std::string prefix = "MP" + std::to_string(self::char_index) + "_";
			STATS::STAT_SET_INT(rage::joaat(prefix + "NO_BOUGHT_YUM_SNACKS"), 30, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "NO_BOUGHT_HEALTH_SNACKS"), 15, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "NO_BOUGHT_EPIC_SNACKS"), 5, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "NUMBER_OF_CHAMP_BOUGHT"), 5, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "NUMBER_OF_ORANGE_BOUGHT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "NUMBER_OF_BOURGE_BOUGHT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "NUMBER_OF_SPRUNK_BOUGHT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "MP_CHAR_ARMOUR_1_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "MP_CHAR_ARMOUR_2_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "MP_CHAR_ARMOUR_3_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "MP_CHAR_ARMOUR_4_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "MP_CHAR_ARMOUR_5_COUNT"), 10, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "CIGARETTES_BOUGHT"), 20, true);
			STATS::STAT_SET_INT(rage::joaat(prefix + "BREATHING_APPAR_BOUGHT"), 20, true);
		}
	};

	fill_inventory g_fill_inventory("fillsnacks", "FILL_INVENTORY", "FILL_INVENTORY_DESC", 0);
}