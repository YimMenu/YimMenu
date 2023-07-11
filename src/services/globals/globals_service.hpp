#pragma once
#include "script_global.hpp"

namespace big
{
	struct global_offset
	{
		int m_offset = 0;
		int m_size   = 0;

		global_offset() = default;
		global_offset(int offset, int size = 0)
		{
			m_offset = offset;

			if (size)
				m_size = size;
		}

		script_global apply(script_global internal_cache)
		{
			return m_size ? internal_cache.at(m_offset, m_size) : internal_cache.at(m_offset);
		}
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(global_offset, m_offset, m_size)

	struct global
	{
		int m_base_address;
		bool m_freeze = false;
		std::string m_name;
		std::vector<global_offset> m_offsets;
		int m_value;

		global() = default;
		global(const char* name, const int base_address, const bool freeze, const int (*offsets)[2], int offset_count) :
			m_name(name),
			m_base_address(base_address),
			m_freeze(freeze)
		{
			m_internal_id = ++m_instance_count;

			for (int i = 0; i < offset_count; ++i)
			{
				const auto offset = offsets[i];
				m_offsets.push_back({ offset[0], offset[1] });
			}
		}

		void build_cache()
		{
			script_global internal_cache(m_base_address);

			for (auto& offset : m_offsets)
				internal_cache = offset.apply(internal_cache);

			m_internal_addr = internal_cache.as<int*>();
		}

		int* get()
		{
			if (m_freeze)
				return &m_value;
			return m_internal_addr;
		}

		int get_id()
		{
			return m_internal_id;
		}

		void set(int value)
		{
			m_value = value;
			if (!m_freeze)
				this->write();
		}

		void write()
		{
			*m_internal_addr = m_value;
		}

	private:
		inline static int m_instance_count;

		int m_internal_id;
		int* m_internal_addr;
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(global, m_base_address, m_freeze, m_offsets, m_name, m_value)

	using global_vec = std::vector<global>;
	class globals_service
	{
		file m_globals_file;

	public:
		globals_service();
		~globals_service();

		bool load();
		void loop();
		void save();

		global_vec m_globals;
		bool m_running = false;

	private:
		void build();

	};

	inline auto g_globals_service = globals_service();
}