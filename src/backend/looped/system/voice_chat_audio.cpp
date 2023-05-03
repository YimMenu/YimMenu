#include "voice_chat_audio.hpp"

#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	void voice_chat_audio::on_enable()
	{
		*g_pointers->m_gta.m_refresh_audio_input = true;
	}

	void voice_chat_audio::on_tick()
	{
		NETWORK::NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL(true);
	}

	void voice_chat_audio::on_disable()
	{
		*g_pointers->m_gta.m_refresh_audio_input = true;
		NETWORK::NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL(false);
	}
}
