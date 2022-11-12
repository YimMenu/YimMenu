#pragma once
#include "gta/joaat.hpp"
#include "gta/script_thread.hpp"
#include "script_hook.hpp"

namespace big
{
	class native_hooks final
	{
		using native_detour = std::pair<rage::scrNativeHash, rage::scrNativeHandler>;

		std::unordered_map<rage::joaat_t, std::vector<native_detour>> m_native_registrations;
		std::unordered_map<rage::scrProgram*, std::unique_ptr<script_hook>> m_script_hooks;

	public:
		native_hooks();
		~native_hooks();

		native_hooks(const native_hooks&) = delete;
		native_hooks(native_hooks&&) noexcept = delete;
		native_hooks& operator=(const native_hooks&) = delete;
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

		void unhook_program(rage::scrProgram* program);
	};

	inline native_hooks* g_native_hooks{};
}