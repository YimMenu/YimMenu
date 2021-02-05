#pragma once
#include "common.hpp"
#include "functions.hpp"
#include "gta/joaat.hpp"
#include "natives.hpp"

namespace big
{
	class custom_guns
	{
	public:

		static void loop();

	private:

		static void cage_gun();
		static void delete_gun();
		static void gravity_gun();
		static void money_gun();
		static void repair_gun();
		static void vehicle_gun();

	};
}