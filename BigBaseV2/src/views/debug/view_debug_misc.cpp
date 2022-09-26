#include "fiber_pool.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "thread_pool.hpp"
#include "util/system.hpp"
#include "views/view.hpp"

namespace big
{
	void view::debug_misc() {
		components::button("Load MP Map", []
		{
				DLC::ON_ENTER_MP();
		});
		ImGui::SameLine();
		components::button("Load SP Map", []
		{
			DLC::ON_ENTER_SP();
		});
	}
}