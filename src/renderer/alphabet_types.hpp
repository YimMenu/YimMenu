#pragma once

namespace big
{
	enum class eAlphabetType
	{
		LATIN, // default - always built
		CHINESE,
		CYRILLIC,
		KOREAN,
		JAPANESE,
		TURKISH,
		LAST_ALPHABET_TYPE
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(eAlphabetType, {{eAlphabetType::LATIN, "latin"}, {eAlphabetType::CHINESE, "chinese"}, {eAlphabetType::CYRILLIC, "cyrillic"}, {eAlphabetType::KOREAN, "korean"}, {eAlphabetType::JAPANESE, "japanese"}, {eAlphabetType::TURKISH, "turkish"}})
}
