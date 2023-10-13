#pragma once
#include "blip.hpp"
#include "core/settings.hpp"
#include "entity.hpp"
#include "gta/enums.hpp"
#include "gta/net_object_mgr.hpp"
#include "services/notifications/notification_service.hpp"
#include "services/players/player_service.hpp"
#include "vehicle.hpp"

namespace big::teleport
{
	inline void bring_player(player_ptr player)
	{
		if (!*g_pointers->m_gta.m_is_session_started)
		{
			g_notification_service->push_warning("Teleport", "Session has not started");
			return;
		}

		Entity ent     = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
		Vector3 coords = self::pos;

		if (ENTITY::IS_ENTITY_DEAD(ent, true))
		{
			g_notification_service->push_warning("Teleport", "Player is dead, you can't teleport them.");
			return;
		}

		if (PED::IS_PED_IN_ANY_VEHICLE(ent, true))
		{
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, coords.x, coords.y, coords.z, TRUE, TRUE, TRUE);
			else
				g_notification_service->push_warning("Teleport", "Failed to take control of entity.");
		}
		else
		{
			auto hnd = vehicle::spawn(VEHICLE_RCBANDITO, *player->get_ped()->get_position(), 0.0f, true);

			if (!hnd && !g_pointers->m_gta.m_handle_to_ptr(hnd)->m_net_object)
			{
				g_notification_service->push_warning("Teleport", "Failed!");
				return;
			}

			ENTITY::SET_ENTITY_VISIBLE(hnd, false, false);
			ENTITY::SET_ENTITY_COLLISION(hnd, false, false);
			ENTITY::FREEZE_ENTITY_POSITION(hnd, true);

			auto obj_id                      = player->get_ped()->m_net_object->m_object_id;
			auto veh_id                      = g_pointers->m_gta.m_handle_to_ptr(hnd)->m_net_object->m_object_id;
			remote_player_teleport remote_tp = {obj_id, {coords.x, coords.y, coords.z}};
			g.m_remote_player_teleports.emplace(veh_id, remote_tp);

			if ((player->is_valid() && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), false))
			    || PLAYER::IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(player->id()))
				g_pointers->m_gta.m_clear_ped_tasks_network(player->get_ped(), true);

			for (int i = 0; i < 30; i++)
			{
				script::get_current()->yield(25ms);

				if (auto ptr = (rage::CDynamicEntity*)g_pointers->m_gta.m_handle_to_ptr(hnd))
					if (auto netobj = ptr->m_net_object)
						g_pointers->m_gta.m_migrate_object(player->get_net_game_player(), netobj, 3);

				auto new_coords = ENTITY::GET_ENTITY_COORDS(hnd, true);
				if (SYSTEM::VDIST2(coords.x, coords.y, coords.z, new_coords.x, new_coords.y, new_coords.z) < 20 * 20 && VEHICLE::GET_PED_IN_VEHICLE_SEAT(hnd, 0, true) == ent)
					break;
			}

			entity::delete_entity(hnd);

			std::erase_if(g.m_remote_player_teleports, [veh_id](auto& obj) {
				return obj.first == veh_id;
			});

			return;
		}
	}

	inline bool into_vehicle(Vehicle veh)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh))
		{
			g_notification_service->push_warning("Teleport", "Invalid Vehicle");
			return false;
		}

		int seat_index = 255;

		if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -1, true))
			seat_index = -1;
		else if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -2, true))
			seat_index = -2;

		if (seat_index == 255)
		{
			g_notification_service->push_warning("Teleport", "There are no seats available in this vehicle for you.");
			return false;
		}

		Vector3 location = ENTITY::GET_ENTITY_COORDS(veh, true);
		entity::load_ground_at_3dcoord(location);

		ENTITY::SET_ENTITY_COORDS(self::ped, location.x, location.y, location.z, 0, 0, 0, 0);

		script::get_current()->yield();

		PED::SET_PED_INTO_VEHICLE(self::ped, veh, seat_index);

		return true;
	}

	inline void to_coords(Vector3 location, bool load_ground = false)
	{
		if (load_ground)
			entity::load_ground_at_3dcoord(location);

		PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, location.x, location.y, location.z + 1.f);
	}

	inline bool to_blip(int sprite, int color = -1)
	{
		Vector3 location;

		if (!blip::get_blip_location(location, sprite, color))
			return false;

		to_coords(location, sprite == (int)BlipIcons::Waypoint);

		return true;
	}

	inline void to_player(Player player)
	{
		Vector3 location = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), true);
		to_coords(location);
	}

	inline bool to_waypoint()
	{
		if (!to_blip((int)BlipIcons::Waypoint))
		{
			g_notification_service->push_warning("Teleport", "No waypoint found.");
			return false;
		}
		return true;
	}

	inline bool to_objective()
	{
		Vector3 location;

		if (!blip::get_objective_location(location))
		{
			g_notification_service->push_warning("Teleport", "No objective found.");
			return false;
		}

		to_coords(location, true);
		return true;
	}
}
