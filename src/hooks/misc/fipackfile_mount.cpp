#include "gta/fidevice.hpp"
#include "hooking.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/gta_data/yim_fipackfile.hpp"

namespace big
{
	bool hooks::fipackfile_mount(rage::fiPackfile* this_, const char* mount_point)
	{
		static bool init = ([] {
			if(g_gta_data_service->state() == eGtaDataUpdateState::ON_INIT_WAITING)
				g_gta_data_service->set_state(eGtaDataUpdateState::ON_INIT_UPDATE_START);
		}(),true);

		auto result = g_hooking->get_original<fipackfile_mount>()(this_, mount_point);

		if (g_gta_data_service->state() == eGtaDataUpdateState::ON_INIT_UPDATE_START)
		{
			yim_fipackfile rpf_wrapper = yim_fipackfile(this_);
			std::for_each(yim_fipackfile::m_wrapper_call_back.begin(), yim_fipackfile::m_wrapper_call_back.end(), [&rpf_wrapper](std::function<size_t(yim_fipackfile & rpf_wrapper)> cb) {
				cb(rpf_wrapper);
			});

			if (!stricmp(this_->GetName(), "BgScript.rpf"))
			{
				g_gta_data_service->set_state(eGtaDataUpdateState::ON_INIT_UPDATE_END);
			}
		}

		return result;
	}
}
