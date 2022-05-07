#include "ShWin.h"
#include <chrono>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) {
	if (uiMsg == WM_CLOSE)
		PostQuitMessage(0);
	else
		return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	return 0;
}

bool ShWinRendCPU::init(HINSTANCE hInst, uint32_t W, uint32_t H, uint16_t w, uint16_t h) {
    WNDCLASSEX wcex;

    memset(&wcex, 0, sizeof(WNDCLASSEX));

	width = W;
	height = H;

    db.init(w, h);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = AppName.c_str() + 1;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (RegisterClassEx(&wcex) == 0)
        return MessageBox(NULL, L"RegisterClassEx failed!", L"hhhh", MB_ERR_INVALID_CHARS), false;

    if ((hWnd = CreateWindow(
		wcex.lpszClassName,
		AppName.c_str(), 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width, 
		height, 
		NULL, 
		NULL, 
		hInst, 
		NULL)) == NULL)
        return MessageBox(NULL, L"CreateWindowEx failed!", L"hhhh", MB_ERR_INVALID_CHARS), false;
    return 1;
}

void ShWinRendCPU::Start() {
	Show(false);
	Rend();
}

uint32_t ShWinRendCPU::ScreenW() { return db.get_w(); }
uint32_t ShWinRendCPU::ScreenH() { return db.get_h(); }

uint32_t  ShWinRendCPU::get_width() { return  width; }
uint32_t ShWinRendCPU::get_height() { return height; }

void ShWinRendCPU::Rend() {

	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	MSG msg;

	RECT rect;

	GetClientRect(hWnd, &rect);

	HDC dc = GetDC(hWnd);

	initSim();

	while (1) {
		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

			tp2 = std::chrono::system_clock::now();
			std::chrono::duration<float> dTime = tp2 - tp1;
			tp1 = tp2;
			float dt = dTime.count();

			if (!loopSim(dt))
				break;

			wchar_t s[64];
			swprintf_s(s, 64, L"ConsoleRenderer - %s - FPS: %5.2f", AppName.c_str(), 1.0f / dt);

			SetWindowText(hWnd, s);

			RECT cRect;
			GetClientRect(hWnd, &cRect);

			width = cRect.right;
			height = cRect.bottom;

			db.dr_in_cont(&dc, width, height);
		}
	}

	if (finitSim())
		db.finit();

	PostMessage(hWnd, WM_DESTROY, 0, 0);
}

void ShWinRendCPU::Show(bool Maximized) {
    RECT dRect, wRect, cRect;

    GetWindowRect(GetDesktopWindow(), &dRect);
    GetWindowRect(hWnd, &wRect);
    GetClientRect(hWnd, &cRect);

    wRect.right  += width - cRect.right ;
    wRect.bottom += height - cRect.bottom;

    wRect.right  -= wRect.left;
    wRect.bottom -= wRect.top ;

    wRect.left = (dRect.right  - wRect.right ) >> 1;
    wRect.top  = (dRect.bottom - wRect.bottom) >> 1;

    MoveWindow(hWnd, wRect.left, wRect.top, wRect.right, wRect.bottom, FALSE);

    ShowWindow(hWnd, Maximized ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);
}