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
}
