
#pragma once
#include <algorithm> // For std::isspace
#include <cctype>    // For std::isalnum
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Convert a string to lowercase
inline std::string toLowercase(const std::string& str)
{
	std::string result;
	for (char c : str)
	{
		result += std::tolower(c);
	}
	return result;
}

// Function to filter strings based on a case-insensitive search string
template <typename T = std::string> std::vector<T> filterStrings(const std::vector<T>& inputVector, const std::string& searchString, std::string(*reducer)(T&) = [] (std::string &t) { return t; })
{
	std::vector<T> filteredVector;

	std::string lowercaseSearchString = toLowercase(searchString);

	// Loop through each string in the input vector
	for (auto some : inputVector)
	{
		// Convert the current string to lowercase for case-insensitive comparison
		std::string lowercaseStr = toLowercase(reducer(some));

		// Check if the lowercase search string is a substring of the lowercase current string
		if (lowercaseStr.find(lowercaseSearchString) != std::string::npos)
		{
			filteredVector.push_back(some);
		}
	}

	return filteredVector;
}
inline std::map<std::string, std::string> filterStrings(const std::map<std::string, std::string>& inputMap, const std::string& searchString, bool filterByKey)
{
	std::map<std::string, std::string> filteredMap;

	std::string lowercaseSearchString = toLowercase(searchString);

	// Loop through each string in the input vector
	for (auto pair : inputMap)
	{
		// Convert the current string to lowercase for case-insensitive comparison
		std::string lowercaseStr = toLowercase(filterByKey ? pair.first : pair.second);

		// Check if the lowercase search string is a substring of the lowercase current string
		if (lowercaseStr.find(lowercaseSearchString) != std::string::npos)
		{
			filteredMap[pair.first] = pair.second;
		}
	}

	return filteredMap;
}

// Function to trim leading and trailing whitespace from a string
inline std::string trimString(const std::string& str)
{
	auto start = str.begin();
	auto end   = str.end();

	// Find the first non-whitespace character from the start
	while (start != end && std::isspace(*start))
	{
		++start;
	}

	// Find the last non-whitespace character from the end
	while (start != end && std::isspace(*(end - 1)))
	{
		--end;
	}

	return std::string(start, end);
}

inline bool startsWithPrefix(const char* str, const char* prefix)
{
	return strncmp(str, prefix, strlen(prefix)) == 0;
}

inline bool isHexadecimal(const std::string& str) {
    // Hexadecimal string must start with "0x" or "0X"
    if (str.length() < 2 || (str[0] != '0' && std::tolower(str[1]) != 'x'))
        return false;

    // Check each character after "0x" or "0X"
    for (size_t i = 2; i < str.length(); ++i) {
        if (!std::isxdigit(str[i]))
            return false;
    }

    return true;
}
