#include "hooking/hooking.hpp"
#include "rage/rlMetric.hpp"
#include "gta/json_serializer.hpp"

namespace big
{
	const auto warn_bad_metrics = std::unordered_set<std::string_view>({
		"REPORTER",
		"REPORT_INVALIDMODEL",
		"MEM_NEW",
		"DEBUGGER_ATTACH",
		"XP_LOSS",
		"CF",
		"CC",
		"CNR",
		"SCRIPT",
		"CHEAT",
		"AUX_DEUX",
		"HARDWARE_OS",
		"HARDWARE_GPU",
		"HARDWARE_MOBO",
		"HARDWARE_MEM",
		"HARDWARE_CPU",
		"PCSETTINGS",
		"CASH_CREATED",
		"DR_PS",
		"IDLEKICK",
		"GSCB",
		"GSINV",
		"GSCW",
		"GSINT",
		"GARAGE_TAMPER",
		"DUPE_DETECT",
		"LAST_VEH",
		"FAIL_SERV",
		"CCF_UPDATE",
		"CODE_CRC",
		"MM",
		"RDEV",
		"RQA",
	});
	const auto filtered_bad_metrics = std::unordered_set<std::string_view>({
		"DIG",
		"AWARD_XP",
		"WEATHER",
		"UVC",
		"W_L",
		"ESVCS",
		"EARN",
		"COLLECTIBLE",
		"FIRST_VEH",
		"RANK_UP", 
		"COMMS_TEXT", 
		"BLAST",
	});

	std::string hex_encode(std::string_view input) {
		const char* hex_chars = "0123456789ABCDEF";
		std::string output;
		output.reserve(input.length() * 2);  // Pre-allocate memory for efficiency
		for (unsigned char c : input) {
			output.push_back(hex_chars[c >> 4]);   // Extract the high nibble (4 bits)
			output.push_back(hex_chars[c & 0x0F]); // Extract the low nibble
		}
		return output;
	}

	std::string remove_module_from_mmlist(std::string_view input, std::string_view element_to_remove) {
		std::string result(input);
		std::string delimiter = "|";
		size_t start_pos = 0;

		while (true) {
			size_t delimiter_pos = result.find(delimiter, start_pos);
			if (delimiter_pos == std::string::npos) {
				break;
			}
			std::string current_element = result.substr(start_pos, delimiter_pos - start_pos);
			if (current_element == element_to_remove) {
				result.erase(start_pos, delimiter_pos - start_pos + delimiter.length());
				break;
			}
			start_pos = delimiter_pos + delimiter.length();
		}

		return result;
	}

	bool hooks::prepare_metric_for_sending(rage::json_serializer* serializer, int unk, int time, rage::rlMetric* metric)
	{
		char metric_json_buffer [256] {};
		rage::json_serializer yim_serializer(metric_json_buffer, sizeof(metric_json_buffer));
		metric->serialize(&yim_serializer);
		auto metric_name             = metric->get_name();
		auto is_warn_bad_metrics     = warn_bad_metrics.contains(metric_name);
		auto is_filtered_bad_metrics = filtered_bad_metrics.contains(metric_name);
		auto is_bad_metric           = is_warn_bad_metrics || is_filtered_bad_metrics;

		if (is_bad_metric)
		{
			if (g.debug.logs.metric_logs || is_warn_bad_metrics)
			{
				LOG(WARNING) << "BAD METRIC: " << metric_name << "; DATA: " << yim_serializer.get_string();
			}
			if (g.notifications.warn_metric && is_warn_bad_metrics)
			{
				g_notification_service.push_warning("METRIC"_T.data(),
					std::format("{} {}", "METRIC_WARNING_MESSAGE"_T, metric_name).c_str());
			}
			if (!strcmp(metric_name, "MM") && !g.debug.block_all_metrics)
			{
				std::string data = std::string(reinterpret_cast<char*>(metric) + 0x18);
				char module_name[MAX_PATH];
				GetModuleFileNameA(g_hmodule, module_name, sizeof(module_name));
				std::string encoded_module_name = hex_encode(std::filesystem::path(module_name).filename().string());
				std::string result              = remove_module_from_mmlist(data, encoded_module_name + "00");
				if (result.size() != data.size())
					LOG(INFO) << "Removed YimMenu DLL from MM metric";
				strncpy(reinterpret_cast<char*>(metric) + 0x18, result.c_str(), 0x900);
				return g_hooking->get_original<prepare_metric_for_sending>()(serializer, unk, time, metric);
			}
			return true;
		}
		else if (g.debug.logs.metric_logs == 1)
		{
			LOG(INFO) << "METRIC: " << metric_name << "; DATA: " << yim_serializer.get_string();
		}

		if (g.debug.block_all_metrics) [[unlikely]]
			return true;
		else
			return g_hooking->get_original<prepare_metric_for_sending>()(serializer, unk, time, metric);
	}
}
