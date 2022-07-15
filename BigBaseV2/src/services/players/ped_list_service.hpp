#pragma once
#include "file_manager/file.hpp"

namespace big
{
	class ped_list_service
	{
		file m_ped_file;
		file m_ped_file_etag;

		std::condition_variable m_cond;
		std::mutex m_mutex;

		nlohmann::json m_all_peds;

		std::vector<std::string> m_pedtype_arr;
	public:
		ped_list_service();
		~ped_list_service();

		nlohmann::json& get_ped_list();

		std::vector<std::string>& get_pedtype_arr();
	private:
		void load();

	};

	inline ped_list_service* g_ped_list_service{};
}