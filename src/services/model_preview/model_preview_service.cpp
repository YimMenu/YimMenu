#include "model_preview_service.hpp"

#include "fiber_pool.hpp"
#include "gui.hpp"
#include "thread_pool.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"

namespace big
{
	model_preview_service::model_preview_service()
	{
		g_model_preview_service = this;
	}

	model_preview_service::~model_preview_service()
	{
		g_model_preview_service = nullptr;
	}

	void model_preview_service::show_ped(Hash hash)
	{
		m_ped_clone      = 0;
		m_veh_model_hash = 0;
		m_veh_owned_mods.clear();

		if (m_ped_model_hash != hash)
		{
			m_ped_model_hash = hash;

			if (m_ped_model_hash != 0)
			{
				m_new_model = true;

				preview_loop();
			}
		}
	}

	void model_preview_service::show_ped(Hash hash, Ped clone)
	{
		m_veh_model_hash = 0;
		m_veh_owned_mods.clear();

		if (m_ped_model_hash != hash || m_ped_clone != clone)
		{
			m_ped_model_hash = hash;
			m_ped_clone      = clone;

			if (m_ped_model_hash != 0)
			{
				m_new_model = true;

				preview_loop();
			}
		}
	}

	void model_preview_service::show_vehicle(Hash hash, bool spawn_max)
	{
		m_ped_model_hash = 0;
		m_ped_clone      = 0;
		m_veh_owned_mods.clear();

		if (m_veh_model_hash != hash || m_veh_spawn_max != spawn_max)
		{
			m_veh_model_hash = hash;

			if (m_veh_model_hash != 0)
			{
				m_veh_spawn_max = spawn_max;
				m_new_model     = true;

				preview_loop();
			}
		}
	}

	void model_preview_service::show_vehicle(const std::map<int, int32_t>& owned_mods, bool spawn_max)
	{
		m_ped_model_hash = 0;
		m_ped_clone      = 0;

		if (m_veh_spawn_max != spawn_max || m_veh_owned_mods.size() != owned_mods.size()
		    || !std::equal(m_veh_owned_mods.begin(), m_veh_owned_mods.end(), owned_mods.begin()))
		{
			m_veh_owned_mods.clear();

			auto hash_item = owned_mods.find(MOD_MODEL_HASH);

			m_veh_model_hash = hash_item->second;

			if (m_veh_model_hash != 0)
			{
				m_veh_owned_mods.insert(owned_mods.begin(), owned_mods.end());
				m_veh_spawn_max = spawn_max;
				m_new_model     = true;

				preview_loop();
			}
		}
	}

	void model_preview_service::preview_loop()
	{
		if (m_running || m_loop_running)
		{
			return;
		}

		m_running = true;

		g_fiber_pool->queue_job([this] {
			m_loop_running = true;

			while (g_running && m_running && g_gui->is_open() && (m_ped_model_hash || m_veh_model_hash))
			{
				Vector3 location;

				if (m_ped_model_hash)
				{
					location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.f, 5.f, -.5f);
				}
				else if (m_veh_model_hash)
				{
					location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.f, 10.f, .5f);
				}

				if (m_current_ent == 0)
				{
					m_new_model = false;
					location.z  = -10.f;

					if (m_ped_model_hash)
					{
						m_current_ent = ped::spawn(ePedType::PED_TYPE_ARMY, m_ped_model_hash, m_ped_clone, location, 0.f, false);

						ENTITY::SET_ENTITY_HEALTH(m_current_ent, 0, 0);
						script::get_current()->yield(20ms);
						PED::RESURRECT_PED(m_current_ent);
						TASK::CLEAR_PED_TASKS(m_current_ent);
					}
					else if (m_veh_model_hash)
					{
						if (m_veh_owned_mods.empty())
						{
							m_current_ent = vehicle::spawn(m_veh_model_hash, location, 0.f, false);
						}
						else
						{
							m_current_ent = vehicle::clone_from_owned_mods(m_veh_owned_mods, location, 0.f, false);
						}
					}

					if (m_current_ent)
					{
						if (m_veh_model_hash && m_veh_spawn_max)
						{
							vehicle::max_vehicle(m_current_ent);
						}

						ENTITY::FREEZE_ENTITY_POSITION(m_current_ent, true);
						ENTITY::SET_ENTITY_ALPHA(m_current_ent, 0, false);
						ENTITY::SET_ENTITY_COLLISION(m_current_ent, false, false);
						ENTITY::SET_CAN_CLIMB_ON_ENTITY(m_current_ent, false);
						OBJECT::SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY(m_current_ent, false);
					}
				}
				else if (m_new_model)
				{
					ENTITY::DETACH_ENTITY(m_current_ent, 1, 1);
					ENTITY::DELETE_ENTITY(&m_current_ent);
				}
				else
				{
					if (const int alpha = ENTITY::GET_ENTITY_ALPHA(m_current_ent); alpha < 255)
					{
						ENTITY::SET_ENTITY_ALPHA(m_current_ent, std::min<int>(255, alpha + 20), false);
					}

					ENTITY::SET_ENTITY_HEADING(m_current_ent, m_heading);
					ENTITY::SET_ENTITY_COORDS(m_current_ent, location.x, location.y, location.z, 0, 0, 0, 0);
				}

				if (m_heading += 0.5f; m_heading > 359)
				{
					m_heading = 0;
				}

				script::get_current()->yield(15ms);
			}

			ENTITY::DETACH_ENTITY(m_current_ent, 1, 1);
			ENTITY::DELETE_ENTITY(&m_current_ent);

			m_current_ent    = 0;
			m_ped_model_hash = 0;
			m_veh_model_hash = 0;
			m_veh_owned_mods.clear();
			m_running      = false;
			m_loop_running = false;
		});
	}

	void model_preview_service::stop_preview()
	{
		m_veh_owned_mods.clear();
		m_running = false;
	}
}
