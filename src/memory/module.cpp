#include "module.hpp"

#include "../common.hpp"

namespace memory
{
	module::module(const std::string_view name) :range(nullptr, 0), m_name(name), m_loaded(false)
	{
		try_get_module();
	}

	handle module::get_export(std::string_view symbol_name)
	{
		if (!m_loaded)
			return nullptr;

		const auto dosHeader          = m_base.as<IMAGE_DOS_HEADER*>();
		const auto ntHeader           = m_base.add(dosHeader->e_lfanew).as<IMAGE_NT_HEADERS*>();
		const auto imageDataDirectory = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
		const auto exportDirectory    = m_base.add(imageDataDirectory.VirtualAddress).as<IMAGE_EXPORT_DIRECTORY*>();

		const auto nameOffsetArray     = m_base.add(exportDirectory->AddressOfNames).as<DWORD*>();
		const auto ordinalArray        = m_base.add(exportDirectory->AddressOfNameOrdinals).as<DWORD*>();
		const auto functionOffsetArray = m_base.add(exportDirectory->AddressOfFunctions).as<DWORD*>();

		for (std::size_t i = 0; i < exportDirectory->NumberOfFunctions; i++)
		{
			const auto functionName = m_base.add(nameOffsetArray[i]).as<const char*>();
			if (strcmp(functionName, symbol_name.data()))
				continue;

			return functionOffsetArray + ordinalArray[i];
		}
		return nullptr;
	}

	bool module::loaded() const
	{
		return m_loaded;
	}

	bool module::wait_for_module(std::optional<std::chrono::high_resolution_clock::duration> time)
	{
		const auto giveup_time = time.has_value() ? std::make_optional(std::chrono::high_resolution_clock::now() + time.value()) : std::nullopt;
		LOG(VERBOSE) << "Waiting for " << m_name << "...";
		while (!try_get_module())
		{
			if (giveup_time.has_value() && giveup_time <= std::chrono::high_resolution_clock::now())
				break;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		return m_loaded;
	}

	bool module::try_get_module()
	{
		if (m_loaded)
			return m_loaded;

		const auto mod = GetModuleHandleA(m_name.data());
		if (!mod)
			return false;
		m_loaded = true;

		m_base               = mod;
		const auto dosHeader = m_base.as<IMAGE_DOS_HEADER*>();
		const auto ntHeader  = m_base.add(dosHeader->e_lfanew).as<IMAGE_NT_HEADERS*>();

		m_size = ntHeader->OptionalHeader.SizeOfImage;

		return m_loaded;
	}
}
