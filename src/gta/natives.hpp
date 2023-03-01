#pragma once
#include "fwddec.hpp"

#include <cstdint>
#include <script/types.hpp>
#include <utility>

namespace rage
{
	class scrNativeCallContext
	{
	public:
		void reset()
		{
			m_arg_count  = 0;
			m_data_count = 0;
		}

		template<typename T>
		void push_arg(T&& value)
		{
			static_assert(sizeof(T) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<T>>*>(reinterpret_cast<std::uint64_t*>(m_args) + (m_arg_count++)) = std::forward<T>(value);
		}

		template<typename T>
		T& get_arg(std::size_t index)
		{
			static_assert(sizeof(T) <= sizeof(std::uint64_t));
			return *reinterpret_cast<T*>(reinterpret_cast<std::uint64_t*>(m_args) + index);
		}

		template<typename T>
		void set_arg(std::size_t index, T&& value)
		{
			static_assert(sizeof(T) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<T>>*>(reinterpret_cast<std::uint64_t*>(m_args) + index) = std::forward<T>(value);
		}

		template<typename T>
		T* get_return_value()
		{
			return reinterpret_cast<T*>(m_return_value);
		}

		template<typename T>
		void set_return_value(T&& value)
		{
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<T>>*>(m_return_value) = std::forward<T>(value);
		}

		template<typename T>
		void set_return_value(T& value)
		{
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<T>>*>(m_return_value) = std::forward<T>(value);
		}

	protected:
		void* m_return_value;
		std::uint32_t m_arg_count;
		void* m_args;
		std::int32_t m_data_count;
		std::uint32_t m_data[48];
	};
	static_assert(sizeof(scrNativeCallContext) == 0xE0);
	using scrNativeHash    = std::uint64_t;
	using scrNativeMapping = std::pair<scrNativeHash, scrNativeHash>;
	using scrNativeHandler = void (*)(scrNativeCallContext*);

	class scrNativeRegistration
	{
	public:
		uint64_t m_nextRegistration1;
		uint64_t m_nextRegistration2;
		void* m_handlers[7];
		uint32_t m_numEntries1;
		uint32_t m_numEntries2;
		uint64_t m_hashes;
		scrNativeRegistration* get_next_registration()
		{
			std::uintptr_t result;
			auto nextReg         = uintptr_t(&m_nextRegistration1);
			auto newReg          = nextReg ^ m_nextRegistration2;
			auto charTableOfRegs = (char*)&result - nextReg;
			for (auto i = 0; i < 3; i++)
			{
				*(DWORD*)&charTableOfRegs[nextReg] = static_cast<DWORD>(newReg) ^ *(DWORD*)nextReg;
				nextReg += 4;
			}
			return reinterpret_cast<scrNativeRegistration*>(result);
		}
		std::uint32_t get_num_entries()
		{
			return static_cast<std::uint32_t>(((std::uintptr_t)&m_numEntries1) ^ m_numEntries1 ^ m_numEntries2);
		}
		std::uint64_t get_hash(std::uint32_t index)
		{
			auto nativeAddress = 16 * index + std::uintptr_t(&m_nextRegistration1) + 0x54;
			std::uint64_t result;
			auto charTableOfRegs = (char*)&result - nativeAddress;
			auto addressIndex    = nativeAddress ^ *(DWORD*)(nativeAddress + 8);
			for (auto i = 0; i < 3; i++)
			{
				*(DWORD*)&charTableOfRegs[nativeAddress] = static_cast<DWORD>(addressIndex ^ *(DWORD*)(nativeAddress));
				nativeAddress += 4;
			}
			return result;
		}
	};

#pragma pack(push, 1)
	class scrNativeRegistrationTable
	{
		scrNativeRegistration* m_entries[0xFF];
		std::uint32_t m_unk;
		bool m_initialized;
	};
#pragma pack(pop)
}