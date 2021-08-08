#pragma once
#include "common.hpp"

namespace big
{
	class vehicle_service
	{
	public:
		vehicle_service();
		~vehicle_service();

		int attempt_save();
		bool restore_vehicle();
	private:
		inline static std::unordered_map<Hash, CHandlingData> m_handling_backup;
	};

	inline vehicle_service* g_vehicle_service;
}