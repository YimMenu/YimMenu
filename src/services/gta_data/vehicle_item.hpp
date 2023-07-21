#pragma once

namespace big
{
#pragma pack(push, 4)
	class vehicle_item final
	{
	public:
		char m_name[16];
		char m_display_name[32];
		char m_display_manufacturer[32];
		char m_vehicle_class[32];
		uint32_t m_hash;
	};
#pragma pack(pop)
}