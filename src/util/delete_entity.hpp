#pragma once
#include "mobile.hpp"
#include "natives.hpp"
#include "vehicle.hpp"

namespace big::entity
{
	inline void delete_entity(Entity& ent)
	{
		if (ent && ENTITY::DOES_ENTITY_EXIST(ent) && take_control_of(ent))
		{
			if (ENTITY::IS_ENTITY_A_VEHICLE(ent) && *g_pointers->m_gta.m_is_session_started)
			{
				if (Vehicle personal_vehicle = mobile::mechanic::get_personal_vehicle(); personal_vehicle == ent)
					return;

				vehicle::clear_all_peds(ent);
			}

			if (ENTITY::IS_ENTITY_ATTACHED(ent))
				ENTITY::DETACH_ENTITY(ent, 0, 0);

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, 7000.f, 7000.f, 15.f, 0, 0, 0);

			if (!ENTITY::IS_ENTITY_A_MISSION_ENTITY(ent))
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ent, true, true);
			ENTITY::DELETE_ENTITY(&ent);

			if (ENTITY::DOES_ENTITY_EXIST(ent))
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ent);
		}
		else
			g_notification_service->push_error("Deletion failed", std::format("For entity {}", ent));
	}
}