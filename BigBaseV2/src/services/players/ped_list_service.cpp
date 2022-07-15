#include "api/remote.hpp"
#include "fiber_pool.hpp"
#include "file_manager.hpp"
#include "thread_pool.hpp"
#include "ped_list_service.hpp"

namespace big
{
	ped_list_service::ped_list_service() :
		m_ped_file(g_file_manager->get_project_file("./lib/peds.json")),
		m_ped_file_etag(g_file_manager->get_project_file("./lib/peds_etag.txt"))
	{
		if (m_ped_file.exists())
		{
			this->load();
			LOG(INFO) << "Ped data loaded.";
		}
		
		g_thread_pool->push([this]()
		{
			bool rem = remote::update_binary("http://github-proxy.damon.sh/DurtyFree/gta-v-data-dumps/master/peds.json", m_ped_file.get_path(), m_ped_file_etag.get_path()
			);

			if (rem)
			{
				this->load();
				LOG(INFO) << "Vehicle data updated.";
			}
			else if (!m_ped_file.exists())
			{
				LOG(WARNING) << "Failed to download peds.json data...";
			}
		});
		
		g_ped_list_service = this;
	}

	ped_list_service::~ped_list_service()
	{
		g_ped_list_service = nullptr;
	}

	nlohmann::json& ped_list_service::get_ped_list()
	{
		return m_all_peds;
	}

	std::vector<std::string>& ped_list_service::get_pedtype_arr()
	{
		return m_pedtype_arr;
	}

	void ped_list_service::load()
	{
		std::ifstream file(m_ped_file.get_path());

		try
		{
			file >> m_all_peds;

			for (auto& item : m_all_peds)
			{
				if (item["Pedtype"].is_null())
					continue;
				if (!std::count(m_pedtype_arr.begin(), m_pedtype_arr.end(), item["Pedtype"]))
				{
					m_pedtype_arr.push_back(item["Pedtype"]);
				}
			}
		}
		catch (const std::exception& ex)
		{
			LOG(WARNING) << "Failed to load peds.json:\n" << ex.what();
		}
	}
}