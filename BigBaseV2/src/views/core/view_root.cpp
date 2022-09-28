#include "views/view.hpp"

namespace big
{
	void view::root()
	{
		view::gta_data();

		view::heading();
		view::navigation();
		view::players();
		view::active_view();
	}
}
