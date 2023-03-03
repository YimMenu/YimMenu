#pragma once
#include "hooking.hpp"

namespace big
{
	enum class eProfanity
	{
		PROFANITY_CHAT_CLEAN = -1,
		PROFANITY_CLEAN,
		PROFANITY_DIRTY,
		PROFANITY_UNK,
		PROFANITY_ERROR
	};

	int hooks::check_chat_profanity(__int64 chat_type, const char* input, const char** output)
	{
		if (g.session.chat_force_clean)
		{
			return static_cast<int>(eProfanity::PROFANITY_CHAT_CLEAN);
		}
		return g_hooking->get_original<hooks::check_chat_profanity>()(chat_type, input, output);
	}
}
