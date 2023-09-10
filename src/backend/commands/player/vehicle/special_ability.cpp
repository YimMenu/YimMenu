#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
	template<int ability_type>
	class vehicle_special_ability : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			{
				g_notification_service->push_warning("TOXIC"_T.data(), "ERROR_PLAYER_IS_NOT_IN_VEHICLE"_T.data());
			}
			else
			{
				g_pointers->m_gta.m_activate_special_ability(player->get_current_vehicle(), ability_type);
			}
		}
	};

	vehicle_special_ability<0> g_special_jump_vehicle("svehjump", "Special: Jump", "Activates the vehicle jump on the player's vehicle. This may cause undefined behavior if the vehicle cannot jump", 0);
	vehicle_special_ability<1> g_special_boost_vehicle("svehboost", "Special: Boost", "Activates the boost on the player's vehicle. This may cause undefined behavior if the vehicle cannot boost", 0);
	vehicle_special_ability<3> g_special_shunt_left("sshuntleft", "Special: Shunt Left", "Shunts the player's vehicle to the left", 0);
	vehicle_special_ability<2> g_special_shunt_right("sshuntright", "Special: Shunt Right", "Shunts the player's vehicle to the right", 0);
}