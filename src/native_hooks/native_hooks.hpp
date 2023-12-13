#pragma once
#include "gta/joaat.hpp"
#include "gta/script_thread.hpp"
#include "vmt_hook.hpp"

namespace big
{
	class native_hook final
	{
	public:
		explicit native_hook(rage::scrProgram* program, const std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler>& native_replacements);
		~native_hook();

	private:
		void hook_instance(rage::scrProgram* program, const std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler>& native_replacements);
		static void scrprogram_dtor(rage::scrProgram* this_, char free_memory);

		rage::scrProgram* m_program;
		std::unique_ptr<vmt_hook> m_vmt_hook;
		std::unique_ptr<vmt_hook> m_handler_hook;
	};

	class native_hooks final
	{
		friend class native_hook;

		using native_detour = std::pair<rage::scrNativeHash, rage::scrNativeHandler>;

		std::unordered_map<rage::joaat_t, std::vector<native_detour>> m_native_registrations;
		std::unordered_map<rage::scrProgram*, std::unique_ptr<native_hook>> m_native_hooks;

	public:
		native_hooks();
		~native_hooks();

		native_hooks(const native_hooks&)                = delete;
		native_hooks(native_hooks&&) noexcept            = delete;
		native_hooks& operator=(const native_hooks&)     = delete;
		native_hooks& operator=(native_hooks&&) noexcept = delete;

		/**
		 * @brief Add a detour for all script threads
		 * 
		 * @param hash Hash of the native to detour
		 * @param detour Detour Function
		 */
		void add_native_detour(rage::scrNativeHash hash, rage::scrNativeHandler detour);
		/**
		 * @brief Add a detour for a specifik script
		 * 
		 * @param script_hash Hash of the script to detour
		 * @param hash Hash of the native to detour
		 * @param detour Detour Function
		 */
		void add_native_detour(rage::joaat_t script_hash, rage::scrNativeHash hash, rage::scrNativeHandler detour);

		void hook_program(rage::scrProgram* program);
	};

	inline native_hooks* g_native_hooks{};
}