#pragma once

namespace big
{
#pragma pack(push, 4)
	class ped_item final
	{
	public:
		char m_name[32];
		char m_ped_type[32];
		uint32_t m_hash;
	};
#pragma pack(pop)
}