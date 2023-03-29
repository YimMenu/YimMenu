#pragma once

#include <d3d11_1.h>
#include <memory>
#include <string>

namespace d3d11
{
	class SwapChain;
	class Geometry;
	class Effect;
	class Texture2D;
	class Context;

	template<class T>
	class ScopedBinder
	{
	public:
		ScopedBinder(std::shared_ptr<Context> const& ctx, std::shared_ptr<T> const& target) :
		    target_(target)
		{
			if (target_)
			{
				target_->bind(ctx);
			}
		}
		~ScopedBinder()
		{
			if (target_)
			{
				target_->unbind();
			}
		}

	private:
		std::shared_ptr<T> const target_;
	};

	class Context
	{
	public:
		Context(ID3D11DeviceContext*);

		void flush();

		operator ID3D11DeviceContext*()
		{
			return ctx_.get();
		}

	private:
		std::shared_ptr<ID3D11DeviceContext> const ctx_;
	};

	//
	// encapsulate a D3D11 Device object
	//
	class Device
	{
	public:
		Device(ID3D11Device*, ID3D11DeviceContext*);

		std::string adapter_name() const;

		operator ID3D11Device*()
		{
			return m_device.get();
		}

		std::shared_ptr<Context> immediate_context();

		std::shared_ptr<Geometry> create_quad(float x, float y, float width, float height, bool flip = false);

		std::shared_ptr<Texture2D> create_texture(int width, int height, DXGI_FORMAT format, const void* data, size_t row_stride);

		std::shared_ptr<Texture2D> open_shared_texture(void*);

		std::unique_ptr<Effect> create_basic_shaders();

		std::unique_ptr<Effect> create_shaders(std::string const& vertex_code, std::string const& vertex_entry, std::string const& vertex_model, std::string const& pixel_code, std::string const& pixel_entry, std::string const& pixel_model);

	private:
		std::shared_ptr<ID3DBlob> compile_shader(std::string const& source_code, std::string const& entry_point, std::string const& model);

		HMODULE _lib_compiler;

		std::shared_ptr<ID3D11Device> const m_device;
		std::shared_ptr<Context> const ctx_;
	};

	//
	// encapsulate a DXGI swapchain for a window
	//
	class SwapChain
	{
	public:
		SwapChain(IDXGISwapChain*, ID3D11RenderTargetView*, ID3D11SamplerState*, ID3D11BlendState*);

		void bind(std::shared_ptr<Context> const& ctx);
		void unbind();

		void clear(float red, float green, float blue, float alpha);

		void present(int sync_interval);
		void resize(int width, int height);

	private:
		std::shared_ptr<ID3D11SamplerState> const sampler_;
		std::shared_ptr<ID3D11BlendState> const blender_;
		std::shared_ptr<IDXGISwapChain> const swapchain_;
		std::shared_ptr<ID3D11RenderTargetView> rtv_;
		std::shared_ptr<Context> ctx_;
	};

	class Texture2D
	{
	public:
		Texture2D(ID3D11Texture2D* tex, ID3D11ShaderResourceView* srv);

		void bind(std::shared_ptr<Context> const& ctx);
		void unbind();

		uint32_t width() const;
		uint32_t height() const;
		DXGI_FORMAT format() const;

		bool has_mutex() const;

		bool lock_key(uint64_t key, uint32_t timeout_ms);
		void unlock_key(uint64_t key);

		void* share_handle() const;

		void copy_from(std::shared_ptr<Texture2D> const&);

		void copy_from(const void* buffer, uint32_t stride, uint32_t rows);

	private:
		HANDLE share_handle_;

		std::shared_ptr<ID3D11Texture2D> const texture_;
		std::shared_ptr<ID3D11ShaderResourceView> const srv_;
		std::shared_ptr<IDXGIKeyedMutex> keyed_mutex_;
		std::shared_ptr<Context> ctx_;
	};

	class Effect
	{
	public:
		Effect(ID3D11VertexShader* vsh, ID3D11PixelShader* psh, ID3D11InputLayout* layout);

		void bind(std::shared_ptr<Context> const& ctx);
		void unbind();

	private:
		std::shared_ptr<ID3D11VertexShader> const vsh_;
		std::shared_ptr<ID3D11PixelShader> const psh_;
		std::shared_ptr<ID3D11InputLayout> const layout_;
		std::shared_ptr<Context> ctx_;
	};


	class Geometry
	{
	public:
		Geometry(D3D_PRIMITIVE_TOPOLOGY primitive, uint32_t vertices, uint32_t stride, ID3D11Buffer*);

		void bind(std::shared_ptr<Context> const& ctx);
		void unbind();

		void draw();

	private:
		D3D_PRIMITIVE_TOPOLOGY primitive_;
		uint32_t vertices_;
		uint32_t stride_;
		std::shared_ptr<ID3D11Buffer> const buffer_;
		std::shared_ptr<Context> ctx_;
	};

	class d3d11_helper
	{
	public:
		static std::shared_ptr<Device> import_device(ID3D11Device* device, ID3D11DeviceContext* devicecontext);
	};
}
