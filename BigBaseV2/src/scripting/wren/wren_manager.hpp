#pragma once
#include "wren.hpp"
#include "wren_script.hpp"

namespace big
{
	class wren_manager
	{
		WrenConfiguration m_config;

		WrenVM* m_vm;

		folder m_scripts_folder;
		std::filesystem::path m_scripts_wren_folder;

		std::unordered_map<std::string, std::unique_ptr<wren_script>> m_wren_scripts;

	public:
		wren_manager();
		~wren_manager();

		void for_each_wren_script_file(std::function<void(const std::string& module_name, const std::filesystem::path& file_path, const std::filesystem::directory_entry& dir_entry)> cb);

		void remove_all_scripts();

		void reload_scripts();

		void compile_script(const std::string& module_name, const std::filesystem::path& file_path, const std::filesystem::file_time_type& disk_last_write_time);

		static void tick_all_scripts();
	};

	inline wren_manager* g_wren_manager{};
}
