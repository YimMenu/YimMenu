#pragma once
#include "renderer/alphabet_types.hpp"
#include "translation_entry.hpp"

namespace big
{
	class local_index
	{
	public:
		int version = -1;
		eAlphabetType alphabet_type = eAlphabetType::LATIN;
		std::string selected_language;
		std::string fallback_default_language;
		std::map<std::string, translation_entry> fallback_languages;
		bool default_language_set = false;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(local_index, version, alphabet_type, selected_language, fallback_default_language, fallback_languages, default_language_set)
	};

}
