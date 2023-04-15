#include "squad_spawner.hpp"
#include "util/entity.hpp"

namespace big
{

	void squad_spawner::terminate_squads()
	{
		for (auto& s : m_active_squads)
		{
			if (entity::take_control_of(s.m_veh_handle))
			{
				entity::delete_entity(s.m_veh_handle);
			}

			for (auto& m : s.m_members)
			{
				if (entity::take_control_of(m.handle))
				{
					entity::delete_entity(m.handle);
				}
			}
		}
	}

}