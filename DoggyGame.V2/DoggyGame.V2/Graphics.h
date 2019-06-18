#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <d3d9.h>
#include "Constants.h"
#define WIN32_LEAN_AND_MEAN

#define LP3DDEVICE LPDIRECT3DDEVICE9
#define LP3DDIRECT LPDIRECT3D9
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

class Graphics
{
public:
	Graphics();
	virtual ~Graphics();
	void InitislizeD3D(HWND hw, int Width, int Height);
	HRESULT ShowBBuffer();

private:
	LP3DDEVICE LPDDevice;
	LP3DDIRECT LPDDirect;
	D3DPRESENT_PARAMETERS D3DParameters;
	HRESULT hr;
	HWND hwnd;
	int Width;
	int Height;
	void initD3Dpp();
};
#endif // !GRAPHICS_H