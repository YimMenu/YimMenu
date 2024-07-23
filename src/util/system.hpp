#pragma once
#include "file_manager.hpp"
#include "memory/module.hpp"
#include "pointers.hpp"

namespace big::system
{
	inline void dump_entry_points()
	{
		try
		{
			const auto hex_string_to_integer = [](const std::string& hex_str) -> uint64_t {
				uint64_t result;
				std::stringstream ss;
				ss << std::hex << hex_str;
				ss >> result;
				return result;
			};

			std::unordered_map<uint64_t, uint64_t> current_native_hash_to_original;
			{
				const auto crossmap_txt_file_path = g_file_manager.get_project_file("./crossmap.txt").get_path();
				auto crossmap_txt_file            = std::ifstream(crossmap_txt_file_path);
				if (!crossmap_txt_file.is_open())
				{
					LOG(FATAL) << "Need the crossmap.txt file from YimMenu repo. Put into %appdata%/YimMenu folder.";
					return;
				}

				std::string line;
				while (std::getline(crossmap_txt_file, line))
				{
					std::stringstream ss(line);
					std::string original, current;

					if (std::getline(ss, original, ',') && std::getline(ss, current, '\n'))
					{
						current_native_hash_to_original[hex_string_to_integer(current)] = hex_string_to_integer(original);
					}
				}

				crossmap_txt_file.close();
			}

			std::unordered_map<uint64_t, std::string> original_native_hash_to_name;
			{
				const auto native_json_file_path = g_file_manager.get_project_file("./natives.json").get_path();
				auto native_json_file            = std::ifstream(native_json_file_path);
				if (!native_json_file.is_open())
				{
					LOG(FATAL) << "Need the natives.json file from YimMenu repo. Put into %appdata%/YimMenu folder.";
					return;
				}
				nlohmann::json native_json = nlohmann::json::parse(native_json_file);

				for (auto& [native_namespace, natives] : native_json.items())
				{
					for (auto& [native_original_hash, native_info] : natives.items())
					{
						original_native_hash_to_name[hex_string_to_integer(native_original_hash)] = native_info["name"];
					}
				}

				native_json_file.close();
			}

			const auto file_path = g_file_manager.get_project_file("./entrypoints.txt");
			auto file            = std::ofstream(file_path.get_path(), std::ios::out | std::ios::trunc);

			for (size_t i = 0; i < g_crossmap.size(); i++)
			{
				const auto address = (uintptr_t)g_pointers->m_gta.m_get_native_handler(g_pointers->m_gta.m_native_registration_table, g_crossmap[i]);

				// clang-format off
			file <<
				original_native_hash_to_name[current_native_hash_to_original[g_crossmap[i]]] <<
				" | " <<
				std::hex << std::uppercase << (((DWORD64)address) - (DWORD64)GetModuleHandleA(0)) << std::dec << std::nouppercase <<
			std::endl;
				// clang-format on
			}

			file.close();
			LOG(INFO) << "Done dumping native entrypoints.";
		}
		catch (const std::exception& e)
		{
			LOG(FATAL) << e.what();
		}
		catch (...)
		{
			LOG(FATAL) << "Unknown exception.";
		}
	}

	inline uintptr_t get_relative_address(void* ptr)
	{
		uintptr_t base_address = memory::module("GTA5.exe").begin().as<uintptr_t>();

		return (uintptr_t)ptr - base_address;
	}
}