#pragma once
#include "common.hpp"

namespace big
{
	using dx_callback      = std::function<void()>;
	using wndproc_callback = std::function<void(HWND, UINT, WPARAM, LPARAM)>;

	class renderer final
	{
	public:
		explicit renderer();
		~renderer();

		/**
		 * @brief Add a callback function to draw your ImGui content in
		 * 
		 * @param callback Function
		 * @param priority The higher the priority the value the later it gets drawn on top
		 * @return true 
		 * @return false 
		 */
		bool add_dx_callback(dx_callback callback, std::uint32_t priority);
		/**
		 * @brief Add a callback function on wndproc
		 * 
		 * @param callback Function
		 */
		void add_wndproc_callback(wndproc_callback callback);

		void on_present();

		void rescale(float rel_size);

		void pre_reset();
		void post_reset();

		void wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	private:
		static void new_frame();
		static void end_frame();

	private:
		IDXGISwapChain* m_dxgi_swapchain;
		ID3D11Device* m_d3d_device;
		ID3D11DeviceContext* m_d3d_device_context;

		std::map<std::uint32_t, dx_callback> m_dx_callbacks;
		std::vector<wndproc_callback> m_wndproc_callbacks;
	};

	inline renderer* g_renderer{};
}
