#include "hooking.hpp"
#include "rage/rlMetric.hpp"

namespace big
{
	const auto bad_metrics = std::unordered_set<std::string>({
	    "REPORTER",
	    "REPORT_INVALIDMODEL",
	    "MEM_NEW",
	    "DEBUGGER_ATTACH",
	    "DIG",
	    "XP_LOSS",
	    "AWARD_XP",
	    "CF",
	    "CC",
	    "CNR",
	    "SCRIPT",
	    "CHEAT",
	    "AUX_DEUX",
	    "WEATHER",
	    "HARDWARE_OS",
	    "HARDWARE_GPU",
	    "HARDWARE_MOBO",
	    "HARDWARE_MEM",
	    "HARDWARE_CPU",
	    "PCSETTINGS",
	    "CASH_CREATED",
	    "DR_PS",
	    "UVC",
	    "W_L",
	    "ESVCS",
	    "IDLEKICK",
	    "GSCB",
	    "GSINV",
	    "GSCW",
	    "GSINT",
	    "EARN",
	    "GARAGE_TAMPER",
	    "LAST_VEH",
	    "FAIL_SERV",
	    "CCF_UPDATE",
	    "CODE_CRC",
	    "COLLECTIBLE",
	    "FIRST_VEH",
	});

	bool hooks::prepare_metric_for_sending(rage::json_serializer* serializer, int unk, int time, rage::rlMetric* metric)
	{
		const auto ret = g_hooking->get_original<prepare_metric_for_sending>()(serializer, unk, time, metric);

		const auto is_bad_metric = bad_metrics.contains(metric->get_name());
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
