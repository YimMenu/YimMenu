#include "custom_text.hpp"

namespace big
{
	void custom_text::add_text(Hash hash, const char* text)
	{
		auto size = strlen(text) + 1;
		auto buffer = std::make_unique<char[]>(size);
		std::copy_n(text, size, buffer.get());

		custom_text::m_text_map.emplace(hash, std::move(buffer));
	}

	const char* custom_text::get_text(Hash hash)
	{
		if (auto it = custom_text::m_text_map.find(hash); it != custom_text::m_text_map.end())
			return it->second.get();
		return nullptr;
	}

	void custom_text::remove_text(Hash hash)
	{
		custom_text::m_text_map.erase(hash);
	}
}