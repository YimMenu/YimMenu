#pragma once
#include "file_manager/file.hpp"

namespace big
{
	class ped_list_service
	{
		file m_ped_file;

		nlohmann::json m_all_peds;

	public:
		ped_list_service();
		~ped_list_service();

		nlohmann::json& get_ped_list();

	private:
		void load();

	};

	inline ped_list_service* g_ped_list_service{};
}