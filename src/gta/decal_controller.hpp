#pragma once

#include "array.hpp"

namespace rage
{
	class decal;
	class decal_list;

	class decal_controller
	{
	public:
		char pad_0x0000[0xB0]; //0x0000
		decal_list* ped_decal_list[69];
		decal_list* all_tattoo_decals_active; //0x02D8 

	}; //Size=0x02E0

	class decal_list
	{
	public:
		virtual ~decal_list() = default;
		virtual __int64 refresh_list(__int64) = 0;
		char pad_0x0000[0x15E0]; //0x0000
		rage::atArray<decal> decal_array; //0x15E8

		void clear_non_perm_decals_from_decal_array()
		{
			DWORD v1; // edx
			BYTE* v2; // rax
			__int64 a1 = (__int64)this;

			v1 = 0;
			if (*(DWORD*)(a1 + 0x15E0) > 0)
			{
				v2 = (BYTE*)(a1 + 0x1E4);
				do
				{
					*v2 |= 0x40u;
					++v1;
					v2 += 0x28;
				} while (v1 < *(DWORD*)(a1 + 0x15E0));
			}
			*(DWORD*)(a1 + 0x15E0) = 0;
		}
	}; //Size=0x15F1

	class decal_helper
	{
	public:
		virtual ~decal_helper() = default;
		virtual Hash* get_decal_type(char*) = 0;
	};

	class decal
	{
	public:
		std::uint32_t N00000001; //0x0000 
		std::uint8_t N00000028; //0x0004 
		std::uint8_t N0000002A; //0x0005 
		char pad_0x0006[0x2]; //0x0006
		std::uint64_t N00000002; //0x0008 
		std::uint64_t N00000003; //0x0010 
		std::uint64_t N00000004; //0x0018 
		std::uint32_t N00000005; //0x0020 
		std::uint32_t N00000022; //0x0024 
		std::uint32_t N00000006; //0x0028 
		char pad_0x002C[0x4]; //0x002C
		decal_helper* m_decal_helper; //0x0030 
		std::uint32_t collection; //0x0038 
		std::uint32_t overlay; //0x003C 
		std::uint16_t N00000009; //0x0040 
		std::uint16_t N00000035; //0x0042 
		std::uint16_t N00000036; //0x0044 
		char pad_0x0046[0x2]; //0x0046
		std::uint32_t N0000000A; //0x0048 
		std::uint32_t N00000041; //0x004C 
		std::uint32_t N0000000B; //0x0050 
		char pad_0x0054[0x4]; //0x0054
		std::uint32_t N0000000C; //0x0058 
		std::uint32_t N00000046; //0x005C 
		std::uint32_t N0000000D; //0x0060 
		char pad_0x0064[0x4]; //0x0064
		std::uint64_t N0000000E; //0x0068 
		std::uint8_t N0000000F; //0x0070 
		char pad_0x0071[0x7]; //0x0071

	}; //Size=0x0078
	static_assert (sizeof(decal) == 0x78, "decal is not sized properly.");
}