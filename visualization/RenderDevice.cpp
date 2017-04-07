#include "stdafx.h"
#include"RenderDevice.h"
#include "Log.h"

RenderDevice::RenderDevice()
{
	m_swapChain = nullptr;
	m_d3d11Device = nullptr;
	m_d3d11DeviceContext = nullptr;
	m_renderTargetView = nullptr;
	m_depthStencilView = nullptr;
	m_depthStencilBuffer = nullptr;
	m_backBuffer11 = nullptr;
}

RenderDevice::~RenderDevice()
{
	m_swapChain->Release();
	m_d3d11Device->Release();
	m_d3d11DeviceContext->Release();
	m_renderTargetView->Release();
	m_depthStencilView->Release();
	m_depthStencilBuffer->Release();
	m_backBuffer11->Release();
}

bool RenderDevice::Init(HWND hwnd)
{
	RECT rc;
	GetClientRect(hwnd, &rc);
	m_width = rc.right - rc.left;
	m_height = rc.bottom - rc.top;

	HRESULT hr = S_OK;

	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc.Width = m_width;
	swapChainDesc.BufferDesc.Height = m_height;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_UNKNOWN,
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_NULL,
		D3D_DRIVER_TYPE_SOFTWARE,
		D3D_DRIVER_TYPE_WARP,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	IDXGIFactory1 *DXGIFactory;
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&DXGIFactory);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан DXGI factory");
		return false;
	}

	IDXGIAdapter1 *Adapter;
	hr = DXGIFactory->EnumAdapters1(0, &Adapter);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не удалось использовать first adapter");
		return false;
	}
	DXGIFactory->Release();

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		D3D_DRIVER_TYPE driverType = driverTypes[driverTypeIndex];
		//hr = D3D11CreateDeviceAndSwapChain(Adapter, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &d3Device, &featureLevel, &d3DevCon);
		hr = D3D11CreateDeviceAndSwapChain(Adapter, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_d3d11Device, /*&featureLevel*/ NULL, &m_d3d11DeviceContext);
		//hr = D3D11CreateDeviceAndSwapChain(Adapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT, NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &d3Device, NULL, &d3DevCon);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан SwapChain");
		return false;
	}
	Adapter->Release();

	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_backBuffer11);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан BackBuffer");
		return false;
	}

	hr = m_d3d11Device->CreateRenderTargetView(m_backBuffer11, NULL, &m_renderTargetView);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан Render Targer");
		return false;
	}

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = m_width;
	depthStencilDesc.Height = m_height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = m_d3d11Device->CreateTexture2D(&depthStencilDesc, NULL, &m_depthStencilBuffer);
	hr = m_d3d11Device->CreateDepthStencilView(m_depthStencilBuffer, NULL, &m_depthStencilView);

	return true;
}

void RenderDevice::Draw()
{
	float bgColor[4] = { 0.0f, 0.1f, 0.1f, 1.0f };
	m_d3d11DeviceContext->ClearRenderTargetView(m_renderTargetView, bgColor);
	m_d3d11DeviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Set our Render Target
	m_d3d11DeviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	//Set the default blend state (no blending) for opaque objects
	m_d3d11DeviceContext->OMSetBlendState(0, 0, 0xffffffff);
}

void RenderDevice::Close()
{
	m_swapChain->Release();
	m_d3d11Device->Release();
	m_d3d11DeviceContext->Release();
	m_renderTargetView->Release();
	m_depthStencilView->Release();
	m_depthStencilBuffer->Release();
	m_backBuffer11->Release();
}
