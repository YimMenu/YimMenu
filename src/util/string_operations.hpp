#pragma once

namespace big::string::operations
{
	inline std::string to_lower(std::string& str)
	{
		std::string result = str;
		std::transform(result.begin(), result.end(), result.begin(), ::tolower);
		str = result;
		return result;
	}

	inline std::string to_upper(std::string& str)
	{
		std::string result = str;
		std::transform(result.begin(), result.end(), result.begin(), ::toupper);
		str = result;
		return result;
	}

	inline std::string trim(std::string& str)
	{
		std::string result = str;
		result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
			return !std::isspace(ch);
		}));
		result.erase(std::find_if(result.rbegin(),
		                 result.rend(),
		                 [](unsigned char ch) {
			                 return !std::isspace(ch);
		                 })
		                 .base(),
		    result.end());
		str = result;
		return result;
	}

	inline std::string remove_whitespace(std::string& str)
	{
		std::string result = str;
		result.erase(std::remove_if(result.begin(), result.end(), isspace), result.end());
		str = result;
		return result;
	}

	static std::vector<std::string> split(const std::string text, char delimiter)
	{
		std::vector<std::string> tokens;
		std::size_t start = 0, end = 0;
		while ((end = text.find(delimiter, start)) != std::string::npos)
		{
			if (end != start)
			{
				tokens.push_back(text.substr(start, end - start));
			}
			start = end + 1;
		}
		if (end != start)
		{
			tokens.push_back(text.substr(start));
		}
		return tokens;
	}

	static std::string join(const std::vector<std::string>& tokens, char delimiter)
	{
		std::string result;
		for (size_t i = 0; i < tokens.size(); i++)
		{
			result += tokens[i];
			if (i != tokens.size() - 1)
			{
				result += delimiter;
			}
		}
		return result;
	}
}