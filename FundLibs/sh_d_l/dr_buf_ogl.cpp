#include "dr_buf_ogl.h"


bool dr_buf_ogl::init(uint16_t w, uint16_t h) {
	this->w = w;
	this->h = h;
	buf = new col[w * h];
	memset(buf, 0, sizeof(uint8_t) * w * h * 3);

	memset(&buf_info, 0, sizeof(BITMAPINFOHEADER));

	buf_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	buf_info.bmiHeader.biPlanes = 1;
	buf_info.bmiHeader.biBitCount = 24;
	buf_info.bmiHeader.biCompression = BI_RGB;
	buf_info.bmiHeader.biWidth = w;
	buf_info.bmiHeader.biHeight = h;
	return 1;
}

bool dr_buf_ogl::finit() { if (buf) delete[] buf; else return 0; buf = NULL; return 1; }

void dr_buf_ogl::dr_in_cont(HDC* dc, uint32_t scr_w, uint32_t scr_h) {
	if (buf) {
		if (scr_w == scr_h)
			StretchDIBits(*dc, 0, 0, scr_w, scr_h, 0, 0, w, h, buf, &buf_info, DIB_RGB_COLORS, SRCCOPY);
		else if (scr_w > scr_h)
			StretchDIBits(*dc, (scr_w - scr_h) * 0.5f, 0, scr_h, scr_h, 0, 0, w, h, buf, &buf_info, DIB_RGB_COLORS, SRCCOPY);
		else
			StretchDIBits(*dc, 0, (scr_h - scr_w) * 0.5f, scr_w, scr_w, 0, 0, w, h, buf, &buf_info, DIB_RGB_COLORS, SRCCOPY);
	}
}

dr_buf_ogl::~dr_buf_ogl() { finit(); }