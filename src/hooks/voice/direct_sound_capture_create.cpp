#include "gta/sound.hpp"
#include "hooking/hooking.hpp"

namespace big
{
	HRESULT hooks::direct_sound_capture_create(GUID* guid, IDirectSoundCapture** sound, void* unknown)
	{
		if ((*guid) == g_yim_device && g.spoofing.voice_chat_audio)
		{
			*sound = &g_direct_sound_capture;
			return (HRESULT)0L;// DS_OK
		}
		else
		{
			return g_hooking->get_original<hooks::direct_sound_capture_create>()(guid, sound, unknown);
		}
	}
}
