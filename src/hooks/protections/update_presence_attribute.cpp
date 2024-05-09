#include "hooking/hooking.hpp"
#include "services/player_database/player_database_service.hpp"

namespace big
{
	inline bool block_session_presence()
	{
		return g.protections.rid_join || (g_player_database_service && g_player_database_service->is_redirect_join_active());
	}

	bool hooks::update_presence_attribute_int(void* presence_data, int profile_index, char* attr, uint64_t value)
	{
		auto hash = rage::joaat(attr);
		if (block_session_presence() && (hash == "gstok"_J || hash == "gsid"_J || hash == "gstype"_J || hash == "gshost"_J || hash == "gsjoin"_J))
		{
			return true;
		}

		return g_hooking->get_original<hooks::update_presence_attribute_int>()(presence_data, profile_index, attr, value);
	}

	bool hooks::update_presence_attribute_string(void* presence_data, int profile_index, char* attr, char* value)
	{
		auto hash = rage::joaat(attr);
		if (block_session_presence() && hash == "gsinfo"_J)
		{
			return true;
		}

		return g_hooking->get_original<hooks::update_presence_attribute_string>()(presence_data, profile_index, attr, value);
	}
}
