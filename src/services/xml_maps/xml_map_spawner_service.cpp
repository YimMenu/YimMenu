#include "xml_map_spawner_service.hpp"
#include "natives.hpp"

namespace big
{
    xml_map_spawner_service::xml_map_spawner_service()
    {
        g_xml_map_spawner_service = this;
    }

    xml_map_spawner_service::~xml_map_spawner_service()
    {
        g_xml_map_spawner_service = nullptr;
    }

    void xml_map_spawner_service::fetch_xml_files()
    {
        auto folder_path = g_file_manager.get_project_folder("xml_maps").get_path();

        try
		{
			for (const auto& entry : std::filesystem::directory_iterator(folder_path))
			{
				if (entry.path().extension() == ".xml")
				{
					pugi::xml_document doc;
					pugi::xml_parse_result result = doc.load_file(entry.path().c_str());

					if (result)
						m_all_xml_maps.emplace(std::pair<std::string, pugi::xml_document>(entry.path().filename().generic_string(), std::move(doc)));
					else
						LOG(WARNING) << "Failed to load XML file: " << entry.path().filename().string() << std::endl;
				}
			}
		}
		catch (const std::exception& e)
		{
			LOG(WARNING) << "Failed fetching XML maps: " << e.what() << std::endl;
		}
    }

    void xml_map_spawner_service::spawn_from_xml(pugi::xml_document& doc)
    {
        auto root = doc.child("SpoonerPlacementes");
		auto ipls_to_unload = root.child("IPLsToRemove");
		auto ipls_to_load = root.child("IPLsToLoad");
		auto sp_maps = ipls_to_load.attribute("load_sp_maps").as_bool();
		auto mp_maps = ipls_to_load.attribute("load_mp_maps").as_bool();
		auto interiors = root.child("InteriorsToEnable");

        // Unload IPLs
		for(auto node = ipls_to_unload.first_child(); node; node = node.next_sibling())
		{
			auto name = (PCHAR)node.text().as_string();
			if(STREAMING::IS_IPL_ACTIVE(name))
				STREAMING::REMOVE_IPL(name);
		}

		if(sp_maps)
		{
			MISC::SET_INSTANCE_PRIORITY_MODE(true);
			DLC::ON_ENTER_SP();
		}

		if(mp_maps)
		{
			MISC::SET_INSTANCE_PRIORITY_MODE(true);
			DLC::ON_ENTER_MP();
		}



    }
}