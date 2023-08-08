#pragma once
#include "base.hpp"
#include "fwddec.hpp"
#include "joaat.hpp"
#include "script/scriptIdBase.hpp"

#include <cstdint>

#pragma pack(push, 1)
namespace rage
{
	class scrProgram : public pgBase
	{
	public:
		uint8_t** m_code_blocks; // 0x10
		uint32_t m_hash;         // 0x18
		uint32_t m_code_size;    // 0x1C
		uint32_t m_arg_count;    // 0x20
		uint32_t m_local_count;  // 0x24
		uint32_t m_global_count; // 0x28
		uint32_t m_native_count; // 0x2C
		void* m_local_data;           // 0x30
		std::int64_t** m_global_data; // 0x38
		void** m_native_entrypoints;  // 0x40
		char m_padding6[0x10];        // 0x48
		uint32_t m_name_hash;    // 0x58
		char m_padding7[0x04];        // 0x5C
		const char* m_name;           // 0x60
		const char** m_strings_data;  // 0x68
		uint32_t m_strings_count;// 0x70
		char m_padding8[0x0C];        // 0x74

		bool is_valid() const
		{
			return m_code_size != 0;
		}

		uint32_t get_num_code_pages() const
		{
			return (m_code_size + 0x3FFF) >> 14;
		}

		uint32_t get_code_page_size(uint32_t page) const
		{
			auto num = get_num_code_pages();
			if (page < num)
			{
				if (page == num - 1)
					return m_code_size & 0x3FFF;
				return 0x4000;
			}

			return 0;
		}

		uint32_t get_full_code_size() const
		{
			auto numPages = get_num_code_pages();
			if (!numPages)
				return 0;
			if (numPages == 1)
				--numPages;

			return (numPages * 0x4000) + (m_code_size & 0x3FFF);
		}

		uint8_t* get_code_page(uint32_t page) const
		{
			return m_code_blocks[page];
		}

		uint8_t* get_code_address(uint32_t index) const
		{
			if (index < m_code_size)
				return &m_code_blocks[index >> 14][index & 0x3FFF];

			return nullptr;
		}

		const char* get_string(uint32_t index) const
		{
			if (index < m_strings_count)
				return &m_strings_data[index >> 14][index & 0x3FFF];

			return nullptr;
		}

		void** get_address_of_native_entrypoint(void* entrypoint)
		{
			for (uint32_t i = 0; i < m_native_count; ++i)
			{
				if (m_native_entrypoints[i] == entrypoint)
				{
					return m_native_entrypoints + i;
				}
			}

			return nullptr;
		}
	};

	class scrProgramTableEntry
	{
	public:
		scrProgram* m_program;// 0x00
		char m_Pad1[0x04];    // 0x08
		joaat_t m_hash;       // 0x0C
	};

	class scrProgramTable
	{
	public:
		scrProgramTableEntry* m_data;// 0x00
		char m_padding[0x10];        // 0x08
		uint32_t m_size;        // 0x18

		std::list<joaat_t> all_script_hashes()
		{
			std::list<rage::joaat_t> hash;

			for (uint32_t i = 0; i < m_size; ++i)
			{
				if (m_data[i].m_program != nullptr && m_data[i].m_program->m_name != nullptr)
				{
					hash.push_back(m_data[i].m_hash);
				}
			}
			return hash;
		}

		std::list<std::string> all_script_names()
		{
			std::list<std::string> hash;

			for (uint32_t i = 0; i < m_size; ++i)
			{
				if (m_data[i].m_program != nullptr && m_data[i].m_program->m_name != nullptr)
				{
					hash.push_back(m_data[i].m_program->m_name);
				}
			}
			return hash;
		}

		scrProgram* find_script(joaat_t hash)
		{
			for (uint32_t i = 0; i < m_size; ++i)
			{
				if (m_data[i].m_hash == hash)
				{
					return m_data[i].m_program;
				}
			}

			return nullptr;
		}

		scrProgramTableEntry* begin()
		{
			return m_data;
		}

		scrProgramTableEntry* end()
		{
			return m_data + m_size;
		}
	};

	static_assert(sizeof(scrProgram) == 0x80);
	static_assert(sizeof(scrProgramTableEntry) == 0x10);
	static_assert(sizeof(scrProgramTable) == 0x1C);
}
#pragma pack(pop)
