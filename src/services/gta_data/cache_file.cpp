#include "cache_file.hpp"

namespace big
{
	cache_file::cache_file(file cache_file) :
	    m_cache_file(cache_file),
	    m_data(nullptr),
	    m_cache_version(0),
	    m_cache_header()
	{
	}

	cache_file::cache_file(file cache_file, uint32_t cache_version) :
	    m_cache_file(cache_file),
	    m_data(nullptr),
	    m_cache_version(cache_version),
	    m_cache_header()
	{
	}

	void cache_file::free()
	{
		m_data.reset();
	}

	bool cache_file::load()
	{
		if (!m_cache_file.exists())
			return false;
		if (m_data)
			return true;

		auto file = std::ifstream(m_cache_file.get_path(), std::ios::binary);

		file.read(reinterpret_cast<char*>(&m_cache_header), sizeof(m_cache_header));

		m_data = std::make_unique<uint8_t[]>(m_cache_header.m_data_size);
		file.read(reinterpret_cast<char*>(m_data.get()), m_cache_header.m_data_size);

		file.close();
		return true;
	}

	bool cache_file::write() const
	{
		if (!m_data)
			return false;

		auto file = std::ofstream(m_cache_file.get_path(), std::ios::binary);

		file.write(reinterpret_cast<const char*>(&m_cache_header), sizeof(m_cache_header));
		file.write(reinterpret_cast<const char*>(m_data.get()), m_cache_header.m_data_size);
		file.close();

		return true;
	}

	uint8_t* cache_file::data() const
	{
		return m_data.get();
	}

	uint64_t cache_file::data_size() const
	{
		return m_cache_header.m_data_size;
	}

	bool cache_file::up_to_date(uint32_t file_version) const
	{
		if (!m_data)
			return false;

		return m_cache_version == m_cache_header.m_cache_version && file_version == m_cache_header.m_file_version;
	}

	void cache_file::set_data(cache_data&& data, uint64_t data_size)
	{
		m_data.swap(data);
		m_cache_header.m_data_size = data_size;
	}

	void cache_file::set_header_version(uint32_t file_version)
	{
		m_cache_header.m_cache_version = m_cache_version;
		m_cache_header.m_file_version  = file_version;
	}

	void cache_file::set_cache_version(uint32_t cache_version)
	{
		m_cache_version = cache_version;
	}
}
