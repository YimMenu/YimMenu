#pragma once
#include "translation_entry.hpp"

namespace big
{
	class local_index
	{
	public:
		int version = -1;
		std::string selected_language;
		std::string fallback_default_language;
		std::map<std::string, translation_entry> fallback_languages;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(local_index, version, selected_language, fallback_default_language, fallback_languages)
	};

}