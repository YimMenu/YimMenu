#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class voice_chat_audio : looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			*g_pointers->m_gta.m_refresh_audio_input   = true;
			*g_pointers->m_gta.m_refresh_audio_input_2 = true;
		}

		virtual void on_tick() override
		{
			NETWORK::NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL(true);
		}

		virtual void on_disable() override
		{
			*g_pointers->m_gta.m_refresh_audio_input   = true;
			*g_pointers->m_gta.m_refresh_audio_input_2 = true;
			NETWORK::NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL(false);
		}
	};

	voice_chat_audio g_voice_chat_audio("vcaudio", "BACKEND_LOOPED_SYSTEM_VOICE_CHAT_AUDIO", "BACKEND_LOOPED_SYSTEM_VOICE_CHAT_AUDIO_DESC", g.spoofing.voice_chat_audio);
}
