#pragma once
#include "common.hpp"

namespace big
{
	class notify
	{
	public:
		static void above_map(const char* text);

		static void blocked_event(const char* name, Player player);

	private:

	};
}