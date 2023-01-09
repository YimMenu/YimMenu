#include "backend/command.hpp"
#include "natives.hpp"

namespace big
{
	class heal : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			ENTITY::SET_ENTITY_HEALTH(self::ped, PED::GET_PED_MAX_HEALTH(self::ped), 0);
			PED::SET_PED_ARMOUR(self::ped, PLAYER::GET_PLAYER_MAX_ARMOUR(self::id));
		}
	};

	heal g_heal("heal", "Heal", "Restores full health and armor", 0);
}