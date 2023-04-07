#include "locals_service.hpp"
#include "core/data/all_script_names.hpp"

namespace big{

    locals_service::locals_service()
	{
		g_globals_service = this;
	}

	locals_service::~locals_service()
	{
		g_globals_service = nullptr;

		m_running = false;

		this->save();
	}

    bool locals_service::is_script_thread_running(GtaThread* thread){
        if(thread)
        {
            return thread->m_context.m_state == rage::eThreadState::running;
        }
        return false;
    }

    bool locals_service::does_script_exist(std::string script_name){
        for(auto s : all_script_names)
            if(script_name == s) return true;
        return false;
    }

    bool locals_service::load()
	{
		std::string path = std::getenv("appdata");
		path += this->file_location;

		std::ifstream file(path);

		if (!file.is_open())
			return false;

		try
		{
			nlohmann::json j;
			j << file;

			//IMPLEMENT LOADING LOCALS
		}
		catch (const std::exception&)
		{
			LOG(WARNING) << "Failure to parse locals.json, aborting...";

			return false;
		}

		return true;
	}

    void locals_service::loop()
	{
		while (m_running)
			for (auto& local : m_locals)
				if (local.m_freeze)
					local.write();
	}

	void locals_service::save()
	{

        std::map<std::string, local> locals_with_names;
        for (auto& l : m_locals){
            locals_with_names.insert(std::pair<std::string, local>(
                l.m_name.empty() ?  std::string(l.m_script_thread_name).append("_").append(std::to_string(l.m_base_address)) : l.m_name, l));
        }
        
		nlohmann::json j;
        for(auto& l : locals_with_names){
            j[l.first]["script_thread_name"] = l.second.m_script_thread_name;
            j[l.first]["base_address"] = l.second.m_base_address;
            j[l.first]["freeze"] = l.second.m_freeze;
            j[l.first]["name"] = l.second.m_name;
            j[l.first]["value"] = l.second.m_value;

            for (int i = 0; i < l.second.m_offsets.size(); i++)
            {
                j[l.first]["offsets"][std::to_string(i)]["offset"] = l.second.m_offsets[i].m_offset;
                if(l.second.m_offsets[i].m_size > 0) j[l.first]["offsets"][std::to_string(i)]["size"] = l.second.m_offsets[i].m_size;
            };
        }

		std::string path = std::getenv("appdata");
		path += this->file_location;
		std::ofstream file(path, std::ios::out | std::ios::trunc);

		try
		{
			file << j.dump(4);

			file.close();
		}
		catch (const std::exception&)
		{
			LOG(WARNING) << "Failed to write to locals.json";
		}
	}

};