#pragma once

namespace big
{
	class custom_text
	{
	public:
		explicit custom_text();
		~custom_text();

		void add_text(Hash hash, const char* text);
		const char* get_text(Hash hash);
		void remove_text(Hash hash);

	private:
		std::unordered_map<Hash, std::unique_ptr<char[]>> m_text_map;
	};

	inline custom_text* g_custom_text{};
}