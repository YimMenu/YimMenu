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

	voice_chat_audio g_voice_chat_audio("vcaudio", "Play Audio Through Voice Chat", "Plays the audio.wav file in the project folder through voice chat. The wave file must be encoded with a mono 16 bit 16kHz PCM format. You have to reset voice chat settings whenever you load the menu for the sound to play",
	    g.spoofing.voice_chat_audio);
}
