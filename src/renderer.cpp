#include "renderer.hpp"

#include "cef/cef_service.hpp"
#include "common.hpp"
#include "file_manager.hpp"
#include "fonts/fonts.hpp"
#include "gui.hpp"
#include "pointers.hpp"

#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <imgui.h>
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
		ctx->IO.IniFilename     = path.c_str();

		ImGui_ImplDX11_Init(m_d3d_device, m_d3d_device_context);
		ImGui_ImplWin32_Init(g_pointers->m_hwnd);

		folder windows_fonts(std::filesystem::path(std::getenv("SYSTEMROOT")) / "Fonts");

		file font_file_path = windows_fonts.get_file("./msyh.ttc");
		if (!font_file_path.exists())
			font_file_path = windows_fonts.get_file("./msyh.ttf");
		auto font_file            = std::ifstream(font_file_path.get_path(), std::ios::binary | std::ios::ate);
		const auto font_data_size = static_cast<int>(font_file.tellg());
		const auto font_data      = std::make_unique<std::uint8_t[]>(font_data_size);

		font_file.seekg(0);
		font_file.read(reinterpret_cast<char*>(font_data.get()), font_data_size);
		font_file.close();

		auto& io = ImGui::GetIO();

		{
			ImFontConfig fnt_cfg{};
			fnt_cfg.FontDataOwnedByAtlas = false;
			strcpy(fnt_cfg.Name, "Fnt20px");

			io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_storopia),
			    sizeof(font_storopia),
			    20.f,
			    &fnt_cfg,
			    io.Fonts->GetGlyphRangesDefault());
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
		if (!m_dx_callbacks.insert({priority, callback}).second)
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

	void renderer::cef_init_render_states()
	{
		g_cef_service->init_device(m_d3d_device, m_d3d_device_context, m_dxgi_swapchain);

		g_cef_service->init_composition();

		// This may need to be destroyed and remade when gui get rescaled / resolution change, unsure yet as I havent tested
		//g_cef_service->open_web_page("https://www.youtube.com/watch?v=MxEjnYdfLXU?autoplay=1");
		g_cef_service->open_web_page("https://jspaint.app");
	}

	// TODO CEF: move this elsewhere? this is pasted from imgui btw, they do the same thing.
	// Backup DX state that will be modified to restore it afterwards (unfortunately this is very ugly looking and verbose. Close your eyes!)
	struct BACKUP_DX11_STATE
	{
		UINT ScissorRectsCount, ViewportsCount;
		D3D11_RECT ScissorRects[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
		D3D11_VIEWPORT Viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
		ID3D11RasterizerState* RS;
		ID3D11BlendState* BlendState;
		FLOAT BlendFactor[4];
		UINT SampleMask;
		UINT StencilRef;
		ID3D11DepthStencilState* DepthStencilState;
		ID3D11ShaderResourceView* PSShaderResource;
		ID3D11SamplerState* PSSampler;
		ID3D11PixelShader* PS;
		ID3D11VertexShader* VS;
		ID3D11GeometryShader* GS;
		UINT PSInstancesCount, VSInstancesCount, GSInstancesCount;
		ID3D11ClassInstance *PSInstances[256], *VSInstances[256], *GSInstances[256]; // 256 is max according to PSSetShader documentation
		D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology;
		ID3D11Buffer *IndexBuffer, *VertexBuffer, *VSConstantBuffer;
		UINT IndexBufferOffset, VertexBufferStride, VertexBufferOffset;
		DXGI_FORMAT IndexBufferFormat;
		ID3D11InputLayout* InputLayout;
	};

	static BACKUP_DX11_STATE cef_backup_dx_state(ID3D11DeviceContext* ctx)
	{
		BACKUP_DX11_STATE old = {};

		old.ScissorRectsCount = old.ViewportsCount = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
		ctx->RSGetScissorRects(&old.ScissorRectsCount, old.ScissorRects);
		ctx->RSGetViewports(&old.ViewportsCount, old.Viewports);
		ctx->RSGetState(&old.RS);
		ctx->OMGetBlendState(&old.BlendState, old.BlendFactor, &old.SampleMask);
		ctx->OMGetDepthStencilState(&old.DepthStencilState, &old.StencilRef);
		ctx->PSGetShaderResources(0, 1, &old.PSShaderResource);
		ctx->PSGetSamplers(0, 1, &old.PSSampler);
		old.PSInstancesCount = old.VSInstancesCount = old.GSInstancesCount = 256;
		ctx->PSGetShader(&old.PS, old.PSInstances, &old.PSInstancesCount);
		ctx->VSGetShader(&old.VS, old.VSInstances, &old.VSInstancesCount);
		ctx->VSGetConstantBuffers(0, 1, &old.VSConstantBuffer);
		ctx->GSGetShader(&old.GS, old.GSInstances, &old.GSInstancesCount);

		ctx->IAGetPrimitiveTopology(&old.PrimitiveTopology);
		ctx->IAGetIndexBuffer(&old.IndexBuffer, &old.IndexBufferFormat, &old.IndexBufferOffset);
		ctx->IAGetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset);
		ctx->IAGetInputLayout(&old.InputLayout);

		return old;
	}

	static void cef_restore_dx_state(ID3D11DeviceContext* ctx, const BACKUP_DX11_STATE& old)
	{
		ctx->RSSetScissorRects(old.ScissorRectsCount, old.ScissorRects);
		ctx->RSSetViewports(old.ViewportsCount, old.Viewports);
		ctx->RSSetState(old.RS);
		if (old.RS)
			old.RS->Release();
		ctx->OMSetBlendState(old.BlendState, old.BlendFactor, old.SampleMask);
		if (old.BlendState)
			old.BlendState->Release();
		ctx->OMSetDepthStencilState(old.DepthStencilState, old.StencilRef);
		if (old.DepthStencilState)
			old.DepthStencilState->Release();
		ctx->PSSetShaderResources(0, 1, &old.PSShaderResource);
		if (old.PSShaderResource)
			old.PSShaderResource->Release();
		ctx->PSSetSamplers(0, 1, &old.PSSampler);
		if (old.PSSampler)
			old.PSSampler->Release();
		ctx->PSSetShader(old.PS, old.PSInstances, old.PSInstancesCount);
		if (old.PS)
			old.PS->Release();
		for (UINT i = 0; i < old.PSInstancesCount; i++)
			if (old.PSInstances[i])
				old.PSInstances[i]->Release();
		ctx->VSSetShader(old.VS, old.VSInstances, old.VSInstancesCount);
		if (old.VS)
			old.VS->Release();
		ctx->VSSetConstantBuffers(0, 1, &old.VSConstantBuffer);
		if (old.VSConstantBuffer)
			old.VSConstantBuffer->Release();
		ctx->GSSetShader(old.GS, old.GSInstances, old.GSInstancesCount);
		if (old.GS)
			old.GS->Release();
		for (UINT i = 0; i < old.VSInstancesCount; i++)
			if (old.VSInstances[i])
				old.VSInstances[i]->Release();
		ctx->IASetPrimitiveTopology(old.PrimitiveTopology);
		ctx->IASetIndexBuffer(old.IndexBuffer, old.IndexBufferFormat, old.IndexBufferOffset);
		if (old.IndexBuffer)
			old.IndexBuffer->Release();
		ctx->IASetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset);
		if (old.VertexBuffer)
			old.VertexBuffer->Release();
		ctx->IASetInputLayout(old.InputLayout);
		if (old.InputLayout)
			old.InputLayout->Release();
	}

	void renderer::on_present()
	{
		if (!g_cef_service)
		{
			return;
		}

		// cef init rendering code
		// TODO CEF: This really should be placed elsewhere,
		// It also should have an equivalent like pre_reset / post_reset like ImGui which invalidate device objects
		// in case the gui get rescaled or swapchain buffer resizing etc
		static bool init_cef_once = (cef_init_render_states(), true);

		if (g_gui->is_open() && init_cef_once)
		{
			const auto ctx_wrapper = g_cef_service->m_d3d_device->immediate_context();

			if (!ctx_wrapper || !g_cef_service->m_swapchain)
				return;

			const auto& ctx = m_d3d_device_context;

			const auto old_dx_state = cef_backup_dx_state(ctx);

			g_cef_service->m_swapchain->bind(ctx_wrapper);

			g_cef_service->m_composition->render(ctx_wrapper);

			cef_restore_dx_state(ctx, old_dx_state);
		}

		// imgui

		new_frame();
		for (const auto& cb : m_dx_callbacks | std::views::values)
			cb();
		end_frame();
	}

	void renderer::rescale(float rel_size)
	{
		pre_reset();
		g_gui->restore_default_style();

		if (rel_size != 1.0f)
			ImGui::GetStyle().ScaleAllSizes(rel_size);

		ImGui::GetStyle().MouseCursorScale = 1.0f;
		ImGui::GetIO().FontGlobalScale     = rel_size;
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


		ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
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
