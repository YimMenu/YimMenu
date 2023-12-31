#pragma once

namespace big
{
	class vtable_hook
	{
	public:
		explicit vtable_hook(void** vft, std::size_t num_funcs);
		~vtable_hook();

		vtable_hook(vtable_hook&& that)            = delete;
		vtable_hook& operator=(vtable_hook&& that) = delete;
		vtable_hook(vtable_hook const&)            = delete;
		vtable_hook& operator=(vtable_hook const&) = delete;

		void hook(std::size_t index, void* func);
		void unhook(std::size_t index);

		template<typename T>
		T get_original(std::size_t index);

		inline void** get_original_table()
		{
			return m_backup_table.get();
		}

		void enable();
		void disable();

	private:
		std::size_t m_num_funcs;
		void** m_table;
		std::unique_ptr<void*[]> m_backup_table;
		std::unique_ptr<void*[]> m_hook_table;
	};

	template<typename T>
	inline T vtable_hook::get_original(std::size_t index)
	{
		return static_cast<T>(m_backup_table[index]);
	}

}
