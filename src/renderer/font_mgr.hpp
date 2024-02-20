#pragma once
#include "alphabet_types.hpp"

namespace big
{
    class font_mgr
    {
    private:
        const std::vector<std::pair<float, ImFont**>> m_extra_font_sizes;
        // each alphabet type should have a couple of fallback fonts
        const std::unordered_map<eAlphabetType, std::vector<std::string>> m_fonts;
        // extra alphabet types that may be required to be added to the atlas
        eAlphabetType m_require_extra;
        bool m_fonts_available;
        /**
         * @brief Internal tracker if the font atlas should be updated at the start of the next frame.
         */
        bool m_should_rebuild_font_map;

    public:
        font_mgr(std::vector<std::pair<float, ImFont**>> extra_font_sizes = { { 28.f, &g.window.font_title }, { 24.f, &g.window.font_sub_title }, { 18.f, &g.window.font_small } });
        ~font_mgr();

        inline bool fonts_available() const
        { return m_fonts_available; }
        inline bool rebuild_required() const
        { return m_should_rebuild_font_map; }

        /**
         * @brief Syncronously invalidates the old font atlas and builds a new one.
         */
        void rebuild_now();
        /**
         * @brief Updates the required underlying glyph ranges to be loaded into the font atlas. Fonts will be updated on the next frame.
         * 
         * @param type 
         */
        void update_required_alphabet_type(eAlphabetType type);

    private:
        void rebuild();

        file get_available_font_file_for_alphabet_type();
        const ImWchar* get_imgui_alphabet_type();

    };
}
