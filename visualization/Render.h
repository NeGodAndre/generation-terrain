#pragma once
#include "stdafx.h"

using namespace DirectX;

struct Vertex	
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float u, float v,
		float nx, float ny, float nz)
		: pos(x, y, z), texCoord(u, v), normal(nx, ny, nz) {}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
	XMFLOAT3 normal;
};
struct cbPerObject
{
	XMMATRIX  WVP;
	XMMATRIX  World;

	XMFLOAT4 difColor;
	bool hasTexture;
};
struct Light
{
	Light()
	{
		ZeroMemory(this, sizeof(Light));
	}
	XMFLOAT3 dir;
	float pad;
	//float range;
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
};
struct cbPerFrame
{
	Light  light;
};
struct HeightMapInfo {
	int terrainWidth;
	int terrainHeight;
	XMFLOAT3 *heightMap;
};

//для obj//
struct SurfaceMaterial
{
	std::wstring matName;
	XMFLOAT4 difColor;
	int texArrayIndex;
	bool hasTexture;
	bool transparent;
};

class Render
{
public:
	Render();
	bool Init(HWND hwnd);
	void DrawScene();
	void UpdateScene();
	void UpdateCamera();
	void Close();

	void MoveBackForward(float step);
	void MoveLeftRight(float step);
	void Rotation(int x, int y, float rot);

private:
	bool InitScene();
	bool InitDirect(HWND hwnd);

	void m_createSphere(int LatLines, int LongLines);
	bool m_heightMapLoad(char* filename, HeightMapInfo &hminfo);
	void m_vectorToVertecAndDWORD(HeightMapInfo hmInfo, std::vector<Vertex>& v, std::vector<DWORD>& indices);
	//для Obj//
	bool m_loadObjModel(std::wstring filename,
		ID3D11Buffer** vertBuff,			
		ID3D11Buffer** indexBuff,			
		std::vector<int>& subsetIndexStart,	
		std::vector<int>& subsetMaterialArray,
		std::vector<SurfaceMaterial>& material,		
		int& subsetCount,	
		bool isRHCoordSys,		
		bool computeNormals);
	//для Obj//
	///////////////////////////
	UINT m_width;
	UINT m_height;
	///////////////////////////
	D3D_FEATURE_LEVEL m_featureLevel;

	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_d3d11Device;
	ID3D11DeviceContext* m_d3d11DeviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Buffer* m_squareIndexBuffer;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11Buffer* m_squareVertBuffer;
	ID3D11VertexShader* m_VS;
	ID3D11PixelShader* m_PS;
	ID3D10Blob* m_VSBuffer;
	ID3D10Blob* m_PSBuffer;

	ID3D11PixelShader* m_D2D_PS;
	ID3D10Blob* m_D2D_PS_Buffer;

	ID3D11InputLayout* m_vertLayout;

	ID3D11Buffer* m_cbPerObjectBuffer;
	ID3D11RasterizerState* m_CCWcullMode;
	ID3D11RasterizerState* m_CWcullMode;
	ID3D11ShaderResourceView* m_cubesTexture;
	ID3D11SamplerState* m_cubesTexSamplerState;
	ID3D11Buffer* m_cbPerFrameBuffer;

	ID3D11Texture2D* m_backBuffer11;//?

	////
	ID3D11Buffer* m_sphereIndexBuffer;
	ID3D11Buffer* m_sphereVertBuffer;

	ID3D11VertexShader* m_SKYMAP_VS;
	ID3D11PixelShader* m_SKYMAP_PS;
	ID3D10Blob* m_SKYMAP_VS_Buffer;
	ID3D10Blob* m_SKYMAP_PS_Buffer;
	ID3D11ShaderResourceView* m_smrv;

	ID3D11DepthStencilState* m_DSLessEqual;
	ID3D11RasterizerState* m_RSCullNone;

	int m_numSphereVertices;
	int m_numSphereFaces;

	XMMATRIX sphereWorld;

	XMMATRIX rotationx;
	XMMATRIX rotationy;
	XMMATRIX rotationz;

	XMMATRIX WVP;
	XMMATRIX cube1World;
	XMMATRIX cube2World;
	XMMATRIX camView;
	XMMATRIX camProjection;
	XMMATRIX d2dWorld;

	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;
	XMVECTOR defaultForward;
	XMVECTOR defaultRight;
	XMVECTOR camForward;
	XMVECTOR camRight;

	XMMATRIX camRotationMatrix;
	XMMATRIX groundWorld;

	float moveLeftRight;
	float moveBackForward;

	float camYaw;
	float camPitch;
	//
	XMMATRIX rotation;
	XMMATRIX scale;
	XMMATRIX translation;
	float rot;

	cbPerObject cbPerObj;
	Light light;

	float rotx = 0;
	float rotz = 0;
	float scaleX = 1.0f;
	float scaleY = 1.0f;

	int NumFaces = 0;
	int NumVertices = 0;

	//для Obj//
	ID3D11BlendState* Transparency;

	ID3D11Buffer* meshVertBuff;
	ID3D11Buffer* meshIndexBuff;
	XMMATRIX meshWorld;
	int meshSubsets = 0;
	std::vector<int> meshSubsetIndexStart;
	std::vector<int> meshSubsetTexture;

	std::vector<ID3D11ShaderResourceView*> meshSRV;
	std::vector<std::wstring> textureNameArray;

	std::vector<SurfaceMaterial> material;
	//для Obj//
};
