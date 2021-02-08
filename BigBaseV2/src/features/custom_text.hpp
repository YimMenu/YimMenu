#pragma once

namespace big
{
	class custom_text
	{
	private:
		inline static std::unordered_map<Hash, std::unique_ptr<char[]>> m_text_map;

	public:
		static void add_text(Hash hash, const char* text);
		static const char* get_text(Hash hash);
		static void remove_text(Hash hash);

	};
}