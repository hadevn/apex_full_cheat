#pragma once

#include "DXStateSaver.h"

#include <string>

#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include <vector>
#include "colors.h"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <memory>
#include <fstream>
#include "Color.h"


class Render
{
public:
	Render(ID3D11Device* device, IDXGISwapChain * pSwapChain);
	~Render();

public:
	void begin();
	void end();

private:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext *m_pContext;
	IDXGISwapChain * m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
};