#pragma once
#include "common.hpp"
#include <imgui.h>
#include <set>


typedef void(*PresentCallback)(void*);


class state_saver

{

	// Public functions

public:

	state_saver();

	~state_saver();


	bool save_current_state(ID3D11DeviceContext* pContext);

	bool restore_saved_state();

	void release_saved_state();


	// Internal data

private:

	bool						m_savedState;

	D3D_FEATURE_LEVEL			m_featureLevel;

	ID3D11DeviceContext* m_pContext;

	D3D11_PRIMITIVE_TOPOLOGY	m_primitiveTopology;

	ID3D11InputLayout* m_pInputLayout;

	ID3D11BlendState* m_pBlendState;

	FLOAT						m_blendFactor[4];

	UINT						m_sampleMask;

	ID3D11DepthStencilState* m_pDepthStencilState;

	UINT						m_stencilRef;

	ID3D11RasterizerState* m_pRasterizerState;

	ID3D11ShaderResourceView* m_pPSSRV;

	ID3D11SamplerState* m_pSamplerState;

	ID3D11VertexShader* m_pVS;

	ID3D11ClassInstance* m_pVSClassInstances[256];

	UINT						m_numVSClassInstances;

	ID3D11Buffer* m_pVSConstantBuffer;

	ID3D11GeometryShader* m_pGS;

	ID3D11ClassInstance* m_pGSClassInstances[256];

	UINT						m_numGSClassInstances;

	ID3D11Buffer* m_pGSConstantBuffer;

	ID3D11ShaderResourceView* m_pGSSRV;

	ID3D11PixelShader* m_pPS;

	ID3D11ClassInstance* m_pPSClassInstances[256];

	UINT						m_numPSClassInstances;

	ID3D11HullShader* m_pHS;

	ID3D11ClassInstance* m_pHSClassInstances[256];

	UINT						m_numHSClassInstances;

	ID3D11DomainShader* m_pDS;

	ID3D11ClassInstance* m_pDSClassInstances[256];

	UINT						m_numDSClassInstances;

	ID3D11Buffer* m_pVB;

	UINT						m_vertexStride;

	UINT						m_vertexOffset;

	ID3D11Buffer* m_pIndexBuffer;

	DXGI_FORMAT					m_indexFormat;

	UINT						m_indexOffset;


	state_saver(const state_saver&);

};

namespace big
{
	class renderer
	{
	public:
		explicit renderer();
		~renderer();

		void on_present();

		void rescale(float rel_size);

		void pre_reset();
		void post_reset();

		bool add_callback(PresentCallback callback) { return m_present_callbacks.insert(callback).second; }
		bool remove_callback(PresentCallback callback) { return m_present_callbacks.erase(callback) != 0; }

		void wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	private:
		comptr<IDXGISwapChain> m_dxgi_swapchain;
		comptr<ID3D11Device> m_d3d_device;
		comptr<ID3D11DeviceContext> m_d3d_device_context;
		std::set<PresentCallback>	m_present_callbacks;
		std::unique_ptr<state_saver> m_state_saver;
		bool m_restoreState = false;

	};

	inline renderer* g_renderer{};
}