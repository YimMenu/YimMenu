#include "common.hpp"
#include "file_manager.hpp"
#include "fonts/fonts.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include <imgui.h>
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <imgui_internal.h>

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace big
{
	renderer::renderer() :
		m_dxgi_swapchain(*g_pointers->m_swapchain)
	{
		if (m_dxgi_swapchain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&m_d3d_device)) < 0)
		{
			throw std::runtime_error("Failed to get D3D device.");
		}
		m_d3d_device->GetImmediateContext(&m_d3d_device_context);

		auto file_path = g_file_manager->get_project_file("./imgui.ini").get_path();

		ImGuiContext* ctx = ImGui::CreateContext();

		static std::string path = file_path.make_preferred().string();
		ctx->IO.IniFilename = path.c_str();

		ImGui_ImplDX11_Init(m_d3d_device, m_d3d_device_context);
		ImGui_ImplWin32_Init(g_pointers->m_hwnd);

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

		{
			ImFontConfig fnt_cfg{};
			fnt_cfg.FontDataOwnedByAtlas = false;
			strcpy(fnt_cfg.Name, "Fnt20px");

			io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_storopia), sizeof(font_storopia), 20.f, &fnt_cfg, io.Fonts->GetGlyphRangesDefault());
			fnt_cfg.MergeMode = true;
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 20.f, &fnt_cfg, ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 20.f, &fnt_cfg, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			io.Fonts->Build();
		}

		{
			ImFontConfig fnt_cfg{};
			fnt_cfg.FontDataOwnedByAtlas = false;
			strcpy(fnt_cfg.Name, "Fnt28px");

			g.window.font_title = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_storopia), sizeof(font_storopia), 28.f, &fnt_cfg);
			fnt_cfg.MergeMode = true;
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 28.f, &fnt_cfg, ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 28.f, &fnt_cfg, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			io.Fonts->Build();
		}

		{
			ImFontConfig fnt_cfg{};
			fnt_cfg.FontDataOwnedByAtlas = false;
			strcpy(fnt_cfg.Name, "Fnt24px");

			g.window.font_sub_title = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_storopia), sizeof(font_storopia), 24.f, &fnt_cfg);
			fnt_cfg.MergeMode = true;
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 24.f, &fnt_cfg, ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 24.f, &fnt_cfg, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			io.Fonts->Build();
		}

		{
			ImFontConfig fnt_cfg{};
			fnt_cfg.FontDataOwnedByAtlas = false;
			strcpy(fnt_cfg.Name, "Fnt18px");

			g.window.font_small = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_storopia), sizeof(font_storopia), 18.f, &fnt_cfg);
			fnt_cfg.MergeMode = true;
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 18.f, &fnt_cfg, ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
			io.Fonts->AddFontFromMemoryTTF(font_data.get(), font_data_size, 18.f, &fnt_cfg, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			io.Fonts->Build();
		}
		
		{
			ImFontConfig font_icons_cfg{};
			font_icons_cfg.FontDataOwnedByAtlas = false;
			std::strcpy(font_icons_cfg.Name, "Icons");
			g.window.font_icon = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_icons), sizeof(font_icons), 24.f, &font_icons_cfg);
		}

		rescale(g.window.gui_scale);

		g_renderer = this;
	}

	renderer::~renderer()
	{
		g_renderer = nullptr;

		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX11_Shutdown();
		ImGui::DestroyContext();
	}

	bool renderer::add_dx_callback(dx_callback callback, std::uint32_t priority)
	{
		if (!m_dx_callbacks.insert({ priority, callback }).second)
		{
			LOG(WARNING) << "Duplicate priority given on DX Callback!";

			return false;
		}
		return true;
	}

	void renderer::add_wndproc_callback(wndproc_callback callback)
	{
		m_wndproc_callbacks.emplace_back(callback);
	}

	void renderer::on_present()
	{
		new_frame();
		for (const auto& cb : m_dx_callbacks | std::views::values)
			cb();
		end_frame();
	}

	void renderer::rescale(float rel_size)
	{
		pre_reset();
		ImGui::GetStyle().ScaleAllSizes(rel_size);
		ImGui::GetIO().FontGlobalScale = rel_size;
		post_reset();
	}

	void renderer::pre_reset()
	{
		ImGui_ImplDX11_InvalidateDeviceObjects();
	}

	void renderer::post_reset()
	{
		ImGui_ImplDX11_CreateDeviceObjects();
	}

	void renderer::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		for (const auto& cb : m_wndproc_callbacks)
			cb(hwnd, msg, wparam, lparam);

		if (g_gui->is_open())
		{
			ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
		}
	}

	void renderer::new_frame()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void renderer::end_frame()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}
