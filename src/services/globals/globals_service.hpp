#pragma once
#include "script_global.hpp"

namespace big
{
	struct global_offset
	{
		global_offset(nlohmann::json data)
		{
			m_offset = data["offset"];

			if (data.contains("size"))
				m_size = data["size"];
		}

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

		nlohmann::json to_json()
		{
			nlohmann::json j;

			j["offset"] = m_offset;
			if (m_size)
				j["size"] = m_size;

			return j;
		}

	private:
		int m_offset = 0;
		int m_size   = 0;
	};

	struct global
	{
		int m_base_address;
		bool m_freeze = false;
		std::string m_name;
		std::vector<global_offset> m_offsets;
		int m_value;

		global(nlohmann::json data)
		{
			m_internal_id = ++m_instance_count;

			m_base_address = data["base_address"];
			m_freeze       = data["freeze"];
			m_name         = data["name"];
			m_value        = data["value"];

			for (auto& offset : data["offsets"])
				m_offsets.push_back(global_offset(offset));
		}

		global(const char* name, const int base_address, const bool freeze, const int (*offsets)[2], int offset_count)
		{
			m_internal_id = ++m_instance_count;

			m_base_address = base_address;
			m_freeze       = freeze;
			m_name         = std::string(name);
			m_value        = 0;

			for (int i = 0; i < offset_count; i++)
				m_offsets.push_back(global_offset(offsets[i][0], offsets[i][1]));
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

		nlohmann::json to_json()
		{
			nlohmann::json j;

			j["base_address"] = m_base_address;
			j["freeze"]       = m_freeze;
			j["name"]         = m_name;
			j["value"]        = m_value;

			j["offsets"] = nlohmann::json::array();
			for (auto& offset : m_offsets)
				j["offsets"].push_back(offset.to_json());

			return j;
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

	class globals_service
	{
		const char* file_location = "\\BigBaseV2\\globals.json";

	public:
		globals_service();
		~globals_service();

		bool load();
		void loop();
		void save();

		std::vector<global> m_globals;
		bool m_running = false;
		;

	private:
		void build(nlohmann::json& data);
	};

	inline globals_service* g_globals_service{};
}