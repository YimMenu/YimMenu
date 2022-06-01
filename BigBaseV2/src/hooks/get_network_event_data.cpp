#include "hooking.hpp"

namespace big
{
	void hooks::get_network_event_data(__int64 a1, rage::CEventNetwork* net_event)
	{
		__int64 event_type = net_event->get_type();

		switch (event_type) {
			case 161: //CEventNetworkRemovedFromSessionDueToComplaints
			{
				g_notification_service->push_warning("Kicked", "You have been desync kicked.");
				break;
			}
		}

		return g_hooking->m_get_network_event_data_hook.get_original<decltype(&get_network_event_data)>()(a1, net_event);
	}
}