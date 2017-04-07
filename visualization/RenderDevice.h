#pragma once
#include"stdafx.h"

class RenderDevice
{
public:
	RenderDevice();
	~RenderDevice();

	bool Init(HWND hwnd);
	void Draw();
	
	void Close();
private:
	UINT m_width;
	UINT m_height;

	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_d3d11Device;
	ID3D11DeviceContext* m_d3d11DeviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11Texture2D* m_depthStencilBuffer;

	ID3D11Texture2D *m_backBuffer11;

	friend class Render;
	friend class Shader;
};