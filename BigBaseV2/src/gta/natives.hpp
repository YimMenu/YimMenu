#pragma once
#include <cstdint>
#include <utility>
#include "fwddec.hpp"
#include "vector.hpp"

namespace rage
{
	class scrNativeCallContext
	{
	public:
		void reset()
		{
			m_arg_count = 0;
			m_data_count = 0;
		}

		template <typename T>
		void push_arg(T &&value)
		{
			static_assert(sizeof(T) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<T>>*>(reinterpret_cast<std::uint64_t*>(m_args) + (m_arg_count++)) = std::forward<T>(value);
		}

		template <typename T>
		T &get_arg(std::size_t index)
		{
			static_assert(sizeof(T) <= sizeof(std::uint64_t));
			return *reinterpret_cast<T*>(reinterpret_cast<std::uint64_t*>(m_args) + index);
		}

		template <typename T>
		void set_arg(std::size_t index, T &&value)
		{
			static_assert(sizeof(T) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<T>>*>(reinterpret_cast<std::uint64_t*>(m_args) + index) = std::forward<T>(value);
		}

		template <typename T>
		T *get_return_value()
		{
			return reinterpret_cast<T*>(m_return_value);
		}

		template <typename T>
		void set_return_value(T &&value)
		{
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<T>>*>(m_return_value) = std::forward<T>(value);
		}
	protected:
		void *m_return_value;
		std::uint32_t m_arg_count;
		void *m_args;
		std::int32_t m_data_count;
		std::uint32_t m_data[48];
	};

	using scrNativeHash = std::uint64_t;
	using scrNativeMapping = std::pair<scrNativeHash, scrNativeHash>;
	using scrNativeHandler = void(*)(scrNativeCallContext*);

	class scrNativeRegistration;

#pragma pack(push, 1)
	class scrNativeRegistrationTable
	{
		scrNativeRegistration *m_entries[0xFF];
		std::uint32_t m_unk;
		bool m_initialized;
	};
#pragma pack(pop)

	static_assert(sizeof(scrNativeCallContext) == 0xE0);
}

using Void = void;
using Any = int;
using Hash = std::uint32_t;
using Entity = std::int32_t;
using Player = std::int32_t;
using FireId = std::int32_t;
using Interior = std::int32_t;
using Ped = Entity;
using Vehicle = Entity;
using Cam = std::int32_t;
using Object = Entity;
using Pickup = Object;
using Blip = std::int32_t;
using Camera = Entity;
using ScrHandle = Entity;
using Vector3 = rage::scrVector;
