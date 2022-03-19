#include "view.hpp"

namespace big
{
	void view::root()
	{
		view::heading();
		view::navigation();
		//view::player_navigation();
		view::active_view();
	}
}
