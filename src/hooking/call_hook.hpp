#pragma once
#include "common.hpp"
#include "memory/handle.hpp"

namespace big
{
	class call_hook_memory
	{
		memory::handle m_memory;
		int m_offset;

	public:
		call_hook_memory();
		~call_hook_memory();

		void* allocate_jump_sequence(void* func);
	};

	class call_hook
	{
	public:
		explicit call_hook(void* location, void* hook);
		~call_hook();

		call_hook(call_hook&& that)            = delete;
		call_hook& operator=(call_hook&& that) = delete;
		call_hook(call_hook const&)            = delete;
		call_hook& operator=(call_hook const&) = delete;

		template<typename T>
		T get_original();

		void enable();
		void disable();

	private:
		void* m_location;
		void* m_hook;
		uint8_t m_patched_bytes[5];
		uint8_t m_original_bytes[5];
		void* m_original_function;
	};

	template<typename T>
	inline T call_hook::get_original()
	{
		return static_cast<T>(m_original_function);
	}
}
