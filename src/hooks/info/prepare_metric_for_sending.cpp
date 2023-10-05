#include "hooking.hpp"
#include "rage/rlMetric.hpp"

namespace big
{
	bool hooks::prepare_metric_for_sending(rage::datBitBuffer* bit_buffer, int unk, int time, rage::rlMetric* metric)
	{
		return false;
	}
}
