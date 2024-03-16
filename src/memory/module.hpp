#pragma once
#include "range.hpp"

namespace memory
{
	class module : public range
	{
	public:
		explicit module(const std::string_view name);

		/**
		 * @brief Get the export address of the current module given a symbol name
		 * 
		 * @param symbol_name 
		 * @return memory::handle 
		 */
		memory::handle get_export(std::string_view symbol_name);

		bool loaded() const;
		size_t size() const;
		DWORD timestamp() const;

		/**
		 * @brief Waits till the given module is loaded.
		 * 
		 * @param time Time to wait before giving up.
		 * @return true 
		 * @return false 
		 */
		bool wait_for_module(std::optional<std::chrono::high_resolution_clock::duration> time = std::nullopt);

	protected:
		bool try_get_module();

	private:
		const std::string_view m_name;
		bool m_loaded;
	};
}
