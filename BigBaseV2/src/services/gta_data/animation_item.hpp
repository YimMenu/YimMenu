#pragma once

namespace big
{
	class animation_item {
	public:
		animation_item(nlohmann::json& item_json);

		std::string dictionary_name;
		std::vector<std::string> animations;
	};
}
