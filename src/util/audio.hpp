#pragma once
#include <Windows.h>
#include <filesystem>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

namespace big::audio
{
	enum string_code
	{
		eRecalc,
		eHighlightedRoute,
		eFeetUntilAction,
		eKeepLeft,
		eKeepRight,
		eStraight,
		eTurnLeft,
		eTurnRight,
		eFiveHundredFeet,
		eError
	};
	string_code hash_input(std::string const& input)
	{
		if (input == "RouteRecalc")
		{
			return eRecalc;
		}
		else if (input == "HighlightedRoute")
		{
			return eHighlightedRoute;
		}
		else if (input == "FeetUntilAction")
		{
			return eFeetUntilAction;
		}
		else if (input == "KeepLeft")
		{
			return eKeepLeft;
		}
		else if (input == "KeepRight")
		{
			return eKeepRight;
		}
		else if (input == "Straight")
		{
			return eStraight;
		}
		else if (input == "TurnLeft")
		{
			return eTurnLeft;
		}
		else if (input == "TurnRight")
		{
			return eTurnRight;
		}
		else if (input == "FiveHundredFeet")
		{
			return eFiveHundredFeet;
		}
		else
		{
			return eError;
		}
	}

	inline void play_sound_nav(std::string audio_item, int feet)
	{
		std::filesystem::path base = std::getenv("appdata");
		base /= "YimMenu";
		base /= "navigation";
		switch (hash_input(audio_item))
		{
		case eRecalc:
			base /= "routerecalc.WAV";
			PlaySound(TEXT(base.string().c_str()), NULL, SND_FILENAME | SND_ASYNC);
			break;

		case eFeetUntilAction:
			switch (feet)
			{
			case 5280:
				base /= "mile.WAV";
				PlaySound(TEXT(base.string().c_str()), NULL, SND_FILENAME | SND_ASYNC);
				break;
			case 1000:
				base /= "thousandfeet.WAV";
				PlaySound(TEXT(base.string().c_str()), NULL, SND_FILENAME | SND_ASYNC);
				break;

			case 500:
				base /= "fivehundredfeet.WAV";
				PlaySound(TEXT(base.string().c_str()), NULL, SND_FILENAME | SND_ASYNC);
				break;
			case 100:
				base /= "onehundredfeet.WAV";
				PlaySound(TEXT(base.string().c_str()), NULL, SND_FILENAME | SND_ASYNC);
				break;
			}
			break;
		case eFiveHundredFeet:
			base /= "fivehundredfeet.WAV";
			PlaySound(TEXT(base.string().c_str()), NULL, SND_FILENAME | SND_ASYNC);
			break;

		case eKeepLeft:
			base /= "keepleft.WAV";
			PlaySound(TEXT(base.string().c_str()), NULL, SND_FILENAME | SND_ASYNC);
			break;

		case eKeepRight:
			base /= "keepright.WAV";
			PlaySound(TEXT(base.string().c_str()), NULL, SND_FILENAME | SND_ASYNC);
			break;
		case eStraight:
			base /= "straight.WAV";
			PlaySound(TEXT(base.string().c_str()), NULL, SND_FILENAME | SND_ASYNC);
			break;
		case eTurnLeft:
			base /= "turnleft.WAV";
			PlaySound(TEXT(base.string().c_str()), NULL, SND_FILENAME | SND_ASYNC);
			break;

		case eTurnRight:
			base /= "turnright.WAV";
			PlaySound(TEXT(base.string().c_str()), NULL, SND_FILENAME | SND_ASYNC);
			break;
		}
	}

	// path param must be the absolute path with .WAV at the end
	inline bool play_sound(std::string path)
	{
		try
		{
			PlaySound(TEXT(base.c_str()), NULL, SND_FILENAME | SND_ASYNC);
		}
	}

}