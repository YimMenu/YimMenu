#include "hooking.hpp"

namespace big
{
	void hooks::get_network_event_data(int64_t unk, rage::CEventNetwork* net_event)
	{
		switch (net_event->get_type()) {
			case 161: //CEventNetworkRemovedFromSessionDueToComplaints
			{
				g_notification_service->push_warning("Kicked", "You have been desync kicked.");
				break;
			}
		}

		return g_hooking->m_get_network_event_data_hook.get_original<decltype(&get_network_event_data)>()(unk, net_event);
	}
}