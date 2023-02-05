#include "fonts_service.hpp"
#include <backends/imgui_impl_dx11.h>

namespace big
{
	fonts_service::fonts_service()
	{}

	void fonts_service::init()
	{
		ImGuiIO& io = ImGui::GetIO();
		fonts_map.emplace("arial.ttf", io.Fonts->GetGlyphRangesDefault());
		fonts_map.emplace("simhei.ttf", io.Fonts->GetGlyphRangesChineseFull());
		fonts_map.emplace("msmincho.ttc", io.Fonts->GetGlyphRangesJapanese());
	}

	void fonts_service::init_render()
	{
		folder windows_fonts(
			std::filesystem::path(std::getenv("SYSTEMROOT")) / "Fonts"
		);

		file font_file_path = windows_fonts.get_file("./msyh.ttc");
		if (!font_file_path.exists())
			font_file_path = windows_fonts.get_file("./msyh.ttf");
		auto font_file = std::ifstream(font_file_path.get_path(), std::ios::binary | std::ios::ate);
		const auto font_data_size = static_cast<int>(font_file.tellg());
		const auto font_data = std::make_unique<std::uint8_t[]>(font_data_size);

		font_file.seekg(0);
		font_file.read(reinterpret_cast<char*>(font_data.get()), font_data_size);
		font_file.close();

		auto& io = ImGui::GetIO();

		ImFontGlyphRangesBuilder builder;
		builder.AddRanges(io.Fonts->GetGlyphRangesChineseSimplifiedCommon()); // Add one of the default ranges
		//builder.AddRanges(io.Fonts->GetGlyphRangesCyrillic());
		builder.BuildRanges(&rander_fonts_ranges);                          // Build the final result (ordered ranges with all the unique characters submitted)

		{
			ImFontConfig fnt_cfg{};
			fnt_cfg.FontDataOwnedByAtlas = false;
			strcpy(fnt_cfg.Name, "Fnt20px");

			io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_storopia), sizeof(font_storopia), 20.f, &fnt_cfg, io.Fonts->GetGlyphRangesDefault());
			fnt_cfg.MergeMode = true;
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 20.f, &fnt_cfg, rander_fonts_ranges.Data);
			io.Fonts->Build();
		}

		{
			ImFontConfig fnt_cfg{};
			fnt_cfg.FontDataOwnedByAtlas = false;
			strcpy(fnt_cfg.Name, "Fnt28px");

			g.window.font_title = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_storopia), sizeof(font_storopia), 28.f, &fnt_cfg);
			fnt_cfg.MergeMode = true;
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 28.f, &fnt_cfg, rander_fonts_ranges.Data);
			io.Fonts->Build();
		}

		{
			ImFontConfig fnt_cfg{};
			fnt_cfg.FontDataOwnedByAtlas = false;
			strcpy(fnt_cfg.Name, "Fnt24px");

			g.window.font_sub_title = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_storopia), sizeof(font_storopia), 24.f, &fnt_cfg);
			fnt_cfg.MergeMode = true;
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 24.f, &fnt_cfg, rander_fonts_ranges.Data);
			io.Fonts->Build();
		}

		{
			ImFontConfig fnt_cfg{};
			fnt_cfg.FontDataOwnedByAtlas = false;
			strcpy(fnt_cfg.Name, "Fnt18px");

			g.window.font_small = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_storopia), sizeof(font_storopia), 18.f, &fnt_cfg);
			fnt_cfg.MergeMode = true;
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 18.f, &fnt_cfg, rander_fonts_ranges.Data);
			io.Fonts->Build();
		}

		{
			ImFontConfig font_icons_cfg{};
			font_icons_cfg.FontDataOwnedByAtlas = false;
			std::strcpy(font_icons_cfg.Name, "Icons");
			g.window.font_icon = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_icons), sizeof(font_icons), 24.f, &font_icons_cfg);
		}
	}

	void fonts_service::select_font(const std::string& font)
	{
		flag = 1;
		changed_font = font;

	}

	void fonts_service::change_font()
	{
		if (!flag) return;
		flag = 0;
		folder windows_fonts(
			std::filesystem::path(std::getenv("SYSTEMROOT")) / "Fonts"
		);

		file font_file_path = windows_fonts.get_file(changed_font);
		if (!font_file_path.exists())
			return;
		auto font_file = std::ifstream(font_file_path.get_path(), std::ios::binary | std::ios::ate);
		const auto font_data_size = static_cast<int>(font_file.tellg());
		const auto font_data = std::make_unique<std::uint8_t[]>(font_data_size);

		font_file.seekg(0);
		font_file.read(reinterpret_cast<char*>(font_data.get()), font_data_size);
		font_file.close();

		auto font_value = fonts_map.at(changed_font);

		auto& io = ImGui::GetIO();

		{
			ImFontConfig fnt_cfg{};
			fnt_cfg.FontDataOwnedByAtlas = false;
			strcpy(fnt_cfg.Name, "Fnt20px");
			auto default_font =  io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 20.f, &fnt_cfg, font_value);
			io.Fonts->Build();
			io.FontDefault = default_font;
		}

		//{
		//	ImFontConfig fnt_cfg{};
		//	fnt_cfg.FontDataOwnedByAtlas = false;
		//	strcpy(fnt_cfg.Name, "Fnt28px-c");
		//	g.window.font_title = io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 28.f, &fnt_cfg, font_value);
		//	io.Fonts->Build();
		//}
		//
		//{
		//	ImFontConfig fnt_cfg{};
		//	fnt_cfg.FontDataOwnedByAtlas = false;
		//	strcpy(fnt_cfg.Name, "Fnt24px-c");
		//	g.window.font_sub_title = io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 24.f, &fnt_cfg, font_value);
		//	io.Fonts->Build();
		//}
		//
		//{
		//	ImFontConfig fnt_cfg{};
		//	fnt_cfg.FontDataOwnedByAtlas = false;
		//	strcpy(fnt_cfg.Name, "Fnt18px-c");
		//	g.window.font_small = io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 18.f, &fnt_cfg, font_value);
		//	io.Fonts->Build();
		//}
		
		ImGui_ImplDX11_InvalidateDeviceObjects();
	}

	std::string& fonts_service::current_font()
	{
		return changed_font;
	}

	fonts_service::fonts_map_t& fonts_service::available_fonts()
	{
		return fonts_map;
	}
}