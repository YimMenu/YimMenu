#pragma once
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace memory
{
	class handle
	{
	public:
		handle(void* ptr = nullptr);
		explicit handle(std::uintptr_t ptr);

		template <typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> as();

		template <typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> as();

		template <typename T>
		std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> as();

		template <typename T>
		handle add(T offset);

		template <typename T>
		handle sub(T offset);

		handle rip();

		explicit operator bool();

		friend bool operator==(handle a, handle b);
		friend bool operator!=(handle a, handle b);
	private:
		void* ptr;
	};

	inline handle::handle(void* ptr) :
		ptr(ptr)
	{}

	inline handle::handle(std::uintptr_t ptr) :
		ptr(reinterpret_cast<void*>(ptr))
	{}

	template <typename T>
	inline std::enable_if_t<std::is_pointer_v<T>, T> handle::as()
	{
		return static_cast<T>(ptr);
	}

	template <typename T>
	inline std::enable_if_t<std::is_lvalue_reference_v<T>, T> handle::as()
	{
		return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(ptr);
	}

	template <typename T>
	inline std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> handle::as()
	{
		return reinterpret_cast<std::uintptr_t>(ptr);
	}

	template <typename T>
	inline handle handle::add(T offset)
	{
		return handle(as<std::uintptr_t>() + offset);
	}

	template <typename T>
	inline handle handle::sub(T offset)
	{
		return handle(as<std::uintptr_t>() - offset);
	}

	inline handle handle::rip()
	{
		return add(as<std::int32_t&>()).add(4);
	}

	inline bool operator==(handle a, handle b)
	{
		return a.ptr == b.ptr;
	}

	inline bool operator!=(handle a, handle b)
	{
		return a.ptr != b.ptr;
	}

	inline handle::operator bool()
	{
		return ptr != nullptr;
	}
}
