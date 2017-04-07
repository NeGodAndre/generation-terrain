#include "stdafx.h"
#include "Render.h"
#include "Log.h"

Render::Render()
{
	m_swapChain = NULL;
	m_d3d11Device = NULL;
	m_d3d11DeviceContext = NULL;
	m_renderTargetView = NULL;
	m_squareIndexBuffer = NULL;
	m_depthStencilView = NULL;
	m_depthStencilBuffer = NULL;
	m_squareVertBuffer = NULL;
	m_VS = NULL;
	m_PS = NULL;
	m_VSBuffer = NULL;
	m_PSBuffer = NULL;
	m_D2D_PS = NULL;
	m_D2D_PS_Buffer = NULL;
	m_vertLayout = NULL;
	m_cbPerObjectBuffer = NULL;
	m_CCWcullMode = NULL;
	m_CWcullMode = NULL;
	m_cubesTexture = NULL;
	m_cubesTexSamplerState = NULL;
	m_cbPerFrameBuffer = NULL;
	m_backBuffer11 = NULL;//?
	m_sphereIndexBuffer = NULL;
	m_sphereVertBuffer = NULL;
	m_SKYMAP_VS = NULL;
	m_SKYMAP_PS = NULL;
	m_SKYMAP_VS_Buffer = NULL;
	m_SKYMAP_PS_Buffer = NULL;
	m_smrv = NULL;
	m_DSLessEqual = NULL;
	m_RSCullNone = NULL;

	defaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	defaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	camYaw = 0.0f;
	camPitch = 0.0f;
	rot = 0.01f;
	rotx = 0;
	rotz = 0;
	scaleX = 1.0f;
	scaleY = 1.0f;

	NumFaces = 0;
	NumVertices = 0;
}

bool Render::Init(HWND hwnd)
{
	RECT rc;
	GetClientRect(hwnd, &rc);
	m_width = rc.right - rc.left;
	m_height = rc.bottom - rc.top;
	if (!InitDirect(hwnd))
	{
		Log::Get()->Err("Не удалось инициализировать DirectX");
		return false;
	}
	if (!InitScene())
	{
		Log::Get()->Err("Не удалось инициализировать экран");
		return false;
	}
	return true;
}

bool Render::InitDirect(HWND hwnd)
{
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
		hr = D3D11CreateDeviceAndSwapChain(Adapter, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_d3d11Device, &m_featureLevel, &m_d3d11DeviceContext);
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

	m_d3d11Device->CreateTexture2D(&depthStencilDesc, NULL, &m_depthStencilBuffer);
	m_d3d11Device->CreateDepthStencilView(m_depthStencilBuffer, NULL, &m_depthStencilView);

	return true;
}

bool Render::InitScene()
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",	 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	////////
	m_createSphere(10, 10);
	///obj
	//if (!m_loadObjModel(L"1.obj", &meshVertBuff, &meshIndexBuff, meshSubsetIndexStart, meshSubsetTexture, material, meshSubsets, true, false))
		//return false;
	///obj
	hr = D3DCompileFromFile(L"Effects.fx", NULL, NULL, "VS", "vs_4_0", 0, 0, &m_VSBuffer, NULL);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не скомпилировался vertex buffer");
		return false;
	}
	hr = D3DCompileFromFile(L"Effects.fx", NULL, NULL, "PS", "ps_4_0", 0, 0, &m_PSBuffer, NULL);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не скомпилировался pixel buffer");
		return false;
	}
	hr = D3DCompileFromFile(L"Effects.fx", NULL, NULL, "D2D_PS", "ps_4_0", 0, 0, &m_D2D_PS_Buffer, 0);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не скомпилировался D2D_PS");
		return false;
	}
	//
	hr = D3DCompileFromFile(L"Effects.fx", 0, 0, "SKYMAP_VS", "vs_4_0", 0, 0, &m_SKYMAP_VS_Buffer, 0);
	hr = D3DCompileFromFile(L"Effects.fx", 0, 0, "SKYMAP_PS", "ps_4_0", 0, 0, &m_SKYMAP_PS_Buffer, 0);
	//
	hr = m_d3d11Device->CreateVertexShader(m_VSBuffer->GetBufferPointer(), m_VSBuffer->GetBufferSize(), NULL, &m_VS);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан Vertex Shader");
		return false;
	}
	hr = m_d3d11Device->CreatePixelShader(m_PSBuffer->GetBufferPointer(), m_PSBuffer->GetBufferSize(), NULL, &m_PS);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан Pixel Shader");
		return false;
	}
	hr = m_d3d11Device->CreatePixelShader(m_D2D_PS_Buffer->GetBufferPointer(), m_D2D_PS_Buffer->GetBufferSize(), NULL, &m_D2D_PS);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан свет");
		return false;
	}
	//
	hr = m_d3d11Device->CreateVertexShader(m_SKYMAP_VS_Buffer->GetBufferPointer(), m_SKYMAP_VS_Buffer->GetBufferSize(), NULL, &m_SKYMAP_VS);
	hr = m_d3d11Device->CreatePixelShader(m_SKYMAP_PS_Buffer->GetBufferPointer(), m_SKYMAP_PS_Buffer->GetBufferSize(), NULL, &m_SKYMAP_PS);
	/////////
	m_d3d11DeviceContext->VSSetShader(m_VS, 0, 0);
	m_d3d11DeviceContext->PSSetShader(m_PS, 0, 0);

	light.dir = XMFLOAT3(0.25f, 0.5f, 1.0f);
	light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	/*light.dir = XMFLOAT3(0.0f, 1.0f, 0.0f);
	light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);*/
	light.pad = 1000.0f;
	//light.range = 1000.0f;

	HeightMapInfo hmInfo;
	m_heightMapLoad("heightmap.bmp", hmInfo);
	int cols = hmInfo.terrainWidth;
	int rows = hmInfo.terrainHeight;
	//int cols = 2;
	//int rows = 2;
	NumVertices = rows * cols;
	NumFaces = (rows - 1)*(cols - 1) * 2;
	std::vector<Vertex> v(NumVertices);
	std::vector<DWORD> indices(NumFaces * 3);
	m_vectorToVertecAndDWORD(hmInfo, v, indices);
	

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * NumFaces * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = &indices[0];
	m_d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &m_squareIndexBuffer);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * NumVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = &v[0];
	hr = m_d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_squareVertBuffer);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан буфер");
		return false;
	}

	hr = m_d3d11Device->CreateInputLayout(layout, numElements, m_VSBuffer->GetBufferPointer(),
		m_VSBuffer->GetBufferSize(), &m_vertLayout);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан Input Layout");
		return false;
	}

	m_d3d11DeviceContext->IASetInputLayout(m_vertLayout);

	m_d3d11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = m_width;
	viewport.Height = m_height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_d3d11DeviceContext->RSSetViewports(1, &viewport);

	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	hr = m_d3d11Device->CreateBuffer(&cbbd, NULL, &m_cbPerObjectBuffer);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан cbPerObjectBuffer");
		return false;
	}

	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerFrame);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	hr = m_d3d11Device->CreateBuffer(&cbbd, NULL, &m_cbPerFrameBuffer);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан cbPerFrameBuffer");
		return false;
	}

	//camPosition = XMVectorSet(0.0f, 5.0f, -8.0f, 0.0f);///////////////////////////////почему -то замена не срабатывает
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);

	camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, m_width / m_height, 1.0f, 1000.0f);

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
	rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbd;

	hr = CreateWICTextureFromFile(m_d3d11Device, L"grass.jpg", NULL, &m_cubesTexture);
	if (FAILED(hr))
	{
		Log::Get()->Err("Текстура из файла не создана");
	}

	hr = CreateDDSTextureFromFile(m_d3d11Device, L"skymap.dds", NULL, &m_smrv);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = m_d3d11Device->CreateSamplerState(&sampDesc, &m_cubesTexSamplerState);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан Sample State");
	}
	//
	D3D11_RASTERIZER_DESC cmdesc;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));

	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_BACK;
	cmdesc.FrontCounterClockwise = true;
	hr = m_d3d11Device->CreateRasterizerState(&cmdesc, &m_CCWcullMode);

	cmdesc.FrontCounterClockwise = false;
	hr = m_d3d11Device->CreateRasterizerState(&cmdesc, &m_CWcullMode);

	cmdesc.CullMode = D3D11_CULL_NONE;
	hr = m_d3d11Device->CreateRasterizerState(&cmdesc, &m_RSCullNone);

	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	m_d3d11Device->CreateDepthStencilState(&dssDesc, &m_DSLessEqual);

	return true;
}

void Render::DrawScene()
{
	float bgColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	m_d3d11DeviceContext->ClearRenderTargetView(m_renderTargetView, bgColor);
	m_d3d11DeviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_d3d11DeviceContext->UpdateSubresource(m_cbPerFrameBuffer, 0, NULL, &light, 0, 0);
	m_d3d11DeviceContext->PSSetConstantBuffers(0, 1, &m_cbPerFrameBuffer);

	m_d3d11DeviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	m_d3d11DeviceContext->OMSetBlendState(0, 0, 0xffffffff);

	m_d3d11DeviceContext->VSSetShader(m_VS, 0, 0);
	m_d3d11DeviceContext->PSSetShader(m_PS, 0, 0);

	m_d3d11DeviceContext->IASetIndexBuffer(m_squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_d3d11DeviceContext->IASetVertexBuffers(0, 1, &m_squareVertBuffer, &stride, &offset);

	WVP = groundWorld * camView * camProjection;
	cbPerObj.WVP = XMMatrixTranspose(WVP);
	cbPerObj.World = XMMatrixTranspose(groundWorld);
	m_d3d11DeviceContext->UpdateSubresource(m_cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	m_d3d11DeviceContext->VSSetConstantBuffers(0, 1, &m_cbPerObjectBuffer);
	m_d3d11DeviceContext->PSSetShaderResources(0, 1, &m_cubesTexture);
	m_d3d11DeviceContext->PSSetSamplers(0, 1, &m_cubesTexSamplerState);

	m_d3d11DeviceContext->RSSetState(m_CCWcullMode);
	m_d3d11DeviceContext->DrawIndexed(NumFaces * 3, 0, 0);
	/*//////////////////
	for (int i = 0; i < meshSubsets; ++i)
	{
		m_d3d11DeviceContext->IASetIndexBuffer(meshIndexBuff, DXGI_FORMAT_R32_UINT, 0);
		m_d3d11DeviceContext->IASetVertexBuffers(0, 1, &meshVertBuff, &stride, &offset);

		WVP = meshWorld * camView * camProjection;
		cbPerObj.WVP = XMMatrixTranspose(WVP);
		cbPerObj.World = XMMatrixTranspose(meshWorld);
		cbPerObj.difColor = material[meshSubsetTexture[i]].difColor;
		cbPerObj.hasTexture = material[meshSubsetTexture[i]].hasTexture;
		m_d3d11DeviceContext->UpdateSubresource(m_cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
		m_d3d11DeviceContext->VSSetConstantBuffers(0, 1, &m_cbPerObjectBuffer);
		m_d3d11DeviceContext->PSSetConstantBuffers(1, 1, &m_cbPerObjectBuffer);
		if (material[meshSubsetTexture[i]].hasTexture)
			m_d3d11DeviceContext->PSSetShaderResources(0, 1, &meshSRV[material[meshSubsetTexture[i]].texArrayIndex]);
		m_d3d11DeviceContext->PSSetSamplers(0, 1, &m_cubesTexSamplerState);

		m_d3d11DeviceContext->RSSetState(m_RSCullNone);
		int indexStart = meshSubsetIndexStart[i];
		int indexDrawAmount = meshSubsetIndexStart[i + 1] - meshSubsetIndexStart[i];
		if (!material[meshSubsetTexture[i]].transparent)
			m_d3d11DeviceContext->DrawIndexed(indexDrawAmount, indexStart, 0);
	}
	///////////////**************new**************////////////////////

	//
	m_d3d11DeviceContext->IASetIndexBuffer(m_sphereIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_d3d11DeviceContext->IASetVertexBuffers(0, 1, &m_sphereVertBuffer, &stride, &offset);

	WVP = sphereWorld * camView * camProjection;
	cbPerObj.WVP = XMMatrixTranspose(WVP);
	cbPerObj.World = XMMatrixTranspose(sphereWorld);
	m_d3d11DeviceContext->UpdateSubresource(m_cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	m_d3d11DeviceContext->VSSetConstantBuffers(0, 1, &m_cbPerObjectBuffer);

	m_d3d11DeviceContext->PSSetShaderResources(0, 1, &m_smrv);
	m_d3d11DeviceContext->PSSetSamplers(0, 1, &m_cubesTexSamplerState);

	m_d3d11DeviceContext->VSSetShader(m_SKYMAP_VS, 0, 0);
	m_d3d11DeviceContext->PSSetShader(m_SKYMAP_PS, 0, 0);

	m_d3d11DeviceContext->OMSetDepthStencilState(m_DSLessEqual, 0);
	m_d3d11DeviceContext->RSSetState(m_RSCullNone);
	m_d3d11DeviceContext->DrawIndexed(m_numSphereFaces * 3, 0, 0);

	m_d3d11DeviceContext->VSSetShader(m_VS, 0, 0);
	m_d3d11DeviceContext->OMSetDepthStencilState(NULL, 0);


	/*///////////
	m_d3d11DeviceContext->OMSetBlendState(Transparency, NULL, 0xffffffff);

	for (int i = 0; i < meshSubsets; ++i)
	{
		m_d3d11DeviceContext->IASetIndexBuffer(meshIndexBuff, DXGI_FORMAT_R32_UINT, 0);
		m_d3d11DeviceContext->IASetVertexBuffers(0, 1, &meshVertBuff, &stride, &offset);

		WVP = meshWorld * camView * camProjection;
		cbPerObj.WVP = XMMatrixTranspose(WVP);
		cbPerObj.World = XMMatrixTranspose(meshWorld);
		cbPerObj.difColor = material[meshSubsetTexture[i]].difColor;
		cbPerObj.hasTexture = material[meshSubsetTexture[i]].hasTexture;
		m_d3d11DeviceContext->UpdateSubresource(m_cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
		m_d3d11DeviceContext->VSSetConstantBuffers(0, 1, &m_cbPerObjectBuffer);
		m_d3d11DeviceContext->PSSetConstantBuffers(1, 1, &m_cbPerObjectBuffer);
		if (material[meshSubsetTexture[i]].hasTexture)
			m_d3d11DeviceContext->PSSetShaderResources(0, 1, &meshSRV[material[meshSubsetTexture[i]].texArrayIndex]);
		m_d3d11DeviceContext->PSSetSamplers(0, 1, &m_cubesTexSamplerState);

		m_d3d11DeviceContext->RSSetState(m_RSCullNone);
		int indexStart = meshSubsetIndexStart[i];
		int indexDrawAmount = meshSubsetIndexStart[i + 1] - meshSubsetIndexStart[i];
		if (material[meshSubsetTexture[i]].transparent)
			m_d3d11DeviceContext->DrawIndexed(indexDrawAmount, indexStart, 0);
	}
	///////////////**************new**************////////////////////

	m_swapChain->Present(0, 0);
}

void Render::UpdateScene()
{
	//
	groundWorld = XMMatrixIdentity();

	scale = XMMatrixScaling(500.0f, 10.0f, 500.0f);
	translation = XMMatrixTranslation(0.0f, 10.0f, 0.0f);

	groundWorld = scale * translation;

	sphereWorld = XMMatrixIdentity();

	scale = XMMatrixScaling(5.0f, 5.0f, 5.0f);
	translation = XMMatrixTranslation(XMVectorGetX(camPosition), XMVectorGetY(camPosition), XMVectorGetZ(camPosition));
	sphereWorld = scale * translation;

	/*////////////////////////////////
	meshWorld = XMMatrixIdentity();

	rotation = XMMatrixRotationY(3.14f);
	scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	meshWorld = rotation * scale * translation;
	///////////////**************new**************////////////////////


	groundWorld = XMMatrixIdentity();
	scale = XMMatrixScaling(10.0f, 10.0f, 10.0f);
	translation = XMMatrixTranslation(-100.0f, -100.0f, -100.0f);
	groundWorld = scale * translation;

	sphereWorld = XMMatrixIdentity();

	scale = XMMatrixScaling(5.0f, 5.0f, 5.0f);
	translation = XMMatrixTranslation(XMVectorGetX(camPosition), XMVectorGetY(camPosition), XMVectorGetZ(camPosition));

	sphereWorld = scale * translation;
}

void Render::UpdateCamera()
{
	camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camTarget = XMVector3TransformCoord(defaultForward, camRotationMatrix);
	camTarget = XMVector3Normalize(camTarget);

	camRight = XMVector3TransformCoord(defaultRight, camRotationMatrix);
	camForward = XMVector3TransformCoord(defaultForward, camRotationMatrix);
	camUp = XMVector3Cross(camForward, camRight);

	camPosition += moveLeftRight*camRight;
	camPosition += moveBackForward*camForward;

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	camTarget = camPosition + camTarget;

	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
}

void Render::Close()
{
	if (m_swapChain)
		m_swapChain->Release();
	if (m_d3d11Device)
		m_d3d11Device->Release();
	if (m_d3d11DeviceContext)
		m_d3d11DeviceContext->Release();
	if (m_renderTargetView)
		m_renderTargetView->Release();
	if (m_squareIndexBuffer)
		m_squareIndexBuffer->Release();
	if (m_depthStencilView)
		m_depthStencilView->Release();
	if (m_depthStencilBuffer)
		m_depthStencilBuffer->Release();
	if (m_squareVertBuffer)
		m_squareVertBuffer->Release();
	if (m_VS)
		m_VS->Release();
	if (m_PS)
		m_PS->Release();
	if (m_VSBuffer)
		m_VSBuffer->Release();
	if (m_PSBuffer)
		m_PSBuffer->Release();
	if (m_vertLayout)
		m_vertLayout->Release();
	if (m_D2D_PS)
		m_D2D_PS->Release();
	if (m_D2D_PS_Buffer)
		m_D2D_PS_Buffer->Release();
	if (m_cbPerObjectBuffer)
		m_cbPerObjectBuffer->Release();
	if (m_CCWcullMode)
		m_CCWcullMode->Release();
	if (m_CWcullMode)
		m_CWcullMode->Release();
	if (m_cubesTexSamplerState)
		m_cubesTexSamplerState->Release();
	if (m_cubesTexture)
		m_cubesTexture->Release();
	if (m_cbPerFrameBuffer)
		m_cbPerFrameBuffer->Release();
	if (m_backBuffer11)
		m_backBuffer11->Release();
	if (m_sphereIndexBuffer)
		m_sphereIndexBuffer->Release();
	if (m_sphereVertBuffer)
		m_sphereVertBuffer->Release();
	if (m_SKYMAP_VS)
		m_SKYMAP_VS->Release();
	if (m_SKYMAP_PS)
		m_SKYMAP_PS->Release();
	if (m_SKYMAP_VS_Buffer)
		m_SKYMAP_VS_Buffer->Release();
	if (m_SKYMAP_PS_Buffer)
		m_SKYMAP_PS_Buffer->Release();
	if (m_smrv)
		m_smrv->Release();
	if (m_DSLessEqual)
		m_DSLessEqual->Release();
	if (m_RSCullNone)
		m_RSCullNone->Release();

	if (meshVertBuff)
		meshVertBuff->Release();
	if (meshIndexBuff)
		meshIndexBuff->Release();
}

void Render::MoveBackForward(float step)
{
	moveBackForward += step;
}

void Render::MoveLeftRight(float step)
{
	moveLeftRight += step;
}

void Render::Rotation(int x, int y, float rot)
{
	camYaw += x * rot;
	camPitch += y * rot;
}

void Render::m_createSphere(int LatLines, int LongLines)
{
	HRESULT hr;

	m_numSphereVertices = ((LatLines - 2) * LongLines) + 2;
	m_numSphereFaces = ((LatLines - 3)*(LongLines)* 2) + (LongLines * 2);

	float sphereYaw = 0.0f;
	float spherePitch = 0.0f;

	std::vector<Vertex> vertices(m_numSphereVertices);

	XMVECTOR currVertPos = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	vertices[0].pos.x = 0.0f;
	vertices[0].pos.y = 0.0f;
	vertices[0].pos.z = 1.0f;

	for (DWORD i = 0; i < (unsigned long)(LatLines - 2); ++i)
	{
		spherePitch = (i + 1) * (3.14f / (LatLines - 1));
		rotationx = XMMatrixRotationX(spherePitch);
		for (DWORD j = 0; j < (unsigned long)LongLines; ++j)
		{
			sphereYaw = j * (6.28f / (LongLines));
			rotationy = XMMatrixRotationZ(sphereYaw);
			currVertPos = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), (rotationx * rotationy));
			currVertPos = XMVector3Normalize(currVertPos);
			vertices[i*LongLines + j + 1].pos.x = XMVectorGetX(currVertPos);
			vertices[i*LongLines + j + 1].pos.y = XMVectorGetY(currVertPos);
			vertices[i*LongLines + j + 1].pos.z = XMVectorGetZ(currVertPos);
		}
	}

	vertices[m_numSphereVertices - 1].pos.x = 0.0f;
	vertices[m_numSphereVertices - 1].pos.y = 0.0f;
	vertices[m_numSphereVertices - 1].pos.z = -1.0f;


	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * m_numSphereVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = &vertices[0];
	hr = m_d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_sphereVertBuffer);


	std::vector<DWORD> indices(m_numSphereFaces * 3);

	int k = 0;
	for (DWORD l = 0; l < (unsigned long)(LongLines - 1); ++l)
	{
		indices[k] = 0;
		indices[k + 1] = l + 1;
		indices[k + 2] = l + 2;
		k += 3;
	}

	indices[k] = 0;
	indices[k + 1] = LongLines;
	indices[k + 2] = 1;
	k += 3;

	for (DWORD i = 0; i < (unsigned long)(LatLines - 3); ++i)
	{
		for (DWORD j = 0; j < (unsigned long)(LongLines - 1); ++j)
		{
			indices[k] = i*LongLines + j + 1;
			indices[k + 1] = i*LongLines + j + 2;
			indices[k + 2] = (i + 1)*LongLines + j + 1;

			indices[k + 3] = (i + 1)*LongLines + j + 1;
			indices[k + 4] = i*LongLines + j + 2;
			indices[k + 5] = (i + 1)*LongLines + j + 2;

			k += 6; // next quad
		}

		indices[k] = (i*LongLines) + LongLines;
		indices[k + 1] = (i*LongLines) + 1;
		indices[k + 2] = ((i + 1)*LongLines) + LongLines;

		indices[k + 3] = ((i + 1)*LongLines) + LongLines;
		indices[k + 4] = (i*LongLines) + 1;
		indices[k + 5] = ((i + 1)*LongLines) + 1;

		k += 6;
	}

	for (DWORD l = 0; l < (unsigned long)(LongLines - 1); ++l)
	{
		indices[k] = m_numSphereVertices - 1;
		indices[k + 1] = (m_numSphereVertices - 1) - (l + 1);
		indices[k + 2] = (m_numSphereVertices - 1) - (l + 2);
		k += 3;
	}

	indices[k] = m_numSphereVertices - 1;
	indices[k + 1] = (m_numSphereVertices - 1) - LongLines;
	indices[k + 2] = m_numSphereVertices - 2;

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * m_numSphereFaces * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = &indices[0];
	m_d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &m_sphereIndexBuffer);


}

bool Render::m_heightMapLoad(char* filename, HeightMapInfo &hminfo)
{
	FILE *filePtr;							
	BITMAPFILEHEADER bitmapFileHeader;	
	BITMAPINFOHEADER bitmapInfoHeader;		
	int imageSize, index;
	unsigned char height;

	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return 0;

	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	hminfo.terrainWidth = bitmapInfoHeader.biWidth;
	hminfo.terrainHeight = bitmapInfoHeader.biHeight;

	imageSize = hminfo.terrainWidth * hminfo.terrainHeight * 3;

	unsigned char* bitmapImage = new unsigned char[imageSize];

	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	fread(bitmapImage, 1, imageSize, filePtr);

	fclose(filePtr);

	hminfo.heightMap = new XMFLOAT3[hminfo.terrainWidth * hminfo.terrainHeight];

	int k = 0;

	float heightFactor = 5.0f;/////////////////////////////////////////////////

	for (int j = 0; j< hminfo.terrainHeight; j++)
	{
		for (int i = 0; i< hminfo.terrainWidth; i++)
		{
			height = bitmapImage[k];

			index = (hminfo.terrainHeight * j) + i;

			hminfo.heightMap[index].x = (float)i;
			hminfo.heightMap[index].y = (float)height / heightFactor;
			hminfo.heightMap[index].z = (float)j;

			k += 3;
		}
	}

	delete[] bitmapImage;
	bitmapImage = 0;

	return true;
}

void Render::m_vectorToVertecAndDWORD(HeightMapInfo hmInfo, std::vector<Vertex>& v, std::vector<DWORD>& indices)
{
	int cols = hmInfo.terrainWidth;
	int rows = hmInfo.terrainHeight;

	NumVertices = rows * cols;
	NumFaces = (rows - 1)*(cols - 1) * 2;

	for (DWORD i = 0; i < (unsigned long)rows; ++i)
	{
		for (DWORD j = 0; j < (unsigned long)cols; ++j)
		{
			v[i*cols + j].pos = hmInfo.heightMap[i*cols + j];
			v[i*cols + j].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		}
	}

	int k = 0;
	int texUIndex = 0;
	int texVIndex = 0;
	for (DWORD i = 0; i < (unsigned long)(rows - 1); i++)
	{
		for (DWORD j = 0; j < (unsigned long)(cols - 1); j++)
		{
			indices[k] = i*cols + j;	
			v[i*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 1.0f);

			indices[k + 1] = i*cols + j + 1;
			v[i*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 1.0f);

			indices[k + 2] = (i + 1)*cols + j;	
			v[(i + 1)*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 0.0f);


			indices[k + 3] = (i + 1)*cols + j;	
			v[(i + 1)*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 0.0f);

			indices[k + 4] = i*cols + j + 1;	
			v[i*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 1.0f);

			indices[k + 5] = (i + 1)*cols + j + 1;	
			v[(i + 1)*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 0.0f);

			k += 6; 

			texUIndex++;
		}
		texUIndex = 0;
		texVIndex++;
	}

	std::vector<XMFLOAT3> tempNormal;

	XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

	float vecX, vecY, vecZ;

	XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < NumFaces; ++i)
	{
		vecX = v[indices[(i * 3)]].pos.x - v[indices[(i * 3) + 2]].pos.x;
		vecY = v[indices[(i * 3)]].pos.y - v[indices[(i * 3) + 2]].pos.y;
		vecZ = v[indices[(i * 3)]].pos.z - v[indices[(i * 3) + 2]].pos.z;
		edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);

		vecX = v[indices[(i * 3) + 2]].pos.x - v[indices[(i * 3) + 1]].pos.x;
		vecY = v[indices[(i * 3) + 2]].pos.y - v[indices[(i * 3) + 1]].pos.y;
		vecZ = v[indices[(i * 3) + 2]].pos.z - v[indices[(i * 3) + 1]].pos.z;
		edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);

		XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));
		tempNormal.push_back(unnormalized);
	}

	XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	int facesUsing = 0;
	float tX;
	float tY;
	float tZ;

	for (int i = 0; i < NumVertices; ++i)
	{
		for (int j = 0; j < NumFaces; ++j)
		{
			if (indices[j * 3] == i ||
				indices[(j * 3) + 1] == i ||
				indices[(j * 3) + 2] == i)
			{
				tX = XMVectorGetX(normalSum) + tempNormal[j].x;
				tY = XMVectorGetY(normalSum) + tempNormal[j].y;
				tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;

				normalSum = XMVectorSet(tX, tY, tZ, 0.0f);
				facesUsing++;
			}
		}

		normalSum = normalSum / (float)facesUsing;

		normalSum = XMVector3Normalize(normalSum);

		v[i].normal.x = XMVectorGetX(normalSum);
		v[i].normal.y = XMVectorGetY(normalSum);
		v[i].normal.z = XMVectorGetZ(normalSum);

		normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		facesUsing = 0;
	}
}

bool Render::m_loadObjModel(std::wstring filename, ID3D11Buffer** vertBuff, ID3D11Buffer** indexBuff, std::vector<int>& subsetIndexStart, std::vector<int>& subsetMaterialArray, std::vector<SurfaceMaterial>& material, int& subsetCount, bool isRHCoordSys, bool computeNormals)
{
	HRESULT hr = 0;

	std::wifstream fileIn(filename.c_str());	
	std::wstring meshMatLib;					

	std::vector<DWORD> indices;
	std::vector<XMFLOAT3> vertPos;
	std::vector<XMFLOAT3> vertNorm;
	std::vector<XMFLOAT2> vertTexCoord;
	std::vector<std::wstring> meshMaterials;

	std::vector<int> vertPosIndex;
	std::vector<int> vertNormIndex;
	std::vector<int> vertTCIndex;

	bool hasTexCoord = false;
	bool hasNorm = false;

	std::wstring meshMaterialsTemp;
	int vertPosIndexTemp;
	int vertNormIndexTemp;
	int vertTCIndexTemp;

	wchar_t checkChar;		
	std::wstring face;		
	int vIndex = 0;			
	int triangleCount = 0;	
	int totalVerts = 0;
	int meshTriangles = 0;
	//
	bool bufBool;// = true;
	//
	if (fileIn)
	{
		while (fileIn)
		{
			checkChar = fileIn.get();	

			switch (checkChar)
			{
			case '#':
				checkChar = fileIn.get();
				while (checkChar != '\n')
					checkChar = fileIn.get();
				break;
			case 'v':	
				checkChar = fileIn.get();
				if (checkChar == ' ')	
				{
					float vz, vy, vx;
					fileIn >> vx >> vy >> vz;	

					if (isRHCoordSys)
					{
						vertPos.push_back(XMFLOAT3(vx, vy, vz * -1.0f));
						//if (bufBool)
						{
							camPosition = XMVectorSet(vx, vy, vz * 1.0f, 0.0f);
						}
					}
						
					else
						vertPos.push_back(XMFLOAT3(vx, vy, vz));
				}
				if (checkChar == 't')
				{
					float vtcu, vtcv;
					fileIn >> vtcu >> vtcv;	

					if (isRHCoordSys)
						vertTexCoord.push_back(XMFLOAT2(vtcu, 1.0f - vtcv));
					else
						vertTexCoord.push_back(XMFLOAT2(vtcu, vtcv));

					hasTexCoord = true;	
				}

				if (checkChar == 'n')
				{
					float vnx, vny, vnz;
					fileIn >> vnx >> vny >> vnz;	

					if (isRHCoordSys)	
						vertNorm.push_back(XMFLOAT3(vnx, vny, vnz * -1.0f));	
					else
						vertNorm.push_back(XMFLOAT3(vnx, vny, vnz));

					hasNorm = true;	
				}
				break;

			case 'g':	
				checkChar = fileIn.get();
				if (checkChar == ' ')
				{
					subsetIndexStart.push_back(vIndex);		
					subsetCount++;
				}
				break;

			case 'f':	
				checkChar = fileIn.get();
				if (checkChar == ' ')
				{
					face = L"";
					std::wstring VertDef;	
					triangleCount = 0;

					checkChar = fileIn.get();
					while (checkChar != '\n')
					{
						face += checkChar;			
						checkChar = fileIn.get();	
						if (checkChar == ' ')		
							triangleCount++;		
					}

					if (face[face.length() - 1] == ' ')
						triangleCount--;	
					triangleCount -= 1;		

					std::wstringstream ss(face);

					if (face.length() > 0)
					{
						int firstVIndex, lastVIndex;	

						for (int i = 0; i < 3; ++i)		
						{
							ss >> VertDef;	

							std::wstring vertPart;
							int whichPart = 0;		

							for (int j = 0; j < VertDef.length(); ++j)
							{
								if (VertDef[j] != '/')	
									vertPart += VertDef[j];

								if (VertDef[j] == '/' || j == VertDef.length() - 1)
								{
									std::wistringstream wstringToInt(vertPart);	

									if (whichPart == 0)	
									{
										wstringToInt >> vertPosIndexTemp;
										vertPosIndexTemp -= 1;		

										if (j == VertDef.length() - 1)
										{
											vertNormIndexTemp = 0;
											vertTCIndexTemp = 0;
										}
									}

									else if (whichPart == 1)	
									{
										if (vertPart != L"")	
										{
											wstringToInt >> vertTCIndexTemp;
											vertTCIndexTemp -= 1;
										}
										else	
											vertTCIndexTemp = 0;

										if (j == VertDef.length() - 1)
											vertNormIndexTemp = 0;

									}
									else if (whichPart == 2)	
									{
										std::wistringstream wstringToInt(vertPart);

										wstringToInt >> vertNormIndexTemp;
										vertNormIndexTemp -= 1;		
									}

									vertPart = L"";	
									whichPart++;	
								}
							}

							if (subsetCount == 0)
							{
								subsetIndexStart.push_back(vIndex);	
								subsetCount++;
							}

							bool vertAlreadyExists = false;
							if (totalVerts >= 3)	
							{
								for (int iCheck = 0; iCheck < totalVerts; ++iCheck)
								{
									if (vertPosIndexTemp == vertPosIndex[iCheck] && !vertAlreadyExists)
									{
										if (vertTCIndexTemp == vertTCIndex[iCheck])
										{
											indices.push_back(iCheck);
											vertAlreadyExists = true;
										}
									}
								}
							}

							if (!vertAlreadyExists)
							{
								vertPosIndex.push_back(vertPosIndexTemp);
								vertTCIndex.push_back(vertTCIndexTemp);
								vertNormIndex.push_back(vertNormIndexTemp);
								totalVerts++;	
								indices.push_back(totalVerts - 1);	
							}

							if (i == 0)
							{
								firstVIndex = indices[vIndex];	
							}

							if (i == 2)
							{
								lastVIndex = indices[vIndex];	
							}
							vIndex++;	
						}

						meshTriangles++;

						for (int l = 0; l < triangleCount - 1; ++l)	
						{
							indices.push_back(firstVIndex);		
							vIndex++;
							
							indices.push_back(lastVIndex);		
							vIndex++;

							ss >> VertDef;

							std::wstring vertPart;
							int whichPart = 0;

							for (int j = 0; j < VertDef.length(); ++j)
							{
								if (VertDef[j] != '/')
									vertPart += VertDef[j];
								if (VertDef[j] == '/' || j == VertDef.length() - 1)
								{
									std::wistringstream wstringToInt(vertPart);

									if (whichPart == 0)
									{
										wstringToInt >> vertPosIndexTemp;
										vertPosIndexTemp -= 1;

										if (j == VertDef.length() - 1)
										{
											vertTCIndexTemp = 0;
											vertNormIndexTemp = 0;
										}
									}
									else if (whichPart == 1)
									{
										if (vertPart != L"")
										{
											wstringToInt >> vertTCIndexTemp;
											vertTCIndexTemp -= 1;
										}
										else
											vertTCIndexTemp = 0;
										if (j == VertDef.length() - 1)
											vertNormIndexTemp = 0;

									}
									else if (whichPart == 2)
									{
										std::wistringstream wstringToInt(vertPart);

										wstringToInt >> vertNormIndexTemp;
										vertNormIndexTemp -= 1;
									}

									vertPart = L"";
									whichPart++;
								}
							}

							bool vertAlreadyExists = false;
							if (totalVerts >= 3)	
							{
								for (int iCheck = 0; iCheck < totalVerts; ++iCheck)
								{
									if (vertPosIndexTemp == vertPosIndex[iCheck] && !vertAlreadyExists)
									{
										if (vertTCIndexTemp == vertTCIndex[iCheck])
										{
											indices.push_back(iCheck);
											vertAlreadyExists = true;
										}
									}
								}
							}

							if (!vertAlreadyExists)
							{
								vertPosIndex.push_back(vertPosIndexTemp);
								vertTCIndex.push_back(vertTCIndexTemp);
								vertNormIndex.push_back(vertNormIndexTemp);
								totalVerts++;	
								indices.push_back(totalVerts - 1);	
							}
	
							lastVIndex = indices[vIndex];

							meshTriangles++;	
							vIndex++;
						}
					}
				}
				break;

			case 'm':	
				checkChar = fileIn.get();
				if (checkChar == 't')
				{
					checkChar = fileIn.get();
					if (checkChar == 'l')
					{
						checkChar = fileIn.get();
						if (checkChar == 'l')
						{
							checkChar = fileIn.get();
							if (checkChar == 'i')
							{
								checkChar = fileIn.get();
								if (checkChar == 'b')
								{
									checkChar = fileIn.get();
									if (checkChar == ' ')
									{
										fileIn >> meshMatLib;
									}
								}
							}
						}
					}
				}

				break;

			case 'u':	
				checkChar = fileIn.get();
				if (checkChar == 's')
				{
					checkChar = fileIn.get();
					if (checkChar == 'e')
					{
						checkChar = fileIn.get();
						if (checkChar == 'm')
						{
							checkChar = fileIn.get();
							if (checkChar == 't')
							{
								checkChar = fileIn.get();
								if (checkChar == 'l')
								{
									checkChar = fileIn.get();
									if (checkChar == ' ')
									{
										meshMaterialsTemp = L"";	

										fileIn >> meshMaterialsTemp; 

										meshMaterials.push_back(meshMaterialsTemp);
									}
								}
							}
						}
					}
				}
				break;

			default:
				break;
			}
		}
	}
	else	
	{
		m_swapChain->SetFullscreenState(false, NULL);	

		std::wstring message = L"Could not open: ";
		message += filename;

		MessageBox(0, message.c_str(),	
			L"Error", MB_OK);

		return false;
	}

	subsetIndexStart.push_back(vIndex); 

	if (subsetIndexStart[1] == 0)
	{
		subsetIndexStart.erase(subsetIndexStart.begin() + 1);
		meshSubsets--;
	}

	if (!hasNorm)
		vertNorm.push_back(XMFLOAT3(0.0f, 0.0f, 0.0f));
	if (!hasTexCoord)
		vertTexCoord.push_back(XMFLOAT2(0.0f, 0.0f));

	fileIn.close();
	fileIn.open(meshMatLib.c_str());

	std::wstring lastStringRead;
	int matCount = material.size();	

	bool kdset = false;

	if (fileIn)
	{
		while (fileIn)
		{
			checkChar = fileIn.get();	

			switch (checkChar)
			{
			case '#':
				checkChar = fileIn.get();
				while (checkChar != '\n')
					checkChar = fileIn.get();
				break;

			case 'K':
				checkChar = fileIn.get();
				if (checkChar == 'd')	
				{
					checkChar = fileIn.get();	

					fileIn >> material[matCount - 1].difColor.x;
					fileIn >> material[matCount - 1].difColor.y;
					fileIn >> material[matCount - 1].difColor.z;

					kdset = true;
				}

				if (checkChar == 'a')
				{
					checkChar = fileIn.get();
					if (!kdset)
					{
						fileIn >> material[matCount - 1].difColor.x;
						fileIn >> material[matCount - 1].difColor.y;
						fileIn >> material[matCount - 1].difColor.z;
					}
				}
				break;

			case 'T':
				checkChar = fileIn.get();
				if (checkChar == 'r')
				{
					checkChar = fileIn.get();	
					float Transparency;
					fileIn >> Transparency;

					material[matCount - 1].difColor.w = Transparency;

					if (Transparency > 0.0f)
						material[matCount - 1].transparent = true;
				}
				break;

			case 'd':
				checkChar = fileIn.get();
				if (checkChar == ' ')
				{
					float Transparency;
					fileIn >> Transparency;

					Transparency = 1.0f - Transparency;

					material[matCount - 1].difColor.w = Transparency;

					if (Transparency > 0.0f)
						material[matCount - 1].transparent = true;
				}
				break;

			case 'm':
				checkChar = fileIn.get();
				if (checkChar == 'a')
				{
					checkChar = fileIn.get();
					if (checkChar == 'p')
					{
						checkChar = fileIn.get();
						if (checkChar == '_')
						{
							checkChar = fileIn.get();
							if (checkChar == 'K')
							{
								checkChar = fileIn.get();
								if (checkChar == 'd')
								{
									std::wstring fileNamePath;

									fileIn.get();	

									bool texFilePathEnd = false;
									while (!texFilePathEnd)
									{
										checkChar = fileIn.get();

										fileNamePath += checkChar;

										if (checkChar == '.')
										{
											for (int i = 0; i < 3; ++i)
												fileNamePath += fileIn.get();

											texFilePathEnd = true;
										}
									}

									bool alreadyLoaded = false;
									for (int i = 0; i < textureNameArray.size(); ++i)
									{
										if (fileNamePath == textureNameArray[i])
										{
											alreadyLoaded = true;
											material[matCount - 1].texArrayIndex = i;
											material[matCount - 1].hasTexture = true;
										}
									}

									if (!alreadyLoaded)
									{
										ID3D11ShaderResourceView* tempMeshSRV;
										hr = DirectX::CreateWICTextureFromFile(m_d3d11Device, fileNamePath.c_str(), nullptr, &tempMeshSRV);
										if (SUCCEEDED(hr))
										{
											textureNameArray.push_back(fileNamePath.c_str());
											material[matCount - 1].texArrayIndex = meshSRV.size();
											meshSRV.push_back(tempMeshSRV);
											material[matCount - 1].hasTexture = true;
										}
									}
								}
							}

							else if (checkChar == 'd')
							{
								material[matCount - 1].transparent = true;
							}
						}
					}
				}
				break;

			case 'n':	
				checkChar = fileIn.get();
				if (checkChar == 'e')
				{
					checkChar = fileIn.get();
					if (checkChar == 'w')
					{
						checkChar = fileIn.get();
						if (checkChar == 'm')
						{
							checkChar = fileIn.get();
							if (checkChar == 't')
							{
								checkChar = fileIn.get();
								if (checkChar == 'l')
								{
									checkChar = fileIn.get();
									if (checkChar == ' ')
									{
										SurfaceMaterial tempMat;
										material.push_back(tempMat);
										fileIn >> material[matCount].matName;
										material[matCount].transparent = false;
										material[matCount].hasTexture = false;
										material[matCount].texArrayIndex = 0;
										matCount++;
										kdset = false;
									}
								}
							}
						}
					}
				}
				break;

			default:
				break;
			}
		}
	}
	else
	{
		m_swapChain->SetFullscreenState(false, NULL);	

		std::wstring message = L"Could not open: ";
		message += meshMatLib;

		MessageBox(0, message.c_str(),
			L"Error", MB_OK);

		return false;
	}

	for (int i = 0; i < meshSubsets; ++i)
	{
		bool hasMat = false;
		for (int j = 0; j < material.size(); ++j)
		{
			if (meshMaterials[i] == material[j].matName)
			{
				subsetMaterialArray.push_back(j);
				hasMat = true;
			}
		}
		if (!hasMat)
			subsetMaterialArray.push_back(0); 
	}

	std::vector<Vertex> vertices;
	Vertex tempVert;

	for (int j = 0; j < totalVerts; ++j)
	{
		tempVert.pos = vertPos[vertPosIndex[j]];
		tempVert.normal = vertNorm[vertNormIndex[j]];
		tempVert.texCoord = vertTexCoord[vertTCIndex[j]];

		vertices.push_back(tempVert);
	}

	if (computeNormals)
	{
		std::vector<XMFLOAT3> tempNormal;

		XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

		float vecX, vecY, vecZ;

		XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		for (int i = 0; i < meshTriangles; ++i)
		{
			vecX = vertices[indices[(i * 3)]].pos.x - vertices[indices[(i * 3) + 2]].pos.x;
			vecY = vertices[indices[(i * 3)]].pos.y - vertices[indices[(i * 3) + 2]].pos.y;
			vecZ = vertices[indices[(i * 3)]].pos.z - vertices[indices[(i * 3) + 2]].pos.z;
			edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);	

			vecX = vertices[indices[(i * 3) + 2]].pos.x - vertices[indices[(i * 3) + 1]].pos.x;
			vecY = vertices[indices[(i * 3) + 2]].pos.y - vertices[indices[(i * 3) + 1]].pos.y;
			vecZ = vertices[indices[(i * 3) + 2]].pos.z - vertices[indices[(i * 3) + 1]].pos.z;
			edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);	

			XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));
			tempNormal.push_back(unnormalized);			
		}

		XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		int facesUsing = 0;
		float tX;
		float tY;
		float tZ;

		for (int i = 0; i < totalVerts; ++i)
		{
			for (int j = 0; j < meshTriangles; ++j)
			{
				if (indices[j * 3] == i ||
					indices[(j * 3) + 1] == i ||
					indices[(j * 3) + 2] == i)
				{
					tX = XMVectorGetX(normalSum) + tempNormal[j].x;
					tY = XMVectorGetY(normalSum) + tempNormal[j].y;
					tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;

					normalSum = XMVectorSet(tX, tY, tZ, 0.0f);	
					facesUsing++;
				}
			}

			normalSum = normalSum / (float)facesUsing;

			normalSum = XMVector3Normalize(normalSum);

			vertices[i].normal.x = XMVectorGetX(normalSum);
			vertices[i].normal.y = XMVectorGetY(normalSum);
			vertices[i].normal.z = XMVectorGetZ(normalSum);

			normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			facesUsing = 0;
		}
	}

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * meshTriangles * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = &indices[0];
	m_d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, indexBuff);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * totalVerts;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = &vertices[0];
	hr = m_d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, vertBuff);

	return true;
}