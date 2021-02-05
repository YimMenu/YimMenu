#pragma once
#include "common.hpp"

namespace big
{
	class vehicle
	{
	public:
		static void loop();

	private:
		static void handling();
		static void no_bike_fall();
		static void speedo_meter();
		static void sticky_tyres();

	};
}