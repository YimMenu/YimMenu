#pragma once
#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class sys
	{
	public:
		static void loop();

	private:
		static void update_player_structs();
		static void update_screen_sizes();

	};
}