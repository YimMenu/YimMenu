#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class voice_chat_audio : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline voice_chat_audio g_voice_chat_audio("vcaudio", "Play Audio Through Voice Chat", "Plays the audio.wav file in the project folder through voice chat. The wave file must be encoded with a mono 16 bit 16kHz PCM format. You have to reset voice chat settings whenever you load the menu for the sound to play",
		    g.spoofing.voice_chat_audio);
	}
}
