#include "cef_service.hpp"

#include "helper.hpp"
#include "pointers.hpp"
#include "remote_cef_client.hpp"

#include <functional>
#include <iostream>

namespace big
{
	static std::optional<std::filesystem::path> get_module_file_path(const std::string& module_name)
	{
		// Maaaaybe use memory::module (will be slower due to useless stuff we dont need there done in its ctor tho)

		HMODULE module_handle;
		if (module_handle = GetModuleHandleA(module_name.c_str()), module_handle == NULL)
		{
			LOG(WARNING) << "Couldnt retrieve module handle for " << module_name << " " << GetLastError();

			return {};
		}

		char module_file_path[MAX_PATH];
		if (GetModuleFileNameA(module_handle, module_file_path, sizeof(module_file_path)) == 0)
		{
			LOG(WARNING) << "Couldnt retrieve module file path for " << module_name << " " << GetLastError();

			return {};
		}

		return module_file_path;
	}

	static std::optional<std::filesystem::path> get_yim_cef_external_executable_path()
	{
		// TODO CEF: If we don't have it on disk, download it?
		// Could be handled by a launcher

		// TODO CEF: Don't hardcode this.
		constexpr auto file_path_str = "C:\\Program Files\\Rockstar Games\\Social Club\\YimCefExternal.exe";

		const auto file_path = std::filesystem::path(file_path_str);

		if (std::filesystem::exists(file_path))
		{
			return file_path;
		}

		return {};
	}

	static void start_process(const std::filesystem::path& process_path)
	{
		STARTUPINFO startup_info;
		PROCESS_INFORMATION process_information;

		ZeroMemory(&startup_info, sizeof(startup_info));
		startup_info.cb = sizeof(startup_info);
		ZeroMemory(&process_information, sizeof(process_information));

		CreateProcessA(process_path.string().c_str(), // The path
		    NULL,                                     // Command line
		    NULL,                                     // Process handle not inheritable
		    NULL,                                     // Thread handle not inheritable
		    FALSE,                                    // Set handle inheritance to FALSE
		    0,                                        // No creation flags
		    NULL,                                     // Use parent's environment block
		    NULL,                                     // Use parent's starting directory
		    &startup_info,                            // Pointer to STARTUPINFO structure
		    &process_information                      // Pointer to PROCESS_INFORMATION structure
		);

		// Close process and thread handles.
		CloseHandle(process_information.hProcess);
		CloseHandle(process_information.hThread);
	}

	cef_service::cef_service()
	{
		g_cef_service = this;

		// This should never fail, if somehow libcef.dll is not in the process we could load it ourselves.
		const auto libcef_dll_path = get_module_file_path("libcef.dll");

		LOG(INFO) << libcef_dll_path.has_value() ? libcef_dll_path.value() : "no libcef dll path";

		// TODO CEF: use (libcef_dll_path - its filename) to put the yim cef external exe in the same folder
		// or atleast send the path as an arg when launching it for signaling where the libcef dll and resources are located
		const auto yim_cef_external_executable_path = get_yim_cef_external_executable_path();
		if (!yim_cef_external_executable_path.has_value())
		{
			LOG(WARNING) << "No yim cef external executable found";
			return;
		}

		start_process(yim_cef_external_executable_path.value());

		constexpr auto ip   = "127.0.0.1";
		constexpr auto port = 27090;
		m_client            = std::make_unique<rpc::client>(ip, port);
	}

	cef_service::~cef_service()
	{
		constexpr auto function_name = "shutdown";
		m_client->call(function_name);

		g_cef_service = nullptr;
	}

	void cef_service::init_composition()
	{
		m_composition = std::make_unique<composition>(m_d3d_device, m_width, m_height);
	}

	// Get the current resolution of the window with the given handle
	static void get_window_size(HWND window_handle, int& width, int& height)
	{
		RECT rect;
		GetClientRect(window_handle, &rect);
		width  = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	void cef_service::init_device(ID3D11Device* pDevice, ID3D11DeviceContext* context, IDXGISwapChain* swapchain)
	{
		ID3D11Texture2D* d3d11_frame_buffer;
		HRESULT hResult = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11_frame_buffer);
		assert(SUCCEEDED(hResult));

		ID3D11RenderTargetView* pRenderTargetview;
		hResult = pDevice->CreateRenderTargetView(d3d11_frame_buffer, 0, &pRenderTargetview);
		assert(SUCCEEDED(hResult));

		context->OMSetRenderTargets(1, &pRenderTargetview, NULL);

		d3d11_frame_buffer->Release();

		// create a default sampler to use
		ID3D11SamplerState* pSampler;
		{
			D3D11_SAMPLER_DESC desc = {};
			desc.AddressU           = D3D11_TEXTURE_ADDRESS_CLAMP;
			desc.AddressV           = D3D11_TEXTURE_ADDRESS_CLAMP;
			desc.AddressW           = D3D11_TEXTURE_ADDRESS_CLAMP;
			desc.ComparisonFunc     = D3D11_COMPARISON_NEVER;
			desc.MinLOD             = 0.0f;
			desc.MaxLOD             = D3D11_FLOAT32_MAX;
			desc.Filter             = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			hResult                 = pDevice->CreateSamplerState(&desc, &pSampler);
			assert(SUCCEEDED(hResult));
		}

		// create a default blend state to use (pre-multiplied alpha)
		ID3D11BlendState* pBlender;
		{
			D3D11_BLEND_DESC desc;
			desc.AlphaToCoverageEnable  = FALSE;
			desc.IndependentBlendEnable = FALSE;
			const auto count            = sizeof(desc.RenderTarget) / sizeof(desc.RenderTarget[0]);
			for (size_t n = 0; n < count; ++n)
			{
				desc.RenderTarget[n].BlendEnable           = TRUE;
				desc.RenderTarget[n].SrcBlend              = D3D11_BLEND_ONE;
				desc.RenderTarget[n].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
				desc.RenderTarget[n].SrcBlendAlpha         = D3D11_BLEND_ONE;
				desc.RenderTarget[n].DestBlendAlpha        = D3D11_BLEND_INV_SRC_ALPHA;
				desc.RenderTarget[n].BlendOp               = D3D11_BLEND_OP_ADD;
				desc.RenderTarget[n].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
				desc.RenderTarget[n].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			}
			hResult = pDevice->CreateBlendState(&desc, &pBlender);
			assert(SUCCEEDED(hResult));
		}

		m_d3d_device = std::make_unique<d3d11::Device>(pDevice, context);
		m_swapchain  = std::make_unique<d3d11::SwapChain>(swapchain, pRenderTargetview, pSampler, pBlender);

		get_window_size(g_pointers->m_hwnd, m_width, m_height);
	}

	void cef_service::open_web_page(const std::string& url)
	{
		LOG(INFO) << "open web page: " << url;

		constexpr auto window_scaling = 0.5f;

		const auto remote_cef_client_instance = remote_cef_client::make("Yim Cef Client", url, m_width * window_scaling, m_height * window_scaling, m_d3d_device, true);
		if (!remote_cef_client_instance)
		{
			return;
		}

		// the frame buffer creation must be delayed until the shared memory is properly setup by yimcefExternal
		// It also means that the remote_cef_client should not be added to the composition with composition->add_layer until its ready
		// That's because when composition->render() is called, we don't check in remote_cef_client::render if the m_frame_buffer is null.
		// The point is to reduce to a maximum the amount of nullptr checks because of it being a hot path, when all is needed is just using init functions properly

		std::thread t([this, remote_cef_client_instance] {
			auto frame_buf = std::make_unique<frame_buffer>(m_d3d_device);

			const auto start_time = std::chrono::steady_clock::now();
			auto time_now         = std::chrono::steady_clock::now();

			while (true)
			{
				constexpr auto timeout  = 10s;
				const auto elapsed_time = time_now - start_time;
				if (elapsed_time > timeout)
				{
					LOG(WARNING) << "10s passed and the shared memory is still not ready, not adding the remote cef client layer to final composition";
					return;
				}

				if (frame_buf->is_shared_memory_ready())
				{
					break;
				}

				time_now = std::chrono::steady_clock::now();
			}

			remote_cef_client_instance->m_frame_buffer = std::move(frame_buf);

			m_composition->add_layer(remote_cef_client_instance);

			remote_cef_client_instance->move(0.25f, 0.25f, window_scaling, window_scaling);

			m_cef_clients.push_back(remote_cef_client_instance);
		});

		t.detach();
	}
}
