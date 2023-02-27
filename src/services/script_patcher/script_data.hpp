#pragma once

namespace big
{
	class script_data
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

		script_data(const script_data& that)            = delete;
		script_data& operator=(const script_data& that) = delete;

		~script_data()
		{
			for (auto i = 0u; i < m_num_pages; i++)
			{
				delete[] m_bytecode[i];
			}

			delete[] m_bytecode;
			m_bytecode = nullptr;
		}
	};
}