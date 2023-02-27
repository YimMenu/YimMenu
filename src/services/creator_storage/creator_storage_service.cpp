#include "creator_storage_service.hpp"

#include "gta/joaat.hpp"
#include "gta/sysMemAllocator.hpp"
#include "gta/tls_context.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "script_function.hpp"

namespace big
{
	std::vector<std::string> creator_storage_service::list_files()
	{
		std::vector<std::string> file_paths;

		const auto file_path = check_jobs_folder();
		for (const auto& directory_entry : std::filesystem::directory_iterator(file_path.get_path()))
			if (directory_entry.path().extension() == ".json")
				file_paths.push_back(directory_entry.path().filename().generic_string());

		return file_paths;
	}

	std::ofstream creator_storage_service::create_file(std::string file)
	{
		return std::ofstream(check_jobs_folder().get_file(file).get_path());
	}

	void creator_storage_service::save_file(std::string_view filename)
	{
		std::ofstream file(check_jobs_folder().get_file(filename).get_path());

		while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(RAGE_JOAAT("fm_race_creator")))
		{
			SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(RAGE_JOAAT("fm_race_creator"));
			script::get_current()->yield();
		}

		char* storage = new char[0x50000];
		scr_functions::save_to_datafile.static_call({(uint64_t)storage});
		delete[] storage;

		SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(RAGE_JOAAT("fm_race_creator"));

		auto buffer = g_pointers->m_save_json_data(g_pointers->m_main_file_object, nullptr, "to save it to a file I guess?");

		if (!buffer)
		{
			g_notification_service->push_error("CREATOR_STORAGE_SAVE_JOB"_T.data(),
			    "CREATOR_STORAGE_CANNOT_OBTAIN_JSON"_T.data());
			return;
		}

		file << buffer;
		file.close();

		rage::tlsContext::get()->m_allocator->Free(buffer);
	}

	void creator_storage_service::load_file(std::string_view file_name)
	{
		const auto file = check_jobs_folder().get_file(file_name);

		std::ifstream file_stream(file.get_path());
		std::string buffer(std::istreambuf_iterator<char>{file_stream}, {});

		if (DATAFILE::DATAFILE_GET_FILE_DICT(0) != nullptr)
			DATAFILE::DATAFILE_DELETE(0);

		sCloudFile* cloud_file = nullptr;
		g_pointers->m_load_cloud_file(&cloud_file, buffer.data(), buffer.length(), "to load it from a file I guess?");
		g_pointers->m_set_as_active_cloud_file(g_pointers->m_main_file_object, &cloud_file);

		while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(RAGE_JOAAT("fm_race_creator")))
		{
			SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(RAGE_JOAAT("fm_race_creator"));
			script::get_current()->yield();
		}

		scr_functions::load_from_datafile.static_call({1, true, false, 0});

		SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(RAGE_JOAAT("fm_race_creator"));
		file_stream.close();
	}

	big::folder creator_storage_service::check_jobs_folder()
	{
		const auto folder = g_file_manager->get_project_folder("./jobs");

		return folder;
	}
}
