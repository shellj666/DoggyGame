#include "Graphics.h"
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN

//Prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

//Pointers
Graphics *graphics;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR CmdLine, int CmdShow)
{
	MSG msg;
	HWND hwnd;
	if (!CreateMainWindow(hwnd, hInstance, CmdShow))
		return 1;

	graphics = new Graphics;
	graphics->InitislizeD3D(hwnd, ScreenWidth, ScreenHeight);
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				done = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			graphics->ShowBBuffer();
	}
	return 0;
}


LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int CmdShow)
{
	WNDCLASSEX wcx;
	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WinProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = ClassName;
	wcx.hIconSm = NULL;

	if (RegisterClassEx(&wcx) == 0)
		return false;
	hwnd = CreateWindow(ClassName, GameName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, ScreenWidth, ScreenHeight, (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID)NULL);
	if (!hwnd)
		return false;
	ShowWindow(hwnd, CmdShow);
	UpdateWindow(hwnd);
	return true;
}
