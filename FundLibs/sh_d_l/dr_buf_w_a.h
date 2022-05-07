#pragma once
#include "dr_buf.h"

class dr_buf_w_a : public dr_buf{
protected:
	BITMAPINFO buf_info;
public:
	bool init(uint16_t w, uint16_t h);
	bool finit();

	void dr_in_cont(HDC* dc, uint32_t scr_w, uint32_t scr_h);
	~dr_buf_w_a();
};