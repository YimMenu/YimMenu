#pragma once
#include "fwddec.hpp"

namespace rage
{
	class sysMemAllocator
	{
	public:
		virtual ~sysMemAllocator() = 0;

		virtual void SetQuitOnFail(bool) = 0;
		virtual void* Allocate(size_t size, size_t align, int subAllocator) = 0;

		inline void* allocate(size_t size, size_t align, int subAllocator)
		{
			return Allocate(size, align, subAllocator);
		}

		virtual void* TryAllocate(size_t size, size_t align, int subAllocator) = 0;

		virtual void Free(void* pointer) = 0;

		virtual void free(void* pointer)
		{
			return Free(pointer);
		}

		virtual void TryFree(void* pointer) = 0;

		virtual void Resize(void* pointer, size_t size) = 0;

		virtual sysMemAllocator* GetAllocator(int allocator) const = 0;

		virtual sysMemAllocator* GetAllocator(int allocator) = 0;

		virtual sysMemAllocator* GetPointerOwner(void* pointer) = 0;

		virtual size_t GetSize(void* pointer) const = 0;

		virtual size_t GetMemoryUsed(int memoryBucket) = 0;

		virtual size_t GetMemoryAvailable() = 0;

	public:

		static sysMemAllocator* sysMemAllocator::UpdateAllocatorValue()
		{
			//B9 ? ? ? ? 48 8B 0C 01 45 33 C9 49 8B D2 48
			auto g_gtaTlsEntry = *(sysMemAllocator**)(*(uintptr_t*)(__readgsqword(88)) + 0xC8); //This has been 0xC8 since 323, I'm not adding this signature to pointers...

			if (g_gtaTlsEntry == nullptr)
				LOG(FATAL) << "Failed to find tlsEntry within GTA5.exe via __readgsqword";

			*(sysMemAllocator**)(*(uintptr_t*)(__readgsqword(88)) + 0xC8) = g_gtaTlsEntry;
			*(sysMemAllocator**)(*(uintptr_t*)(__readgsqword(88)) + 0xC8 - 8) = g_gtaTlsEntry;

			return g_gtaTlsEntry;
		}
	};

	inline sysMemAllocator* GetAllocator()
	{
		sysMemAllocator* allocator = *(sysMemAllocator**)(*(uintptr_t*)(__readgsqword(88)) + 0xC8);

		if (!allocator)
		{
			return sysMemAllocator::UpdateAllocatorValue();
		}

		return allocator;
	}
}