#include "backend.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "looped/looped.hpp"

namespace big
{
	void backend::loop()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::self_godmode();
		}QUEUE_JOB_END_CLAUSE
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::self_noclip();
		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::weapons_gravity_gun();
		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::vehicle_speedo_meter();
		}QUEUE_JOB_END_CLAUSE
	}
}