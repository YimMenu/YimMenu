#include "gta/net_game_event.hpp"
#include "hooking.hpp"
#include "util/notify.hpp"

#include <netsync/nodes/ped/CPedTaskSpecificDataNode.hpp>

namespace big
{
	void hooks::serialize_ped_task_specific_data_node(CPedTaskSpecificDataNode* node, rage::CSyncDataBase* data)
	{
		if (data->IsSizeCalculator())
			node->m_buffer_size = 602;

		data->SerializeDwordAlt(&node->m_buffer_size, 10);

		if (data->m_type == rage::CSyncDataBase::Type::Reader && node->m_buffer_size > 602)
		{
			notify::crash_blocked(g.m_syncing_player, "ped task specific array overflow");
			return;
		}

		if (node->m_buffer_size && node->m_buffer_size <= 602)
			data->SerializeArray(node->m_task_data_buffer, node->m_buffer_size);
	}
}