#pragma once

namespace big::string_conversions
{
	inline std::string utf_16_to_code_page(uint32_t code_page, std::wstring_view input)
	{
		if (input.empty())
			return {};

		const auto size = WideCharToMultiByte(code_page, 0, input.data(), static_cast<int>(input.size()), nullptr, 0, nullptr, nullptr);

		std::string output(size, '\0');

		if (size
		    != WideCharToMultiByte(code_page,
		        0,
		        input.data(),
		        static_cast<int>(input.size()),
		        output.data(),
		        static_cast<int>(output.size()),
		        nullptr,
		        nullptr))
		{
			const auto error_code = GetLastError();
			LOG(WARNING) << "WideCharToMultiByte Error in String " << error_code;
			return {};
		}

		return output;
	}
}