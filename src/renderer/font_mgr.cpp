#include "font_mgr.hpp"
#include "fonts/fonts.hpp"

namespace big
{
	font_mgr::font_mgr(std::vector<std::pair<float, ImFont**>> extra_font_sizes) :
        m_extra_font_sizes(extra_font_sizes),
        m_require_extra(eAlphabetType::LATIN),
        m_should_rebuild_font_map(true),
        m_fonts({
            { eAlphabetType::CHINESE, { "msyh.ttc", "msyh.ttf", "arial.ttf" } },
            { eAlphabetType::CYRILLIC, { "msyh.ttc", "msyh.ttf", "arial.ttf" } },
            { eAlphabetType::JAPANESE, { "msyh.ttc", "msyh.ttf", "arial.ttf" } },
            { eAlphabetType::KOREAN, { "malgun.ttf", "arial.ttf" } },
        })
	{

	}

	font_mgr::~font_mgr()
	{
	}

	void font_mgr::rebuild_now()
	{
        if (!m_should_rebuild_font_map)
        {
            return;
        }
        m_should_rebuild_font_map = false;

        const auto extra_font_file = get_available_font_file_for_alphabet_type();
        if (m_require_extra != eAlphabetType::LATIN && !extra_font_file.exists())
        {
            LOG(WARNING) << "Could not find an appropriate font for the current language!";
        }
        const auto extra_glyph_range = get_imgui_alphabet_type();

        auto& io = ImGui::GetIO();
        io.Fonts->Clear();

        // default font size
        {
            ImFontConfig fnt_cfg{};
            fnt_cfg.FontDataOwnedByAtlas = false;
            strcpy(fnt_cfg.Name, "Fnt20px");

            io.Fonts->AddFontFromMemoryTTF(const_cast<uint8_t*>(font_storopia), sizeof(font_storopia), 20.f, &fnt_cfg, io.Fonts->GetGlyphRangesDefault());
            if (m_require_extra != eAlphabetType::LATIN && extra_font_file.exists())
            {
                fnt_cfg.MergeMode = true;
                io.Fonts->AddFontFromFileTTF(extra_font_file.get_path().string().c_str(), 20.f, &fnt_cfg, extra_glyph_range);
            }
            io.Fonts->Build();
        }

        // any other font sizes we need to support
        for (auto [ size, font_ptr ] : m_extra_font_sizes)
        {
            ImFontConfig fnt_cfg{};
            fnt_cfg.FontDataOwnedByAtlas = false;
            strcpy(fnt_cfg.Name, std::format("Fnt{}px", (int)size).c_str());

            *font_ptr = io.Fonts->AddFontFromMemoryTTF(const_cast<uint8_t*>(font_storopia), sizeof(font_storopia), size, &fnt_cfg, io.Fonts->GetGlyphRangesDefault());
            if (m_require_extra != eAlphabetType::LATIN && extra_font_file.exists())
            {
                fnt_cfg.MergeMode = true;
                io.Fonts->AddFontFromFileTTF(extra_font_file.get_path().string().c_str(), size, &fnt_cfg, extra_glyph_range);
            }
            io.Fonts->Build();
        }

        // icons blueh
		{
			ImFontConfig font_icons_cfg{};
			font_icons_cfg.FontDataOwnedByAtlas = false;
			std::strcpy(font_icons_cfg.Name, "Icons");
			g.window.font_icon = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<uint8_t*>(font_icons), sizeof(font_icons), 24.f, &font_icons_cfg);
		}
	}

	void font_mgr::update_required_alphabet_type(eAlphabetType type)
	{
        m_require_extra = type;
        m_should_rebuild_font_map = true;
	}

	file font_mgr::get_available_font_file_for_alphabet_type()
	{
        static const auto fonts_folder = std::filesystem::path(std::getenv("SYSTEMROOT")) / "Fonts";
	
        const auto& fonts = m_fonts.find(m_require_extra);
        if (fonts == m_fonts.end())
            return {};
        for (const auto& font : fonts->second)
        {
            auto font_file = file(fonts_folder / font);
            LOG(INFO) << font_file.get_path().lexically_normal();
            if (font_file.exists())
            {
                return font_file;
            }
        }
        return {};
    }

	const ImWchar* font_mgr::get_imgui_alphabet_type()
	{
        auto& io = ImGui::GetIO();
        switch (m_require_extra)
        {
        case eAlphabetType::CHINESE:
            return io.Fonts->GetGlyphRangesChineseFull();
        case eAlphabetType::CYRILLIC:
            return io.Fonts->GetGlyphRangesCyrillic();
        case eAlphabetType::JAPANESE:
            return io.Fonts->GetGlyphRangesJapanese();
        case eAlphabetType::KOREAN:
            return io.Fonts->GetGlyphRangesKorean();

        default:
        case eAlphabetType::LATIN:
            return io.Fonts->GetGlyphRangesDefault();
        }
	}
}
