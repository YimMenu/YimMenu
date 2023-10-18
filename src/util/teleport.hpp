#pragma once
#include "blip.hpp"
#include "core/data/remote_player_teleport.hpp"
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
		Vector3 coord = {self::pos.x, self::pos.y + 1.f, self::pos.z + 1.f};

		if (!*g_pointers->m_gta.m_is_session_started)
			return g_notification_service->push_warning("Teleport", "Session has not started");

		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());

		auto hnd = vehicle::spawn(VEHICLE_RCBANDITO, *player->get_ped()->get_position(), 0.0f, true);

		if (!hnd && !g_pointers->m_gta.m_handle_to_ptr(hnd)->m_net_object)
			return g_notification_service->push_warning("Teleport", "Failed bcz unable to spawn RCBANDITO at player location.");

		ENTITY::SET_ENTITY_VISIBLE(hnd, false, false);
		ENTITY::SET_ENTITY_COLLISION(hnd, false, false);
		ENTITY::FREEZE_ENTITY_POSITION(hnd, true);

		if (ENTITY::IS_ENTITY_DEAD(ent, true))
			return g_notification_service->push_warning("Teleport", "Player is dead, you can't teleport them.");

		if (player->is_valid())
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(ent, false) || PLAYER::IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(player->id()))
			{
				g_notification_service->push_success("Teleport", std::format("Player {} is in vehicle", player->get_name()));

				ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

				if (entity::take_control_of(ent))
				{
					g_notification_service->push_success("Teleport",
					    std::format("Trying to teleport {} with vehicle", player->get_name()));
					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, coord.x, coord.y, coord.z, 0, 0, 0);
				}
				else
					g_notification_service->push_warning("Teleport", "Failed to take control of player vehicle.");
			}
			else
			{
				auto obj_id                      = player->get_ped()->m_net_object->m_object_id;
				auto veh_id                      = g_pointers->m_gta.m_handle_to_ptr(hnd)->m_net_object->m_object_id;
				remote_player_teleport remote_tp = {obj_id, {coord.x, coord.y, coord.z}};
				m_remote_player_teleports.emplace(veh_id, remote_tp);

				if (PED::IS_PED_IN_ANY_VEHICLE(ent, false) || PLAYER::IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(player->id()))
					g_pointers->m_gta.m_clear_ped_tasks_network(player->get_ped(), true);

				for (int i = 0; i < 30; i++)
				{
					script::get_current()->yield(25ms);

					if (auto ptr = (rage::CDynamicEntity*)g_pointers->m_gta.m_handle_to_ptr(hnd))
						if (auto netobj = ptr->m_net_object)
							g_pointers->m_gta.m_migrate_object(player->get_net_game_player(), netobj, 3);

					auto new_coords = ENTITY::GET_ENTITY_COORDS(hnd, true);
					if (SYSTEM::VDIST2(coord.x, coord.y, coord.z, new_coords.x, new_coords.y, new_coords.z) < 20 * 20 && VEHICLE::GET_PED_IN_VEHICLE_SEAT(hnd, 0, true) == ent)
						break;
				}

				std::erase_if(m_remote_player_teleports, [veh_id](auto& obj) {
					return obj.first == veh_id;
				});
			}
			entity::delete_entity(hnd);
		}
	}

	inline void into_vehicle(Vehicle veh)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh))
			return g_notification_service->push_warning("Teleport", "Invalid Vehicle");

		for (int i = -1; i < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(veh); i++)
			if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i, true))
			{
				Vector3 location = ENTITY::GET_ENTITY_COORDS(veh, true);
				entity::load_ground_at_3dcoord(location);
				ENTITY::SET_ENTITY_COORDS(self::ped, location.x, location.y, location.z, 0, 0, 0, 0);
				script::get_current()->yield();
				PED::SET_PED_INTO_VEHICLE(self::ped, veh, i);
				return;
			}

		g_notification_service->push_warning("Teleport", "No seat available");
	}

	inline void to_coords(Vector3 location, bool load_ground = false)
	{
		if (load_ground)
			entity::load_ground_at_3dcoord(location);

		auto yaw   = ENTITY::GET_ENTITY_HEADING(self::ped);
		auto pitch = CAM::GET_GAMEPLAY_CAM_RELATIVE_PITCH();
		auto roll  = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();

		PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, location.x, location.y, location.z + 1.f);

		if (self::veh)
		{
			ENTITY::SET_ENTITY_HEADING(self::veh, yaw);
			CAM::SET_GAMEPLAY_CAM_RELATIVE_PITCH(pitch, 1.f);
			CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(roll);
		}
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
