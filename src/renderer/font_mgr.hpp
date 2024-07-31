#pragma once
#include "alphabet_types.hpp"

namespace big
{
	class font_mgr final
	{
	private:
		const std::vector<std::pair<float, ImFont**>> m_extra_font_sizes;
		// each alphabet type should have a couple of fallback fonts
		const std::unordered_map<eAlphabetType, std::vector<std::string>> m_fonts;
		// extra alphabet types that may be required to be added to the atlas
		eAlphabetType m_require_extra;
		// prevent crashes when doing thread unsafe actions
		std::mutex m_update_lock;

	public:
		font_mgr(std::vector<std::pair<float, ImFont**>> extra_font_sizes = {{20.f, nullptr},
					 {28.f, &g.window.font_title},
		             {24.f, &g.window.font_sub_title},
		             {18.f, &g.window.font_small}});
		virtual ~font_mgr() = default;

		bool can_use();
		void release_use();

		/**
         * @brief Updates the required underlying glyph ranges to be loaded into the font atlas. Fonts will be updated on the next frame.
         * 
         * @param type 
         */
		void update_required_alphabet_type(eAlphabetType type);

	private:
		void rebuild();

		file get_available_font_file_for_alphabet_type(const eAlphabetType type) const;
		const std::unordered_set<eAlphabetType> get_required_alphabet_types() const;

		static eAlphabetType get_game_language_alphabet_type();
		static const ImWchar* get_imgui_alphabet_type(const eAlphabetType type);

		static const ImWchar* GetGlyphRangesChineseSimplifiedOfficial();
		static const ImWchar* GetGlyphRangesTurkish();

	};
}
