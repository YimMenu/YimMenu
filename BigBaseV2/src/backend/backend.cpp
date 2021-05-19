#include "backend.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "looped/looped.hpp"
#include "core/globals.hpp"

namespace big
{
	void backend::loop()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::self_noclip();
		}QUEUE_JOB_END_CLAUSE
	}
}