#pragma once
#include <unordered_map>
#include <string>
#include "imgui.h"
#include "fonts/fonts.hpp"

namespace big
{
	class fonts_service
	{
    public:
        using fonts_map_t = std::unordered_map<std::string, ImWchar*>;
        fonts_service();
        virtual ~fonts_service() = default;
        fonts_service(const fonts_service&) = delete;
        fonts_service(fonts_service&&) noexcept = delete;
        fonts_service& operator=(const fonts_service&) = delete;
        fonts_service& operator=(fonts_service&&) noexcept = delete;
        void init();
        void select_font(const std::string& font);
        fonts_map_t& available_fonts();

    private:
        fonts_map_t fonts_map;
	};
    inline auto g_fonts_service = fonts_service();
}
