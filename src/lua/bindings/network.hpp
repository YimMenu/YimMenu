#pragma once

// https://stackoverflow.com/a/40777268
/**
	* Convert a Lua sequence into a C++ vector
	* Throw exception on errors or wrong types
	*/
template<typename elementType>
inline std::vector<elementType> convert_sequence(sol::table t)
{
	std::size_t sz = t.size();
	std::vector<elementType> res(sz);
	for (int i = 1; i <= sz; i++)
	{
		res[i - 1] = t[i];
	}
	return res;
}

namespace lua::network
{
	void bind(sol::state& state);
}