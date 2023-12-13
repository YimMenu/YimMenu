#pragma once

namespace big
{
	struct LanguageType
	{
		uint32_t id;
		const char name[32];
	};

	const LanguageType languages[] = {
	    {0, "English"},
	    {1, "French"},
	    {2, "German"},
	    {3, "Italian"},
	    {4, "Spanish (Spain)"},
	    {5, "Portuguese (Brazil)"},
	    {6, "Polish"},
	    {7, "Russian"},
	    {8, "Korean"},
	    {9, "Chinese (Traditional)"},
	    {10, "Japanese"},
	    {11, "Spanish (Mexico)"},
	    {12, "Chinese (Simpified)"},
	};
}