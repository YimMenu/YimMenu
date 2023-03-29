#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "d3d11.hpp"
#include "frame_buffer.hpp"
#include "helper.hpp"

#include <d3dcompiler.h>
#include <directxmath.h>
#include <memory>
#include <string>


std::string to_utf8(const wchar_t* utf16)
{
	if (!utf16)
	{
		return std::string();
	}

	const auto cch = static_cast<int>(wcslen(utf16));
	std::shared_ptr<char> utf8;
	const auto cb = WideCharToMultiByte(CP_UTF8, 0, utf16, cch, nullptr, 0, nullptr, nullptr);
	if (cb > 0)
	{
		utf8 = std::shared_ptr<char>(reinterpret_cast<char*>(malloc(cb + 1)), free);
		WideCharToMultiByte(CP_UTF8, 0, utf16, cch, utf8.get(), cb, nullptr, nullptr);
		*(utf8.get() + cch) = '\0';
	}
	if (!utf8)
	{
		return std::string();
	}
	return std::string(utf8.get(), cb);
}

std::wstring from_utf8charptr_to_utf16(const char* utf8);
std::wstring from_utf8string_to_utf16(std::string const& utf8)
{
	return from_utf8charptr_to_utf16(utf8.c_str());
}

//
// quick and dirty conversion from UTF-8 to wide-char std::string for Windows
//
std::wstring from_utf8charptr_to_utf16(const char* utf8)
{
	if (!utf8)
	{
		return std::wstring();
	}

	const auto cb = static_cast<int>(strlen(utf8));
	std::shared_ptr<WCHAR> utf16;
	const auto cch = MultiByteToWideChar(CP_UTF8, 0, utf8, cb, nullptr, 0);
	if (cch > 0)
	{
		utf16 = std::shared_ptr<WCHAR>(reinterpret_cast<WCHAR*>(malloc(sizeof(WCHAR) * (cch + 1))), free);
		MultiByteToWideChar(CP_UTF8, 0, utf8, cb, utf16.get(), cch);
		*(utf16.get() + cch) = L'\0';
	}
	if (!utf16)
	{
		return std::wstring();
	}
	return std::wstring(utf16.get(), cch);
}

namespace d3d11
{
	using namespace big;

	struct SimpleVertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 tex;
	};

	Context::Context(ID3D11DeviceContext* ctx) :
	    ctx_(cef_helper::to_shared_ptr(ctx))
	{
	}

	void Context::flush()
	{
		ctx_->Flush();
	}


	SwapChain::SwapChain(IDXGISwapChain* swapchain, ID3D11RenderTargetView* rtv, ID3D11SamplerState* sampler, ID3D11BlendState* blender) :
	    sampler_(cef_helper::to_shared_ptr(sampler)),
	    blender_(cef_helper::to_shared_ptr(blender)),
	    swapchain_(cef_helper::to_shared_ptr(swapchain)),
	    rtv_(cef_helper::to_shared_ptr(rtv))
	{
	}

	void SwapChain::bind(std::shared_ptr<Context> const& ctx)
	{
		ctx_                           = ctx;
		ID3D11DeviceContext* d3d11_ctx = (ID3D11DeviceContext*)(*ctx_);

		ID3D11RenderTargetView* rtv[1] = {rtv_.get()};
		d3d11_ctx->OMSetRenderTargets(1, rtv, nullptr);

		// set default blending state
		if (blender_)
		{
			float factor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
			d3d11_ctx->OMSetBlendState(blender_.get(), factor, 0xffffffff);
		}

		// set default sampler state
		if (sampler_)
		{
			ID3D11SamplerState* samplers[1] = {sampler_.get()};
			d3d11_ctx->PSSetSamplers(0, 1, samplers);
		}
	}

	void SwapChain::unbind()
	{
		ctx_.reset();
	}

	Effect::Effect(ID3D11VertexShader* vsh, ID3D11PixelShader* psh, ID3D11InputLayout* layout) :
	    vsh_(cef_helper::to_shared_ptr(vsh)),
	    psh_(cef_helper::to_shared_ptr(psh)),
	    layout_(cef_helper::to_shared_ptr(layout))
	{
	}

	void Effect::bind(std::shared_ptr<Context> const& ctx)
	{
		ctx_                           = ctx;
		ID3D11DeviceContext* d3d11_ctx = (ID3D11DeviceContext*)(*ctx_);

		d3d11_ctx->IASetInputLayout(layout_.get());
		d3d11_ctx->VSSetShader(vsh_.get(), nullptr, 0);
		d3d11_ctx->PSSetShader(psh_.get(), nullptr, 0);
	}

	void Effect::unbind()
	{
	}

	Geometry::Geometry(D3D_PRIMITIVE_TOPOLOGY primitive, uint32_t vertices, uint32_t stride, ID3D11Buffer* buffer) :
	    primitive_(primitive),
	    vertices_(vertices),
	    stride_(stride),
	    buffer_(cef_helper::to_shared_ptr(buffer))
	{
	}

	void Geometry::bind(std::shared_ptr<Context> const& ctx)
	{
		ctx_                           = ctx;
		ID3D11DeviceContext* d3d11_ctx = (ID3D11DeviceContext*)(*ctx_);

		// todo: handle offset
		uint32_t offset = 0;

		ID3D11Buffer* buffers[1] = {buffer_.get()};
		d3d11_ctx->IASetVertexBuffers(0, 1, buffers, &stride_, &offset);
		d3d11_ctx->IASetPrimitiveTopology(primitive_);
	}

	void Geometry::unbind()
	{
	}

	void Geometry::draw()
	{
		ID3D11DeviceContext* d3d11_ctx = (ID3D11DeviceContext*)(*ctx_);
		assert(d3d11_ctx);

		// todo: handle offset
		d3d11_ctx->Draw(vertices_, 0);
	}


	Texture2D::Texture2D(ID3D11Texture2D* tex, ID3D11ShaderResourceView* srv) :
	    texture_(cef_helper::to_shared_ptr(tex)),
	    srv_(cef_helper::to_shared_ptr(srv))
	{
		share_handle_ = nullptr;

		IDXGIResource* res = nullptr;
		if (SUCCEEDED(texture_->QueryInterface(__uuidof(IDXGIResource), reinterpret_cast<void**>(&res))))
		{
			res->GetSharedHandle(&share_handle_);
			res->Release();
		}

		// are we using a keyed mutex?
		IDXGIKeyedMutex* mutex = nullptr;
		if (SUCCEEDED(texture_->QueryInterface(__uuidof(IDXGIKeyedMutex), (void**)&mutex)))
		{
			keyed_mutex_ = cef_helper::to_shared_ptr(mutex);
		}
	}

	uint32_t Texture2D::width() const
	{
		D3D11_TEXTURE2D_DESC desc;
		texture_->GetDesc(&desc);
		return desc.Width;
	}

	uint32_t Texture2D::height() const
	{
		D3D11_TEXTURE2D_DESC desc;
		texture_->GetDesc(&desc);
		return desc.Height;
	}

	DXGI_FORMAT Texture2D::format() const
	{
		D3D11_TEXTURE2D_DESC desc;
		texture_->GetDesc(&desc);
		return desc.Format;
	}

	bool Texture2D::has_mutex() const
	{
		return (keyed_mutex_.get() != nullptr);
	}

	bool Texture2D::lock_key(uint64_t key, uint32_t timeout_ms)
	{
		if (keyed_mutex_)
		{
			const auto hr = keyed_mutex_->AcquireSync(key, timeout_ms);
			return SUCCEEDED(hr);
		}
		return true;
	}

	void Texture2D::unlock_key(uint64_t key)
	{
		if (keyed_mutex_)
		{
			keyed_mutex_->ReleaseSync(key);
		}
	}

	void Texture2D::bind(std::shared_ptr<Context> const& ctx)
	{
		ctx_                           = ctx;
		ID3D11DeviceContext* d3d11_ctx = (ID3D11DeviceContext*)(*ctx_);
		if (srv_)
		{
			ID3D11ShaderResourceView* views[1] = {srv_.get()};
			d3d11_ctx->PSSetShaderResources(0, 1, views);
		}
	}

	void Texture2D::unbind()
	{
	}

	void* Texture2D::share_handle() const
	{
		return share_handle_;
	}

	void Texture2D::copy_from(std::shared_ptr<Texture2D> const& other)
	{
		ID3D11DeviceContext* d3d11_ctx = (ID3D11DeviceContext*)(*ctx_);
		assert(d3d11_ctx);
		if (other)
		{
			d3d11_ctx->CopyResource(texture_.get(), other->texture_.get());
		}
	}

	void Texture2D::copy_from(const void* buffer, uint32_t stride, uint32_t rows)
	{
		if (!buffer)
		{
			return;
		}

		ID3D11DeviceContext* d3d11_ctx = (ID3D11DeviceContext*)(*ctx_);
		assert(d3d11_ctx);

		D3D11_MAPPED_SUBRESOURCE res;
		const auto hr = d3d11_ctx->Map(texture_.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &res);
		if (SUCCEEDED(hr))
		{
			if (rows == height())
			{
				if (res.RowPitch == stride)
				{
					memcpy(res.pData, buffer, stride * rows);
				}
				else
				{
					const uint8_t* src = (const uint8_t*)buffer;
					uint8_t* dst       = (uint8_t*)res.pData;
					uint32_t cb        = res.RowPitch < stride ? res.RowPitch : stride;
					for (uint32_t y = 0; y < rows; ++y)
					{
						memcpy(dst, src, cb);
						src += stride;
						dst += res.RowPitch;
					}
				}
			}

			d3d11_ctx->Unmap(texture_.get(), 0);
		}
	}

	Device::Device(ID3D11Device* pdev, ID3D11DeviceContext* pctx) :
	    m_device(cef_helper::to_shared_ptr(pdev)),
	    ctx_(std::make_shared<Context>(pctx))
	{
		_lib_compiler = LoadLibrary("d3dcompiler_47_64.dll");
	}

	std::string Device::adapter_name() const
	{
		IDXGIDevice* dxgi_dev = nullptr;
		auto hr               = m_device->QueryInterface(__uuidof(dxgi_dev), (void**)&dxgi_dev);
		if (SUCCEEDED(hr))
		{
			IDXGIAdapter* dxgi_adapt = nullptr;
			hr                       = dxgi_dev->GetAdapter(&dxgi_adapt);
			dxgi_dev->Release();
			if (SUCCEEDED(hr))
			{
				DXGI_ADAPTER_DESC desc;
				hr = dxgi_adapt->GetDesc(&desc);
				dxgi_adapt->Release();
				if (SUCCEEDED(hr))
				{
					return to_utf8(desc.Description);
				}
			}
		}

		return "n/a";
	}

	std::shared_ptr<Context> Device::immediate_context()
	{
		return ctx_;
	}

	std::shared_ptr<Geometry> Device::create_quad(float x, float y, float width, float height, bool flip)
	{
		x       = (x * 2.0f) - 1.0f;
		y       = 1.0f - (y * 2.0f);
		width   = width * 2.0f;
		height  = height * 2.0f;
		float z = 1.0f;

		SimpleVertex vertices[] = {{DirectX::XMFLOAT3(x, y, z), DirectX::XMFLOAT2(0.0f, 0.0f)}, {DirectX::XMFLOAT3(x + width, y, z), DirectX::XMFLOAT2(1.0f, 0.0f)}, {DirectX::XMFLOAT3(x, y - height, z), DirectX::XMFLOAT2(0.0f, 1.0f)}, {DirectX::XMFLOAT3(x + width, y - height, z), DirectX::XMFLOAT2(1.0f, 1.0f)}};

		if (flip)
		{
			DirectX::XMFLOAT2 tmp(vertices[2].tex);
			vertices[2].tex = vertices[0].tex;
			vertices[0].tex = tmp;

			tmp             = vertices[3].tex;
			vertices[3].tex = vertices[1].tex;
			vertices[1].tex = tmp;
		}

		D3D11_BUFFER_DESC desc = {};
		desc.Usage             = D3D11_USAGE_DEFAULT;
		desc.ByteWidth         = sizeof(SimpleVertex) * frame_buffer::required_bytes_per_pixel;
		desc.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags    = 0;

		D3D11_SUBRESOURCE_DATA srd = {};
		srd.pSysMem                = vertices;

		ID3D11Buffer* buffer = nullptr;
		const auto hr        = m_device->CreateBuffer(&desc, &srd, &buffer);
		if (SUCCEEDED(hr))
		{
			return std::make_shared<Geometry>(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, 4, static_cast<uint32_t>(sizeof(SimpleVertex)), buffer);
		}

		return nullptr;
	}

	std::shared_ptr<Texture2D> Device::open_shared_texture(void* handle)
	{
		ID3D11Texture2D* tex = nullptr;
		auto hr              = m_device->OpenSharedResource(handle, __uuidof(ID3D11Texture2D), (void**)(&tex));
		if (FAILED(hr))
		{
			return nullptr;
		}

		D3D11_TEXTURE2D_DESC td;
		tex->GetDesc(&td);

		ID3D11ShaderResourceView* srv = nullptr;

		if (td.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc;
			srv_desc.Format                    = td.Format;
			srv_desc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
			srv_desc.Texture2D.MostDetailedMip = 0;
			srv_desc.Texture2D.MipLevels       = 1;

			hr = m_device->CreateShaderResourceView(tex, &srv_desc, &srv);
			if (FAILED(hr))
			{
				tex->Release();
				return nullptr;
			}
		}

		return std::make_shared<Texture2D>(tex, srv);
	}

	std::shared_ptr<Texture2D> Device::create_texture(int width, int height, DXGI_FORMAT format, const void* data, size_t row_stride)
	{
		D3D11_TEXTURE2D_DESC td;
		td.ArraySize          = 1;
		td.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
		td.CPUAccessFlags     = data ? 0 : D3D11_CPU_ACCESS_WRITE;
		td.Format             = format;
		td.Width              = width;
		td.Height             = height;
		td.MipLevels          = 1;
		td.MiscFlags          = 0;
		td.SampleDesc.Count   = 1;
		td.SampleDesc.Quality = 0;
		td.Usage              = data ? D3D11_USAGE_DEFAULT : D3D11_USAGE_DYNAMIC;

		D3D11_SUBRESOURCE_DATA srd;
		srd.pSysMem          = data;
		srd.SysMemPitch      = static_cast<uint32_t>(row_stride);
		srd.SysMemSlicePitch = 0;

		ID3D11Texture2D* tex = nullptr;
		auto hr              = m_device->CreateTexture2D(&td, data ? &srd : nullptr, &tex);
		if (FAILED(hr))
		{
			return nullptr;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc;
		srv_desc.Format                    = td.Format;
		srv_desc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		srv_desc.Texture2D.MostDetailedMip = 0;
		srv_desc.Texture2D.MipLevels       = 1;

		ID3D11ShaderResourceView* srv = nullptr;
		hr                            = m_device->CreateShaderResourceView(tex, &srv_desc, &srv);
		if (FAILED(hr))
		{
			tex->Release();
			return nullptr;
		}

		return std::make_shared<Texture2D>(tex, srv);
	}


	std::shared_ptr<ID3DBlob> Device::compile_shader(std::string const& source_code, std::string const& entry_point, std::string const& model)
	{
		if (!_lib_compiler)
		{
			LOG(WARNING) << "no lib compiler dll";
			return nullptr;
		}

		typedef HRESULT(WINAPI * PFN_D3DCOMPILE)(LPCVOID, SIZE_T, LPCSTR, const D3D_SHADER_MACRO*, ID3DInclude*, LPCSTR, LPCSTR, UINT, UINT, ID3DBlob**, ID3DBlob**);

		const auto fnc_compile = reinterpret_cast<PFN_D3DCOMPILE>(GetProcAddress(_lib_compiler, "D3DCompile"));
		if (!fnc_compile)
		{
			LOG(WARNING) << "ERROR!! Cant get GetProcAddress(D3DCompile)";
			return nullptr;
		}

		DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(NDEBUG)
		//flags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
		//flags |= D3DCOMPILE_AVOID_FLOW_CONTROL;
#else
		flags |= D3DCOMPILE_DEBUG;
		flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		ID3DBlob* blob     = nullptr;
		ID3DBlob* blob_err = nullptr;

		const auto psrc = source_code.c_str();
		const auto len  = source_code.size() + 1;

		const auto hr = fnc_compile(psrc, len, nullptr, nullptr, nullptr, entry_point.c_str(), model.c_str(), flags, 0, &blob, &blob_err);

		if (FAILED(hr))
		{
			if (blob_err)
			{
				LOG(WARNING) << "ERROR!! blob_err";
				blob_err->Release();
			}

			return nullptr;
		}

		if (blob_err)
		{
			blob_err->Release();
		}

		return std::shared_ptr<ID3DBlob>(blob, [](ID3DBlob* p) {
			if (p)
				p->Release();
		});
	}


	// Create some basic shaders so we can draw a textured-quad
	std::unique_ptr<Effect> Device::create_basic_shaders()
	{
		LOG(INFO) << "Compiling basic shaders";
		const auto vsh =
		    R"--(struct VS_INPUT
{
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
};
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.pos = input.pos;
	output.tex = input.tex;
	return output;
})--";

		const auto psh =
		    R"--(Texture2D tex0 : register(t0);
SamplerState samp0 : register(s0);
struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};
float4 main(VS_OUTPUT input) : SV_Target
{
	return tex0.Sample(samp0, input.tex);
})--";

		return create_shaders(vsh, "main", "vs_4_0", psh, "main", "ps_4_0");
	}

	std::unique_ptr<Effect> Device::create_shaders(std::string const& vertex_code, std::string const& vertex_entry, std::string const& vertex_model, std::string const& pixel_code, std::string const& pixel_entry, std::string const& pixel_model)
	{
		const auto vs_blob        = compile_shader(vertex_code, vertex_entry, vertex_model);
		ID3D11VertexShader* vshdr = nullptr;
		ID3D11InputLayout* layout = nullptr;

		m_device->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vshdr);

		D3D11_INPUT_ELEMENT_DESC layout_desc[] = {
		    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		    {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		uint32_t elements = ARRAYSIZE(layout_desc);

		// Create the input layout
		m_device->CreateInputLayout(layout_desc, elements, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &layout);

		const auto ps_blob       = compile_shader(pixel_code, pixel_entry, pixel_model);
		ID3D11PixelShader* pshdr = nullptr;
		m_device->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &pshdr);

		return std::make_unique<Effect>(vshdr, pshdr, layout);
	}


	std::shared_ptr<Device> d3d11_helper::import_device(ID3D11Device* device, ID3D11DeviceContext* devicecontext)
	{
		const auto dev = std::make_shared<Device>(device, devicecontext);

		return dev;
	}
}
