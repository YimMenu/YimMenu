#pragma once

namespace big
{
	template<typename ValueType>
	static inline void set_from_key_or_default(const nlohmann::json& j, const char* key, ValueType& value, ValueType default_value = {})
	{
		if (j.contains(key) && !j[key].is_null())
		{
			j.at(key).get_to(value);
		}
		else
		{
			value = default_value;
		}
	}
}