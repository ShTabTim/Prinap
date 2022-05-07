#pragma once
#include <Windows.h>

typedef struct sKeyState {
	bool bPressed;
	bool bReleased;
	bool bHeld;
}sKeyState;

void key_loop(HWND hWnd);
sKeyState GetKey(int nKeyID);
sKeyState GetMouse(int nMouseButtonID);
void set_cursor(int x, int y);
int get_x();
int get_y();
int getdx();
int getdy();