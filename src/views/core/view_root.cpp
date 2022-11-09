#include "views/view.hpp"

namespace big
{
	void view::root()
	{
		view::heading();
		view::navigation();
		view::players();
		view::active_view();

		debug::main();
	}
}
