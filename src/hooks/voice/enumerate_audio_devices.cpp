#include "gta/sound.hpp"
#include "hooking/hooking.hpp"

class CFoundDevice
{
public:
	GUID m_guid;
	char16_t m_name[64];
	int m_device_type;
	int m_default_type;
	int m_pad2;
};
static_assert(sizeof(CFoundDevice) == 0x9C);

namespace big
{
	int hooks::enumerate_audio_devices(CFoundDevice* found_devices, int count, int flags)
	{
		auto res = g_hooking->get_original<hooks::enumerate_audio_devices>()(found_devices, count, flags);

		if ((flags & 1) && g.spoofing.voice_chat_audio)
		{
			for (int i = 0; i < count; i++)
			{
				if (found_devices[i].m_device_type != 2 || found_devices[i].m_default_type != 2)
				{
					lstrcpyW((LPWSTR)found_devices[i].m_name, L"YimMenu Virtual Input Device");
					found_devices[i].m_guid         = g_yim_device;
					found_devices[i].m_device_type  = 1;
					found_devices[i].m_default_type = 1;

					if (i >= res)
						res++;

					break;
				}
			}
		}

		return res;
	}
}
