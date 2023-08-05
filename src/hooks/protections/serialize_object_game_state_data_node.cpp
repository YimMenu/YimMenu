#include "gta/net_game_event.hpp"
#include "hooking.hpp"
#include "util/notify.hpp"

namespace big
{
	void hooks::serialize_object_game_state_data_node(__int64 node, rage::CSyncDataBase* data)
	{
		if (data->m_type == rage::CSyncDataBase::Type::Reader)
		{
			auto buffer = *data->m_buffer;
			if (buffer.Read<bool>(1))
			{
				auto task_type = buffer.Read<uint32_t>(10);
				auto size      = buffer.Read<uint32_t>(8);

				if (size > 150)
				{
					notify::crash_blocked(g.m_syncing_player, "object game state array overflow");
					LOG(INFO) << size;
					//return;
				}
			}
		}

		g_hooking->get_original<hooks::serialize_object_game_state_data_node>()(node, data);
	}
}
