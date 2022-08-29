#include "animation_item.hpp"

namespace big
{
	animation_item::animation_item(nlohmann::json& item_json)
	{
		this->dictionary_name = item_json["DictionaryName"];
		for (auto& animation : item_json["Animations"])
		{
			this->animations.push_back(animation.get<std::string>());
		}
	}
}
