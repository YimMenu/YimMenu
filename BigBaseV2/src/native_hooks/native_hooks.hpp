#pragma once
#include "gta/joaat.hpp"
#include "gta/script_thread.hpp"
#include "script_hook.hpp"

namespace big
{
	class native_hooks final
	{
		using native_detour = std::pair<rage::scrNativeHash, rage::scrNativeHandler>;

		std::map<rage::joaat_t, std::vector<native_detour>> m_native_registrations;
		std::map<rage::joaat_t, std::unique_ptr<script_hook>> m_script_hooks;

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

		/**
		 * @brief Check if this thread requires us to hook anything
		 * 
		 * @param gta_thread A GtaThread pointer to hook natives from
		 * @return true If we detoured a function
		 * @return false If no functions have been detoured
		 */
		bool check_for_thread(const GtaThread* gta_thread);
		/**
		 * @brief If a GtaThread terminates call this function to remove the unused script_hook
		 * 
		 * @param gta_thread 
		 */
		void do_cleanup_for_thread(const GtaThread* gta_thread);
	};

	inline native_hooks* g_native_hooks{};
}