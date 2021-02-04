#include "custom_text.hpp"

namespace big
{
	custom_text::custom_text()
	{
		g_custom_text = this;
	}

	custom_text::~custom_text()
	{
		g_custom_text = nullptr;
	}

	void custom_text::add_text(Hash hash, const char* text)
	{
		auto size = strlen(text) + 1;
		auto buffer = std::make_unique<char[]>(size);
		std::copy_n(text, size, buffer.get());

		this->m_text_map.emplace(hash, std::move(buffer));
	}

	const char* custom_text::get_text(Hash hash)
	{
		if (auto it = this->m_text_map.find(hash); it != m_text_map.end())
			return it->second.get();
		return nullptr;
	}

	void custom_text::remove_text(Hash hash)
	{
		this->m_text_map.erase(hash);
	}
}