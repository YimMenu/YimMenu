#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "pointers.hpp"
#include "util/vehicle.hpp"
#include "util/mobile.hpp"
#include "gta_util.hpp"

namespace big
{

	class blackhole : looped_command
	{
		using looped_command::looped_command;

		std::vector<Entity> target_entities;

		void get_entities()
		{            
			const auto replay_interface = *g_pointers->m_replay_interface;
			if(!replay_interface)
				return;
	
			if (g.world.blackhole.include_vehicles)
			{
				const auto vehicle_interface = replay_interface->m_vehicle_interface;
				for (int i = 0; i < vehicle_interface->m_max_vehicles; i++)
				{
					const auto vehicle_ptr = vehicle_interface->get_vehicle(i);
					if (!vehicle_ptr)
						continue;

					const auto veh = g_pointers->m_ptr_to_handle(vehicle_ptr);
					if (!veh)
						break;

					target_entities.push_back(veh);
				}
			}

			if (g.world.blackhole.include_peds)
			{
				const auto ped_interface = replay_interface->m_ped_interface;
				for (int i = 0; i < ped_interface->m_max_peds; i++)
				{
					const auto ped_ptr = ped_interface->get_ped(i);
					if (!ped_ptr)
						continue;

					//make sure to don't include ourselves
					if (ped_ptr == gta_util::get_local_ped())
						continue;

					const auto ped = g_pointers->m_ptr_to_handle(ped_ptr);
					if (!ped)
						break;

					target_entities.push_back(ped);
				}
			}
		}

		virtual void on_tick() override
		{
			get_entities();

			for (auto entity : target_entities)
			{
				auto entity_coord = ENTITY::GET_ENTITY_COORDS(entity, false);
				ENTITY::APPLY_FORCE_TO_ENTITY(entity, 1, ((g.world.blackhole.pos.x - entity_coord.x) * 9.f), ((g.world.blackhole.pos.y - entity_coord.y) * 9.f), ((g.world.blackhole.pos.z - entity_coord.z) * 9.f), 0.f, 0.f, 0.f, 0, false, true, true, 0, 0);
			}

			//draw blackhole
			GRAPHICS::DRAW_MARKER(28,
				g.world.blackhole.pos.x, g.world.blackhole.pos.y, g.world.blackhole.pos.z,
				0.f, 0.f, 0.f, 0, 0, 0, 15.f, 15.f, 15.f,
				g.world.blackhole.color[0] * 255,
				g.world.blackhole.color[1] * 255,
				g.world.blackhole.color[2] * 255,
				g.world.blackhole.alpha,
				0, 0, 0, 0, 0, 0, 0);
			
			//cleanup
			target_entities.clear();
		}

		//make sure that we always cleanup our memory
		virtual void on_disable() override
		{
			target_entities.clear();
		}
	};
	
	blackhole g_blackhole("blackhole", "Blackhole", "Spawns a black hole that picks up all the peds and vehicles in your area.", g.world.blackhole.enable);
}