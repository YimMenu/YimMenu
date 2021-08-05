#include "backend/looped/looped.hpp"
#include "gta/replay.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	static bool busy = false;

	void looped::protections_replay_interface()
	{
		if (busy) return;
		busy = true;

		Ped player = PLAYER::PLAYER_PED_ID();

		rage::CReplayInterface* replay_interface = *g_pointers->m_replay_interface;
		rage::CObjectInterface* object_interface = replay_interface->m_object_interface;

		const int max_obj = object_interface->m_max_objects;
		for (int i = 0; i < max_obj; i++)
		{
			rage::CObject* obj = object_interface->get_object(i);
			if (obj == nullptr) continue;

			Object ent = g_pointers->m_ptr_to_handle(obj);

			if (g.protections.replay_interface.attach)
			{
				if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(player, ent) || ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(player, true), ent))
				{
					entity::delete_entity(ent);
				}
			}

			if (g.protections.replay_interface.cage && obj->m_model_info->m_model == RAGE_JOAAT("prop_gold_cont_01"))
				entity::delete_entity(ent);

			script::get_current()->yield();
		}

		busy = false;
	}
}