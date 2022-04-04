#pragma once

namespace big
{
	class pe_image final
	{
		const std::string_view m_path;
		const char* const m_target = "ScriptHookV.dll";

		std::vector<char> m_file_buffer;
		const IMAGE_NT_HEADERS64* nt_header = nullptr;

	public:
		pe_image(const std::string_view path)
			: m_path(path)
		{

		}
		~pe_image() = default;

		bool load()
		{
			std::ifstream input(m_path.data(), std::ios::binary);
			if (input.fail())
				return false;
			
			m_file_buffer = { std::istreambuf_iterator(input), std::istreambuf_iterator<char>() };
			input.close();

			return verify_header_n_load();
		}

		[[nodiscard]] bool is_openvhook_compatible() const
		{
			auto* import_table = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(
				get_directory_address(IMAGE_DIRECTORY_ENTRY_IMPORT)
			);

			for (; import_table->Name; ++import_table)
				if (const auto* dll_name = (const char*)rva_to_va(import_table->Name); strcmp(dll_name, m_target) == 0)
					return false;

			return true;
		}

		[[nodiscard]] bool patch_image() const
		{
			auto* import_table = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(
				get_directory_address(IMAGE_DIRECTORY_ENTRY_IMPORT)
			);

			for (; import_table->Name; ++import_table)
			{
				if (auto* dll_name = reinterpret_cast<char*>(rva_to_va(import_table->Name)); strcmp(dll_name, m_target) == 0)
				{
					ZeroMemory(dll_name, strlen(dll_name));
					strcpy(dll_name, "BigBaseV2.dll");
					
					std::ofstream file(m_path.data(), std::ios::binary | std::ios::out);
					file.write(m_file_buffer.data(), m_file_buffer.size());
					file.close();

					return true;
				}
			}

			return false;
		}

	private:
		[[nodiscard]] uint64_t get_directory_address(const int index) const
		{
			const auto* data_directory = nt_header->OptionalHeader.DataDirectory;

			return rva_to_va(data_directory[index].VirtualAddress);
		}

		[[nodiscard]] uint64_t rva_to_va(const uint32_t rva) const
		{
			const auto* sectionHeader = reinterpret_cast<const IMAGE_SECTION_HEADER*>(nt_header + 1);
			for (int i = 0; i < nt_header->FileHeader.NumberOfSections; ++i, ++sectionHeader)
				if (rva >= sectionHeader->VirtualAddress && rva <= sectionHeader->VirtualAddress + sectionHeader->Misc.VirtualSize)
					return reinterpret_cast<uint64_t>(m_file_buffer.data()) + (rva - sectionHeader->VirtualAddress + sectionHeader->PointerToRawData);
			return 0;
		}

		/**
		 * @brief Check if the ASI has a valid DLL header and loads DLL header
		 */
		bool verify_header_n_load()
		{
			const auto* dos_header = reinterpret_cast<const IMAGE_DOS_HEADER*>(m_file_buffer.data());
			if (dos_header->e_magic != IMAGE_DOS_SIGNATURE)
				return false;
			
			nt_header = reinterpret_cast<const IMAGE_NT_HEADERS64*>(reinterpret_cast<const uint8_t*>(dos_header) + dos_header->e_lfanew);

			return true;
		}
	};
}