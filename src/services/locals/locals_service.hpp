#pragma once

#include "file_manager.hpp"
#include "file_manager/file.hpp"
#include "gta/script_thread.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"

namespace big
{

	struct local_offset
	{
		local_offset(int offset, int size = 0)
		{
			m_offset = offset;

			if (size)
				m_size = size;
		}

		int m_offset = 0;
		int m_size   = 0;
	};


	struct local
	{
		GtaThread* m_script_thread;
		char m_script_thread_name[200];
		int m_base_address;
		bool m_freeze = false;
		char m_name[200];
		std::vector<local_offset> m_offsets;
		int m_value;
		int m_freeze_value_int;
		float m_freeze_value_float;
		Vector3 m_freeze_value_vector3;
		int* m_internal_address;
		Vector3* m_internal_address_vector3;
		int m_edit_mode = 0;

		local(const char* script_thread_name, const char* name, const int base_address, const bool freeze, const int (*offsets)[2], int offset_count, int edit_mode = 0)
		{
			m_internal_id = ++m_instance_count;

			strcpy(m_script_thread_name, script_thread_name);
			m_base_address = base_address;
			m_freeze       = freeze;
			strcpy(m_name, name);
			m_value = 0;

			for (int i = 0; i < offset_count; i++)
				m_offsets.push_back(local_offset(offsets[i][0], offsets[i][1]));

			m_edit_mode = edit_mode;

			fetch_local_pointer();
		}

		int get_id() const
		{
			return m_internal_id;
		}

		int* fetch_local_pointer()
		{
			m_script_thread = gta_util::find_script_thread(rage::joaat(m_script_thread_name));

			if (m_script_thread)
			{
				script_local actual_local = script_local(m_script_thread, m_base_address);

				for (auto& offset : m_offsets)
				{
					if (offset.m_size > 0)
						actual_local = actual_local.at(offset.m_offset, offset.m_size);
					else
						actual_local = actual_local.at(offset.m_offset);
				}

				m_internal_address         = actual_local.as<int*>();
				m_internal_address_vector3 = actual_local.as<Vector3*>();

				return m_internal_address;
			}
			return nullptr;
		}

		const char* get_local_chain_text()
		{
			static char offsetschain[200] = "";
			strcpy(offsetschain, "");
			strcat(offsetschain, std::to_string(m_base_address).data());
			for (auto o : m_offsets)
			{
				strcat(offsetschain, std::string(".f_" + std::to_string(o.m_offset)).data());
				if (o.m_size)
					strcat(offsetschain, std::string("/" + std::to_string(o.m_size)).data());
			}
			return offsetschain;
		}

	private:
		inline static int m_instance_count;
		int m_internal_id;
	};


	class locals_service
	{
	public:
		std::filesystem::path get_path();
		bool load();
		void save();

		static bool does_script_exist(std::string script);
		static bool is_script_thread_running(GtaThread* thread);

		std::vector<local> m_locals;
		bool m_running = false;
	};

	inline locals_service g_locals_service{};
}