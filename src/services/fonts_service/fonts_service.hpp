#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "imgui.h"
#include "fonts/fonts.hpp"

namespace big
{
	class fonts_service
	{
    public:
        using fonts_map_t = std::unordered_map<std::string, const ImWchar *>;
        fonts_service();
        virtual ~fonts_service() = default;
        fonts_service(const fonts_service&) = delete;
        fonts_service(fonts_service&&) noexcept = delete;
        fonts_service& operator=(const fonts_service&) = delete;
        fonts_service& operator=(fonts_service&&) noexcept = delete;
        void init();
        void init_render();
        void select_font(const std::string& font);
        fonts_map_t& available_fonts();

    private:
        fonts_map_t fonts_map;
	};
    inline std::unique_ptr<fonts_service> g_fonts_service;
}
