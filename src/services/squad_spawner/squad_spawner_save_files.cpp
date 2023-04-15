#include "squad_spawner.hpp"

namespace big
{

	std::filesystem::path squad_spawner::get_file_path()
	{
		return g_file_manager->get_project_folder("SquadSpawner").get_path();
	}

	bool squad_spawner::fetch_squads()
	{
		m_templates.clear();
		std::ifstream read;
		try
		{
			for (const auto& path : std::filesystem::directory_iterator(get_file_path()))
			{
				nlohmann::json j;
				if (path.path().extension() == ".json")
				{
					read.open(path.path(), std::ifstream::in);
					if (read.is_open())
					{
						read >> j;
						read.close();
					}
					//TODO ADD FROM JSON TO SQUAD STRUCT
				}
			}
            return true;
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Squad Spawner fetching files failed: " << e.what();
		}

        return false;
	}

    bool squad_spawner::save_squad(squad s){

        for(auto s_ : m_templates) if(strcmp(s_.m_name, s.m_name) == 0 ) return false;

        std::ofstream write;
		std::string savename = s.m_name; 
        savename.append(".json");
        std::filesystem::path path = get_file_path() / savename;

        write.open(path, std::ofstream::out | std::ofstream::trunc);
        try{
            if(write.is_open()){
                //TODO ADD TO JSON FROM SQUAD STRUCT
                write.close();
                return true;
            }
        }catch(std::exception e){
            LOG(WARNING) << "Squad Spawner saving squad failed: " << e.what();
        }

        return false;

    }

}