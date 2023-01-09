#pragma once
#include "natives.hpp"

namespace big
{
	class creator_storage_service
	{
	public:
		static std::vector<std::string> list_files();

		static std::ofstream create_file(std::string name);
		static void load_file(std::string_view file_name);
		static void save_file(std::string_view file_name);

	private:
		static big::folder check_jobs_folder();
	};
}