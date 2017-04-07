#pragma once

#include "stdafx.h"
#include "RenderDevice.h"
#include "Log.h"
#include <WICTextureLoader.h>

using namespace DirectX;

class Shader
{
public:
	Shader(RenderDevice *renderDevice);
	bool CreateShader(wchar_t * fileNameVS, wchar_t * fileNamePS, LPCSTR nameVS, LPCSTR namePS);
	void InputElementLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements);
	bool CreateInputLayout();
	bool LoadWICTexture(const wchar_t *name);
	bool LoadDDSTexture(const wchar_t *name);
	void Draw();

	void Close();
private:
	HRESULT m_compileShaderFromFile(wchar_t* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel, ID3DBlob** Buffer);
	HRESULT m_createSamplerState();

	RenderDevice* m_renderDevice;
	ID3D11VertexShader* m_VS;
	ID3D11PixelShader* m_PS;
	ID3D11InputLayout* m_vertLayout;

	ID3D10Blob* VSBuffer;
	ID3D10Blob* PSBuffer;

	ID3D11ShaderResourceView* m_texture;
	ID3D11SamplerState *m_sampleState;

	D3D11_INPUT_ELEMENT_DESC* m_layout;
	UINT m_numElements;
};