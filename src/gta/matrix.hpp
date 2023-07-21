#pragma once
#include "rage/vector.hpp"
#include <cstdint>

namespace rage
{
	class matrix4x4
	{
	public:
		union {
			struct
			{
				fvector4 _1;
				fvector4 _2;
				fvector4 _3;
				fvector4 _4;
			};

			float raw[4 * 4] = {};
		};
	};

	class CViewPort
	{
	public:
		char _0x0000[0x24C];
		float m_matrix[0x10];
	};

	struct ScreenResolution
	{
		uint32_t w, h;
	};
}
