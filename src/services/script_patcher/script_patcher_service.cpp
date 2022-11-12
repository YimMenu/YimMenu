#include "common.hpp"
#include "script_patcher_service.hpp"
#include <script/scrProgram.hpp>
#include <memory/pattern.hpp>

namespace big
{
	void script_patch::enable(script_data* data)
	{
		std::memcpy(get_code_address(data, m_ip), m_patch.data(), m_patch.size());
	}

	void script_patch::disable(script_data* data)
	{
		std::memcpy(get_code_address(data, m_ip), m_original.data(), m_original.size());
	}

	script_patch::script_patch(rage::joaat_t script, const memory::pattern pattern, int32_t offset, std::vector<std::uint8_t> patch, bool* enable_bool) :
		m_script(script),
		m_pattern(pattern),
		m_offset(offset),
		m_patch(std::move(patch)),
		m_bool(enable_bool),
		m_ip(0)
	{
	}

	void script_patch::update(script_data* data)
	{
		if (m_ip == 0)
		{
			auto result = get_code_location_by_pattern(data, m_pattern);
			if (!result.has_value())
				LOG(FATAL) << "Failed to find pattern";

			m_ip = result.value() + m_offset;

			for (int i = 0; i < m_patch.size(); i++)
				m_original.push_back(*get_code_address(data, m_ip + i));
		}

		if (!m_bool || *m_bool)
			enable(data);
		else
			disable(data);
	}

	script_data* script_patcher_service::get_data_for_script(rage::joaat_t script)
	{
		for (auto& p : m_script_data)
		{
			if (p.first == script)
			{
				return p.second.get();
			}
		}

		return nullptr;
	}

	bool script_patcher_service::does_script_have_patches(rage::joaat_t script)
	{
		for (auto& p : m_script_patches)
		{
			if (p.m_script == script)
				return true;
		}

		return false;
	}

	void script_patcher_service::create_data_for_script(rage::scrProgram* program)
	{
		auto pages = new std::uint8_t * [program->get_num_code_pages()];

		for (auto i = 0u; i < program->get_num_code_pages(); i++)
		{
			pages[i] = new std::uint8_t[program->get_code_page_size(i)];
			std::memcpy(pages[i], program->get_code_page(i), program->get_code_page_size(i));
		}

		m_script_data.emplace(program->m_name_hash, std::make_unique<script_data>(program->m_code_size, pages, program->get_num_code_pages()));
	}

	void script_patcher_service::update_all_patches_for_script(rage::joaat_t script)
	{
		auto data = get_data_for_script(script);

		for (auto& p : m_script_patches)
			if (p.m_script == script)
				p.update(data);
	}

	void script_patcher_service::add_patch(script_patch&& patch)
	{
		m_script_patches.push_back(std::move(patch));
	}

	void script_patcher_service::on_script_load(rage::scrProgram* program)
	{
		if (get_data_for_script(program->m_name_hash) == nullptr && does_script_have_patches(program->m_name_hash))
		{
			create_data_for_script(program);
			update_all_patches_for_script(program->m_name_hash);
		}
	}

	std::uint8_t** script_patcher_service::get_script_bytecode(rage::joaat_t script)
	{
		if (auto data = get_data_for_script(script))
			return data->m_bytecode;

		return nullptr;
	}

	void script_patcher_service::update()
	{
		for (auto& p : m_script_patches)
		{
			auto data = get_data_for_script(p.m_script);
			if (data)
			{
				p.update(data);
			}
		}
	}
}