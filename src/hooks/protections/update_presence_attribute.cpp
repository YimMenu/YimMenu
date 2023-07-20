#include "hooking.hpp"
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
		if (block_session_presence() && (hash == RAGE_JOAAT("gstok") || hash == RAGE_JOAAT("gsid") || hash == RAGE_JOAAT("gstype") || hash == RAGE_JOAAT("gshost") || hash == RAGE_JOAAT("gsjoin")))
		{
			return true;
		}

		return g_hooking->get_original<hooks::update_presence_attribute_int>()(presence_data, profile_index, attr, value);
	}

	bool hooks::update_presence_attribute_string(void* presence_data, int profile_index, char* attr, char* value)
	{
		auto hash = rage::joaat(attr);
		if (block_session_presence() && hash == RAGE_JOAAT("gsinfo"))
		{
			return true;
		}

		// shouldn't have any side effects
		if (hash == RAGE_JOAAT("peeraddr"))
		{
			value = (char*)"";
		}

		return g_hooking->get_original<hooks::update_presence_attribute_string>()(presence_data, profile_index, attr, value);
	}
}