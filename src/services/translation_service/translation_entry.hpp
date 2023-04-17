#pragma once

namespace big
{
	class translation_entry
	{
	public:
		std::string name;
		std::string file;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(translation_entry, name, file)
	};
}