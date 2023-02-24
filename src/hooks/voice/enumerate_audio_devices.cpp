#include "hooking.hpp"

class CFoundDevice
{
public:
	GUID m_guid;
	char m_name[64];
	char m_pad[0x44];
	int m_default_type;
	int m_pad2;
};
static_assert(sizeof(CFoundDevice) == 0x9C);

namespace big
{
	void hooks::enumerate_audio_devices(CFoundDevice* found_devices, int count, int flags)
	{
		g_hooking->get_original<hooks::enumerate_audio_devices>()(found_devices, count, flags);

		if (flags & 1)
		{
			for (int i = 0; i < count; i++)
			{
				if (strlen(found_devices[i].m_name) == 0)
				{
					strcpy(found_devices[i].m_name, "YimMenu Virtual Input Device");
					found_devices[i].m_guid         = GUID_VIDEO_DIM_TIMEOUT;
					found_devices[i].m_default_type = 1;
				}
			}
		}
	}
}
