#pragma once

#include "Windows.h"
#include "cef/composition.hpp"
#include "cef/d3d11.hpp"
#include "rpc/client.h"

#include <condition_variable>
#include <memory>
#include <vector>

namespace big
{
	class remote_cef_client;

	class cef_service
	{
	public:
		cef_service();
		~cef_service();

		int m_width = 0, m_height = 0;

		std::condition_variable m_signal;
		std::atomic_bool m_ready;
		std::mutex m_lock;

		std::shared_ptr<d3d11::Device> m_d3d_device   = nullptr;
		std::shared_ptr<d3d11::SwapChain> m_swapchain = nullptr;
		std::unique_ptr<composition> m_composition;

		std::vector<std::shared_ptr<remote_cef_client>> m_cef_clients;
		std::unique_ptr<rpc::client> m_client;

		void open_web_page(const std::string& url);

		void init_composition();
		void init_device(ID3D11Device* pDevice, ID3D11DeviceContext* context, IDXGISwapChain* swapchain);
	};

	inline cef_service* g_cef_service;
}
