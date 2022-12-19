#include "hooking.hpp"
#include "gta/net_game_event.hpp"
#include "util/notify.hpp"
#include <datanodes/dynamic_entity/CDynamicEntityGameStateDataNode.hpp>

namespace big
{
	constexpr uint32_t NULL_INTERIOR = 0x0FFFCFFFF;

	void hooks::serialize_dynamic_entity_game_state_data_node(CDynamicEntityGameStateDataNode* node, rage::CSyncDataBase* data)
	{
		data->SerializeBool(&node->unk_00C5);
		if (node->unk_00C5 && !data->IsSizeCalculator())
		{
			data->SerializeDwordAlt(&node->m_interior_index, 32);
		}
		else
		{
			bool is_null_interior = node->m_interior_index == NULL_INTERIOR;
			data->SerializeBool(&is_null_interior);

			if (!is_null_interior || data->IsSizeCalculator())
			{
				data->SerializeDwordAlt(&node->m_interior_index, 32);
			}
			else
			{
				node->m_interior_index = NULL_INTERIOR;
			}
		}

		data->SerializeBool(&node->unk_00C4);

		bool has_decors = node->m_decor_count != 0;
		data->SerializeBool(&has_decors);

		if (has_decors || data->IsSizeCalculator())
		{
			data->SerializeDwordAlt(&node->m_decor_count, 4);

			if (data->IsSizeCalculator())
				node->m_decor_count = 11;

			if (node->m_decor_count > 11)
			{
				notify::crash_blocked(g.m_syncing_player, "out of bounds decorator count");
				return;
			}

			for (uint32_t i = 0; i < node->m_decor_count; i++)
			{
				data->SerializeDwordAlt(&node->m_decors[i].m_type, 3);
				data->SerializeDwordAlt(&node->m_decors[i].m_value, 32);
				data->SerializeDwordAlt(&node->m_decors[i].m_name_hash, 32);
			}
		}
	}
}