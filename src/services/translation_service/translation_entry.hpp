#pragma once
#include "renderer/alphabet_types.hpp"

namespace big
{
	class translation_entry
	{
	public:
		// default to latin as most languages make use of it
		eAlphabetType alphabet_type = eAlphabetType::LATIN;
		std::string name;
		std::string file;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(translation_entry, alphabet_type, name, file)
	};
}
