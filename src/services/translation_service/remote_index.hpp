#pragma once
#include "translation_entry.hpp"

namespace big
{
	class remote_index
	{
	public:
		int version = -1;
		std::string default_lang;
		std::map<std::string, translation_entry> translations;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(remote_index, version, default_lang, translations)
	};
}
