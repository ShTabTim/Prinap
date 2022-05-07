#include "Keys.h"

short m_keyOldState[256] = { 0 };
short m_keyNewState[256] = { 0 };
sKeyState m_keys[256], m_mouse[5];
POINT pt = { 0, 0 };
POINT ptOld = { 0, 0 };
POINT START = { 0, 0 };

bool m_mouseOldState[5] = { 0 };
bool m_mouseNewState[5] = { 0 };
void get_cur_pos(POINT& pptt) {
	GetCursorPos(&pptt); 
	pptt.x =  pptt.x - START.x;
	pptt.y = -pptt.y - START.y; 
}
sKeyState GetKey(int nKeyID) { return m_keys[nKeyID]; }
sKeyState GetMouse(int nMouseButtonID) { return m_mouse[nMouseButtonID]; }
void set_cursor(int x, int y) {
	SetCursorPos(x + START.x, -y -START.y); 
	get_cur_pos(pt);
}
int getdx() { return pt.x - ptOld.x; }
int getdy() { return pt.y - ptOld.y; }

int get_x() { return pt.x; }
int get_y() { return pt.y; }

void key_loop(HWND hwnd) {
	RECT wRect, cRect;
	GetWindowRect(hwnd, &wRect);
	GetClientRect(hwnd, &cRect);
	START.x = 0.5f * (wRect.right + wRect.left - cRect.right);
	START.y = -wRect.bottom + 0.15f * (wRect.bottom - wRect.top - cRect.bottom);
	for (int i = 0; i < 256; i++) {
		m_keyNewState[i] = GetAsyncKeyState(i);

		m_keys[i].bPressed = false;
		m_keys[i].bReleased = false;

		if (m_keyNewState[i] != m_keyOldState[i])
			if (m_keyNewState[i] & 0x8000) {
				m_keys[i].bPressed = !m_keys[i].bHeld;
				m_keys[i].bHeld = true;
			} else {
				m_keys[i].bReleased = true;
				m_keys[i].bHeld = false;
			}

		m_keyOldState[i] = m_keyNewState[i];
	}
	for (int m = 0; m < 5; m++) {
		m_mouse[m].bPressed = false;
		m_mouse[m].bReleased = false;

		if (m_mouseNewState[m] != m_mouseOldState[m])
			if (m_mouseNewState[m]) {
				m_mouse[m].bPressed = true;
				m_mouse[m].bHeld = true;
			}
			else {
				m_mouse[m].bReleased = true;
				m_mouse[m].bHeld = false;
			}
		m_mouseOldState[m] = m_mouseNewState[m];
	}
	ptOld = pt;
	get_cur_pos(pt);
}
