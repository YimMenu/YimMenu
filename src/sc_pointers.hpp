#pragma once

namespace big
{
	// needed for serialization of the pointers cache
#pragma pack(push, 1)
	struct socialclub_pointers
	{
		PVOID m_update_presence_attribute_int;
		PVOID m_update_presence_attribute_string;

		functions::start_get_presence_attributes m_start_get_presence_attributes;
	};
#pragma pack(pop)

	static_assert(sizeof(socialclub_pointers) % 8 == 0, "Pointers are not properly aligned");
}
