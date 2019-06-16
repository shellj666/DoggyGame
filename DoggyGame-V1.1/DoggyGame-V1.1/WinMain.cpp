#include<Windows.h>

//Global Variables
const char ClassName[] = "Class Name";
const char GameTitle[] = "Game Title";
int ScreenWidth = 500;
int ScreenHeight = 500;

//Prototypes
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int);
bool CreateMainWindow(HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hIn, HINSTANCE hInPrev, LPSTR CmdLine, int CmdShow)
{
	MSG msg;
	if (!CreateMainWindow(hIn, CmdShow))
		return false;
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
	}
	return msg.wParam;
}

//For handling windows events
LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//Creating the mmain window
bool CreateMainWindow(HINSTANCE hIn, int CmdShow)
{
	WNDCLASSEX wcx;
	HWND hwnd;

	wcx.cbSize = sizeof(wcx); // Size of structure
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WinProc;
	wcx.cbClsExtra = 0; // No extra class memory
	wcx.cbWndExtra = 0; // No extra window memory
	wcx.hInstance = hIn; // Handle to instance
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW); // Predefined arrow
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL; // Name of menu resource
	wcx.lpszClassName = ClassName; // Name of window class
	wcx.hIconSm = NULL;

	if (RegisterClassEx(&wcx) == 0)
		return false;
	hwnd = CreateWindow(ClassName, GameTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, ScreenWidth, ScreenHeight, (HWND)NULL, (HMENU)NULL, hIn, (LPVOID)NULL);
	if (!hwnd)
		return false;
	ShowWindow(hwnd, CmdShow);
	UpdateWindow(hwnd);
	return true;
}

