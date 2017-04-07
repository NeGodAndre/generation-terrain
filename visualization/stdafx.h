#pragma once

#include <clocale>
#include <ctime>

#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <D3D11.h>
#include <d3d10.h>
#include <DirectXMath.h>
#include <D3Dcompiler.h>

#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include <Keyboard.h>
#include <Mouse.h>

#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3D10.lib")
#pragma comment(lib, "D3DCompiler.lib")

#pragma comment (lib, "DirectXTK.lib")