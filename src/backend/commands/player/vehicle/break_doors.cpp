#include "backend/player_command.hpp"
#include "gta/net_game_event.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	inline void break_vehicle_door(CVehicle* vehicle, std::uint8_t door_index)
	{
		if (!vehicle->m_net_object)
			return;

		int object_id = vehicle->m_net_object->m_object_id;

		g_pointers->m_gta.m_check_event_queue(*g_pointers->m_gta.m_net_event_manager, true);

		CDoorBreakEvent* event =
		    reinterpret_cast<CDoorBreakEvent*>(g_pointers->m_gta.m_get_new_pool_item(*g_pointers->m_gta.m_net_event_pool));

		if (!event)
			return;

		g_pointers->m_gta.m_construct_door_break_event(event);

		event->m_vehicle_id = object_id;
		event->m_door_id    = door_index;

		g_pointers->m_gta.m_queue_network_event(*g_pointers->m_gta.m_net_event_manager, event);
	}

	class break_doors : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			Ped ped         = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);
			for (int i = 0; i < VEHICLE::GET_NUMBER_OF_VEHICLE_DOORS(vehicle); i++)
				break_vehicle_door(player->get_current_vehicle(), i);
		}
	};

	break_doors g_break_doors("breakdoors", "BACKEND_BREAK_VEHICLE_DOORS", "BACKEND_BREAK_VEHICLE_DOORS_DESC", 0);
}