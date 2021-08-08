#include "vehicle_service.hpp"

namespace big
{
	vehicle_service::vehicle_service()
	{
		g_vehicle_service = this;
	}

	vehicle_service::~vehicle_service()
	{
		g_vehicle_service = nullptr;
	}

	int vehicle_service::attempt_save()
	{
		if (g_local_player == nullptr || g_local_player->m_in_vehicle == 0x10 || g_local_player->m_vehicle == nullptr)
			return -1;
		if (m_handling_backup.find(g_local_player->m_vehicle->m_handling->m_model_hash) != m_handling_backup.end())
			return 0;

		CHandlingData handling = *g_local_player->m_vehicle->m_handling;

		m_handling_backup.emplace(g_local_player->m_vehicle->m_handling->m_model_hash, handling);

		return 1;
	}

	bool vehicle_service::restore_vehicle()
	{
		if (auto it = m_handling_backup.find(g_local_player->m_vehicle->m_handling->m_model_hash); it != m_handling_backup.end())
		{
			*g_local_player->m_vehicle->m_handling = it->second;

			return true;
		}

		return false;
	}
}