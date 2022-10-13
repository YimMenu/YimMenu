#pragma once
#include "wren.hpp"
#include "wren_script.hpp"

namespace big
{
	class wren_manager
	{
		static constexpr auto Script_class_name = "Script";
		static constexpr auto Script_yield_method_name = "yield()";
		static constexpr auto Script_yield_ms_arg_method_name = "yield(_)";
		static constexpr auto Script_trigger_script_event_method_name = "tse(_,_)";

		static constexpr auto natives_module_name = "natives";
		static constexpr auto SCRIPT_INTERNAL_class_name = "SCRIPT_INTERNAL";
		static constexpr auto SCRIPT_INTERNAL_TICK_method_name = "TICK()";

		WrenConfiguration m_config;

		WrenVM* m_vm;

		folder m_scripts_folder;
		std::filesystem::path m_scripts_wren_folder;

		std::unordered_map<std::string, std::unique_ptr<wren_script>> m_wren_scripts;

		bool m_has_tick_function = false;
		WrenHandle* m_script_internal_class_handle = nullptr;
		WrenHandle* m_script_internal_tick_fn_handle = nullptr;

		static WrenForeignMethodFn wren_bind_foreign_method(
			WrenVM* vm,
			const char* module, const char* class_name,
			bool is_static,
			const char* signature);

		void cleanup_memory();

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
