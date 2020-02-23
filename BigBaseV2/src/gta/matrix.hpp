#pragma once
#include "vector.hpp"

namespace rage
{
	class matrix4x4
	{
	public:
		union
		{
			struct
			{
				vector4 _1;
				vector4 _2;
				vector4 _3;
				vector4 _4;
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
