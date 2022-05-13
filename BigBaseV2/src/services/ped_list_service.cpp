#include "api/remote.hpp"
#include "fiber_pool.hpp"
#include "file_manager.hpp"
#include "gui.hpp"
#include "thread_pool.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"
#include "ped_list_service.hpp"

namespace big
{
	ped_list_service::ped_list_service() :
		m_ped_file(g_file_manager->get_project_file("./lib/peds.json"))
	{
		if (m_ped_file.exists())
			this->load();
		else
		{
			g_thread_pool->push([this]()
				{
					if (remote::download_binary("http://github-proxy.damon.sh/DurtyFree/gta-v-data-dumps/master/peds.json", m_ped_file.get_path()))
						this->load();
					else
						LOG(WARNING) << "Failed to download peds.json data...";
				});
		}

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

	void ped_list_service::load()
	{
		std::ifstream file(m_ped_file.get_path());

		try
		{
			file >> m_all_peds;
		}
		catch (const std::exception& ex)
		{
			LOG(WARNING) << "Failed to load peds.json:\n" << ex.what();
		}
	}
}