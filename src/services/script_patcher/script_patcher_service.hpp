#pragma once
#include <script/scrProgram.hpp>
#include "memory/pattern.hpp"

namespace big
{
	struct script_data
	{
		std::uint32_t m_num_pages;

	public:
		std::uint32_t m_code_size;
		std::uint8_t** m_bytecode;

		script_data(std::uint32_t code_size, std::uint8_t** bytecode, std::uint32_t num_pages) :
			m_code_size(code_size),
			m_bytecode(bytecode),
			m_num_pages(num_pages)
		{
		}

		~script_data()
		{
			for (auto i = 0u; i < m_num_pages; i++)
			{
				delete[] m_bytecode[i];
			}

			delete[] m_bytecode;
		}
	};

	class script_patch
	{
		friend class script_patcher_service;

		rage::joaat_t m_script;
		const memory::pattern m_pattern;
		int32_t m_offset;
		std::vector<uint8_t> m_patch;
		std::vector<uint8_t> m_original;
		bool* m_bool;
		int32_t m_ip;

		static std::uint8_t* get_code_address(script_data* data, std::uint32_t index)
		{
			return &data->m_bytecode[index >> 14][index & 0x3FFF];
		}

		static const std::optional<uint32_t> get_code_location_by_pattern(script_data* data, const memory::pattern& pattern)
		{
			std::uint32_t code_size = data->m_code_size;
			for (std::uint32_t i = 0; i < (code_size - pattern.m_bytes.size()); i++)
			{
				for (std::uint32_t j = 0; j < pattern.m_bytes.size(); j++)
					if (pattern.m_bytes[j].has_value())
						if (pattern.m_bytes[j].value() != *get_code_address(data, i + j))
							goto incorrect;

				return i;
incorrect:
				continue;
			}

			return std::nullopt;
		}

		void enable(script_data* data);
		void disable(script_data* data);

	public:
		script_patch(rage::joaat_t script, const memory::pattern pattern, int32_t offset, std::vector<std::uint8_t> patch, bool* enable_bool);
		void update(script_data* data);
	};

	class script_patcher_service
	{
		std::vector<script_patch> m_script_patches;
		std::unordered_map<rage::joaat_t, std::unique_ptr<script_data>> m_script_data;
		script_data* get_data_for_script(rage::joaat_t script);
		bool does_script_have_patches(rage::joaat_t script);
		void create_data_for_script(rage::scrProgram* program);
		void update_all_patches_for_script(rage::joaat_t script);

	public:
		void add_patch(script_patch&& patch);
		void on_script_load(rage::scrProgram* program);
		std::uint8_t** get_script_bytecode(rage::joaat_t script);
		void update();
	};

	inline script_patcher_service g_script_patcher_service;
}