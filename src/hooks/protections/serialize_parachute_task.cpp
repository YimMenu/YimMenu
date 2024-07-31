#include "hooking/hooking.hpp"
#include "util/notify.hpp"

#include <entities/CDynamicEntity.hpp>

namespace big
{
#pragma pack(push, 8)
	struct TaskObject
	{
		uint16_t m_net_id;
		rage::CDynamicEntity* m_entity;
	};
#pragma pack(pop)

	void hooks::serialize_parachute_task(__int64 info, rage::CSyncDataBase* serializer)
	{
		auto object = reinterpret_cast<TaskObject*>(info + 0x30);
		g_hooking->get_original<hooks::serialize_parachute_task>()(info, serializer);

		if (object->m_entity && object->m_entity->m_entity_type != 5) [[unlikely]]
		{
			g_pointers->m_gta.m_remove_reference(object->m_entity, &object->m_entity);
			notify::crash_blocked(g.m_syncing_player, "invalid parachute object type");
			object->m_entity = nullptr;
			object->m_net_id = 0;
		}
	}
}
