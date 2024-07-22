#include "backend/player_command.hpp"
#include "util/entity.hpp"

namespace big
{
	class delete_vehicle : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			auto object = player->get_current_vehicle();
			if (object)
				entity::force_remove_network_entity(object);
			else if (player->get_ped())
			{
				auto net_id = *(int16_t*)(((__int64)player->get_ped()->m_net_object) + 0x3D8); // TODO: extract offset
				if (net_id)
					entity::force_remove_network_entity(net_id);
			}
		}
	};

	delete_vehicle g_delete_vehicle("deleteveh", "BACKEND_DELETE_VEHICLE", "BACKEND_DELETE_VEHICLE_DESC", 0);
}
