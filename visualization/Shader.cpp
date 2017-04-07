#include "stdafx.h"
#include "Shader.h"

//using namespace DirectX;

Shader::Shader(RenderDevice * renderDevice)
{
	m_renderDevice = renderDevice;
	m_PS = nullptr;
	m_VS = nullptr;
	m_vertLayout = nullptr;

	VSBuffer = nullptr;
	PSBuffer = nullptr;

	m_texture = nullptr;
	m_sampleState = nullptr;
}

HRESULT Shader::m_compileShaderFromFile(wchar_t* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel, ID3DBlob** Buffer)
{
	HRESULT hr;
	ID3DBlob *pErrorBlob = nullptr;
	hr = D3DCompileFromFile(FileName, NULL, NULL, EntryPoint, ShaderModel, 0, 0, Buffer, &pErrorBlob);
	if (FAILED(hr))
	{
		Log::Get()->Err((char*)pErrorBlob->GetBufferPointer());
	}
	return hr;
}
HRESULT Shader::m_createSamplerState()
{
	HRESULT hr;
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = m_renderDevice->m_d3d11Device->CreateSamplerState(&sampDesc, &m_sampleState);
	return hr;
}

bool Shader::CreateShader(wchar_t * fileNameVS, wchar_t * fileNamePS, LPCSTR nameVS, LPCSTR namePS)
{
	HRESULT hr;
	
	hr = m_compileShaderFromFile(fileNameVS, nameVS, "vs_4_0", &VSBuffer);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не скомпилировался vertex buffer");
		return false;
	}
	hr = m_compileShaderFromFile(fileNamePS, namePS, "ps_4_0", &PSBuffer);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не скомпилировался pixel buffer");
		return false;
	}
	hr = m_renderDevice->m_d3d11Device->CreateVertexShader(VSBuffer->GetBufferPointer(), VSBuffer->GetBufferSize(), NULL, &m_VS);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан Vertex Shader");
		return false;
	}
	hr = m_renderDevice->m_d3d11Device->CreatePixelShader(PSBuffer->GetBufferPointer(), PSBuffer->GetBufferSize(), NULL, &m_PS);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан Pixel Shader");
		return false;
	}
	m_renderDevice->m_d3d11DeviceContext->VSSetShader(m_VS, NULL, 0);
	m_renderDevice->m_d3d11DeviceContext->PSSetShader(m_PS, NULL, 0);
	return true;
}

void Shader::InputElementLayout(D3D11_INPUT_ELEMENT_DESC * layout, UINT numElements)
{
	m_layout = layout;
	m_numElements = numElements;
}
bool Shader::CreateInputLayout()
{
	HRESULT hr;
	hr = m_renderDevice->m_d3d11Device->CreateInputLayout(m_layout, m_numElements, VSBuffer->GetBufferPointer(),
		VSBuffer->GetBufferSize(), &m_vertLayout);
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан Input Layout");
		return false;
	}

	m_renderDevice->m_d3d11DeviceContext->IASetInputLayout(m_vertLayout);

	m_renderDevice->m_d3d11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}

bool Shader::LoadWICTexture(const wchar_t *name)
{
	HRESULT hr;

	hr = DirectX::CreateWICTextureFromFile(m_renderDevice->m_d3d11Device, name, NULL, &m_texture);
	if (FAILED(hr))
	{
		Log::Get()->Err("Текстура из файла ", name, " не создана");
		return false;
	}
	hr = m_createSamplerState();
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан Sample State к файлу ", name);
		return false;
	}
	return true;
}
bool Shader::LoadDDSTexture(const wchar_t *name)
{
	HRESULT hr;

	hr = DirectX::CreateDDSTextureFromFile(m_renderDevice->m_d3d11Device, name, NULL, &m_texture);
	if (FAILED(hr))
	{
		Log::Get()->Err("Текстура из файла ", name, " не создана");
		return false;
	}
	hr = m_createSamplerState();
	if (FAILED(hr))
	{
		Log::Get()->Err("Не создан Sample State к файлу ", name);
		return false;
	}
	return true;
}
void Shader::Draw()
{
	m_renderDevice->m_d3d11DeviceContext->VSSetShader(m_VS, NULL, 0);
	m_renderDevice->m_d3d11DeviceContext->PSSetShader(m_PS, NULL, 0);
	if(m_texture)
		m_renderDevice->m_d3d11DeviceContext->PSSetShaderResources(0, 1, &m_texture);
	if(m_sampleState)
		m_renderDevice->m_d3d11DeviceContext->PSSetSamplers(0, 1, &m_sampleState);

	m_renderDevice->m_swapChain->Present(0, 0);
}
void Shader::Close()
{
	m_PS->Release();
	m_VS->Release();
	if (m_vertLayout)
		m_vertLayout->Release();
	if (m_texture)
		m_texture->Release();
	if (m_sampleState)
		m_sampleState->Release();
}
