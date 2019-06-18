#include "Graphics.h"

Graphics::Graphics()
{
	LPDDirect = NULL;
	LPDDevice = NULL;
}

Graphics::~Graphics()
{

}

void Graphics::InitislizeD3D(HWND hw, int ScreenW, int ScreenH)
{
	hwnd = hw;
	ScreenW = ScreenWidth;
	ScreenH = ScreenHeight;

	LPDDirect = Direct3DCreate9(D3D_SDK_VERSION);
	initD3Dpp();

	D3DCAPS9 Caps;
	DWORD Behavior;
	hr = LPDDirect->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps);
	if ((Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 || Caps.VertexShaderVersion < D3DVS_VERSION(1, 1))Behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else Behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	hr = LPDDirect->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, Behavior, &D3DParameters, &LPDDevice);
}

void Graphics::initD3Dpp()
{
		ZeroMemory(&D3DParameters, sizeof(D3DParameters));
		D3DParameters.BackBufferWidth = Width;
		D3DParameters.BackBufferHeight = Height;
		D3DParameters.BackBufferFormat = D3DFMT_UNKNOWN;
		D3DParameters.BackBufferCount = 1;
		D3DParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		D3DParameters.hDeviceWindow = hwnd;
		D3DParameters.Windowed = true;
		D3DParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

HRESULT Graphics::ShowBBuffer()
{
	LPDDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 0.0f, 0);
	hr = LPDDevice->Present(NULL, NULL, NULL, NULL);
	return hr;
}