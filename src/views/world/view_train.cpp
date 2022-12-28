#include "fiber_pool.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "views/view.hpp"
#include "util/train.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/model_preview/model_preview_service.hpp"
#include "services/players/player_service.hpp"

#include <imgui_internal.h>


namespace big
{
	void view::train()
	{
		components::button("Hijack Train", []
			{
				train::hijack_train();
			});
	}
}