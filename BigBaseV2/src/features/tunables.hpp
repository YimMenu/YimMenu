#pragma once
#include "common.hpp"

namespace big
{
	class tunables
	{
	public:
		static void loop();

	private:
		static void disable_phone();
		static void no_idle_kick();

	};
}