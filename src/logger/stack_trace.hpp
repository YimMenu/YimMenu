#pragma once
#include "common.hpp"

namespace big
{
	class stack_trace
	{
	public:
		stack_trace();
		virtual ~stack_trace();

		const std::vector<uint64_t>& frame_pointers();
		void new_stack_trace(EXCEPTION_POINTERS* exception_info);
		std::string str() const;

		friend std::ostream& operator<<(std::ostream& os, const stack_trace& st);
		friend std::ostream& operator<<(std::ostream& os, const stack_trace* st);

	private:
		struct module_info
		{
			module_info(std::filesystem::path path, void* base) :
			    m_name(path.filename().string()),
			    m_base(reinterpret_cast<uintptr_t>(base))
			{
				const auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
				const auto nt_header  = reinterpret_cast<IMAGE_NT_HEADERS*>(m_base + dos_header->e_lfanew);

				m_size = nt_header->OptionalHeader.SizeOfCode;
			}

			std::string m_name;
			uintptr_t m_base;
			size_t m_size;
		};

	private:
		void dump_module_info();
		void dump_registers();
		void dump_stacktrace();
		void dump_script_info();
		void dump_cpp_exception();
		void grab_stacktrace();
		const module_info* get_module_by_address(uint64_t addr) const;

		static std::string exception_code_to_string(const DWORD code);

	private:
		EXCEPTION_POINTERS* m_exception_info;

		std::stringstream m_dump;
		std::vector<uint64_t> m_frame_pointers;

		inline static std::vector<module_info> m_modules;
	};

	inline std::ostream& operator<<(std::ostream& os, const stack_trace& st)
	{
		os << st.str();

		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const stack_trace* st)
	{
		os << st->str();

		return os;
	}
}