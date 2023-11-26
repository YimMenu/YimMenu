#include "hooking.hpp"
#include "rage/rlMetric.hpp"

namespace big
{
	const auto bad_metrics = std::to_array<const std::string>({
	    "DIG",
	    "AWARD_XP",
	    "CF",
	    "CC",
	    "CNR",
	    "SCRIPT",
	    "AUX_DEUX",
	    "HARDWARE_OS",
	    "HARDWARE_GPU",
	    "HARDWARE_MOBO",
	    "HARDWARE_MEM",
	    "HARDWARE_MEM",
	    "PCSETTINGS",
	    "CASH_CREATED",
	    "DR_PS",
	    "UVC",
	    "W_L",
	    "ESVCS",
	    "GSCB",
	    "GSINV",
	    "GSCW",
	    "GSINT",
	    "EARN",
	    "GARAGE_TAMPER",
	    "TAMPER",
	});

	bool hooks::prepare_metric_for_sending(rage::json_serializer* serializer, int unk, int time, rage::rlMetric* metric)
	{
		const auto ret = g_hooking->get_original<prepare_metric_for_sending>()(serializer, unk, time, metric);

		const auto is_bad_metric = std::find_if(bad_metrics.begin(), bad_metrics.end(), [metric](auto bad_metric) {
			return metric->get_name() == bad_metric;
		}) != bad_metrics.end();
		if (is_bad_metric)
		{
			LOG(WARNING) << "BAD METRIC: " << metric->get_name() << "; DATA: " << serializer->get_string();

			return false;
		}

		if (!is_bad_metric && g.debug.logs.metric_logs)
		{
			LOG(INFO) << "METRIC: " << metric->get_name() << "; DATA: " << serializer->get_string();
		}

		return ret;
	}
}
