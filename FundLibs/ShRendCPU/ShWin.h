#pragma once
#include <Windows.h>
#include "../sh_d_l/dr_buf_w_a.h"
#include "../sh_d_l/dr_buf_ogl.h"
#include <string>

#define USE_DR_BUF_W_A
//#define USE_DR_BUF_OGL

/* For users:
class MainRenderer : public ShWinRendCPU {
	bool initSim() {
		AppName = L"//name//";
		//Inittsialize yuor simulation
		return true;
	}
	bool loopSim(float dt) {
		//Draw whis db.DrawPixel/DrawLine and other
		return true;
	}
	bool finitSim() {
		//Finitsialize yuor simulation
		return true;
	}
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR sCmdLine, int iShow){
	MainRenderer simulation;
	if (simulation.init(hInst, ScrWW, ScrHH, WndProc))
		simulation.Start();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam){
	if(uiMsg == WM_CLOSE)
		PostQuitMessage(0);
	else
        return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	return 0;
}
*/
typedef struct ShWinRendCPU {
private:
	void Rend();
protected:
	uint32_t width, height;
#if defined(USE_DR_BUF_W_A)
	dr_buf_w_a db;
#elif defined(USE_DR_BUF_OGL)
	dr_buf_ogl db;
#endif

	HWND hWnd;
	std::wstring AppName = L"Renderer";

	virtual bool initSim() = 0;
	virtual bool loopSim(float dt) = 0;
	virtual bool finitSim() = 0;
public:
	bool init(HINSTANCE hInst, uint32_t W, uint32_t H, uint16_t w, uint16_t h);
	void Start();

	uint32_t ScreenW();
	uint32_t ScreenH();

	uint32_t get_width();
	uint32_t get_height();

	void Show(bool Maximized);
}ShWin;