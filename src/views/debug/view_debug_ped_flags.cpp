#include "fiber_pool.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "thread_pool.hpp"
#include "util/system.hpp"
#include "views/view.hpp"

namespace big
{
	void view::debug_ped_flags() {
		static bool value = false;
		static int current_flag = 0;
		
		ImGui::InputInt("Ped Flag", &current_flag);
		g_fiber_pool->queue_job([] {
			value = PED::GET_PED_CONFIG_FLAG(self::ped, current_flag, false);
		});

		if (ImGui::Checkbox("Active", &value))
		{
			PED::SET_PED_CONFIG_FLAG(self::ped, current_flag, value);
		}
	}
}