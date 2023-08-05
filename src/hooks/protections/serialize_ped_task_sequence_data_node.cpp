#include "gta/net_game_event.hpp"
#include "hooking.hpp"
#include "util/notify.hpp"

#include <netsync/nodes/ped/CPedTaskSequenceDataNode.hpp>

namespace big
{
	void hooks::serialize_ped_task_sequence_data_node(CPedTaskSequenceDataNode* node, rage::CSyncDataBase* data)
	{
		data->SerializeBool(&node->m_has_sequence);
		if (node->m_has_sequence)
		{
			bool has_resource_id = node->m_sequence_resource_id != 0;
			data->SerializeBool(&has_resource_id);
			if (has_resource_id || data->IsSizeCalculator())
				data->SerializeDwordAlt((uint32_t*)&node->m_sequence_resource_id, 15);
			else
				node->m_sequence_resource_id = 0;

			if (data->IsSizeCalculator())
				node->m_num_tasks_in_sequence = 10;
			data->SerializeDwordAlt((uint32_t*)&node->m_num_tasks_in_sequence, 4);

			int num = node->m_num_tasks_in_sequence;
			if (num > 10)
				num = 10;

			for (int i = 0; i < num; i++)
			{
				data->SerializeDwordAlt((uint32_t*)&node->m_task_data[i].m_task_type, 10);
				if (data->IsSizeCalculator())
					node->m_task_data[i].m_task_data_size = 602;
				data->SerializeDwordAlt((uint32_t*)&node->m_task_data[i].m_task_data_size, 10);
				if (data->m_type == rage::CSyncDataBase::Type::Reader && node->m_task_data[i].m_task_data_size > 602)
				{
					notify::crash_blocked(g.m_syncing_player, "ped task sequence array overflow");
					return;
				}

				if (node->m_task_data[i].m_task_data_size <= 602)
					data->SerializeArray(&node->m_task_data[i].m_task_data, node->m_task_data[i].m_task_data_size);
			}

			if (node->m_num_tasks_in_sequence > 0)
				data->SerializeDword((uint32_t*)&node->m_unk, 1);
		}
	}
}