#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
	class smash_windows : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
			{
				entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(ped));
				Vehicle UserVeh     = PED::GET_VEHICLE_PED_IS_IN(ped, false);
				static int windowID = 0;
				for (windowID = 0; windowID < 10; windowID++)
				{
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, windowID);
				}
			}
		}
	};

	smash_windows g_smash_windows("smashwindows", "Smash Vehicle Windows", "Smashes all their windows", 0);
}