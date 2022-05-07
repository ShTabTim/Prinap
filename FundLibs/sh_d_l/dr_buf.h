#pragma once
#include <cstdint>
#include <windows.h>
#include <functional>
#include "sprite.h"

class dr_buf {
protected:
	typedef struct col {uint8_t b, g, r; }col;
	void dr_in_buf(uint32_t index, uint8_t r, uint8_t g, uint8_t b);
	void add_in_buf(uint32_t index, uint8_t r, uint8_t g, uint8_t b);
	void mix_in_buf(uint32_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void clip(int32_t& x, int32_t& y);
	col* buf;
	uint16_t w, h;
public:
	virtual bool init(uint16_t w, uint16_t h) = 0;
	virtual bool finit() = 0;

	uint8_t* get_buf();
	uint16_t get_w();
	uint16_t get_h();

	void fill_rect(int32_t x0, int32_t  y0, int32_t w1, int32_t h1, uint8_t r, uint8_t g, uint8_t b);

	void draw_pix(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b);
	void add_pix(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b);
	void mix_pix(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t r, uint8_t g, uint8_t b);

	void fill_triang(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t r, uint8_t g, uint8_t b);

	void draw_circ(int32_t x, int32_t y, int32_t rad, uint8_t r, uint8_t g, uint8_t b);
	void fill_circ(int32_t x, int32_t y, int32_t rad, uint8_t r, uint8_t g, uint8_t b);

	//NORMAL//
	void draw_spt(int32_t x, int32_t y, sptG* spt);
	void draw_spt(int32_t x, int32_t y, sptG* spt, float g);
	void draw_spt(int32_t x, int32_t y, int32_t w, int32_t h, sptG* spt);
	//SCALED//
	void draw_spt_scaled(int32_t x, int32_t y, float scale, sptG* spt);
	void draw_spt_offseted(int32_t x, int32_t y, int16_t o_x, int16_t o_y, sptG* spt);
	//LAMBDA//
	void draw_spt(int32_t x, int32_t y, sptG* spt, std::function<bool(uint16_t, uint16_t)> a);
	void draw_spt(int32_t x, int32_t y, sptG* spt, std::function<bool(uint16_t, uint16_t)> a, float g);
	void draw_spt_scaled(int32_t x, int32_t y, float scale, sptG* spt, std::function<bool(uint16_t, uint16_t)> a, float g);

	void draw_spt(int32_t x, int32_t y, sptRGB* spt);
	void draw_spt_offseted(int32_t x, int32_t y, int16_t o_x, int16_t o_y, sptRGB* spt);
	void draw_spt(int32_t x, int32_t y, sptRGB* spt, float r, float g, float b);
	void draw_spt(int32_t x, int32_t y, sptRGB* spt, std::function<bool(uint16_t, uint16_t)> a);
	void draw_spt_scaled(int32_t x, int32_t y, float scale, sptRGB* spt);
	void draw_spt(int32_t x, int32_t y, int32_t w, int32_t h, sptRGB* spt);
	void draw_spt_scaled(int32_t x, int32_t y, float scale, sptRGB* spt, std::function<bool(uint16_t, uint16_t)> a, float r, float g, float b);
	void draw_spt(int32_t x, int32_t y, sptRGB* spt, std::function<bool(uint16_t, uint16_t)> a, float r, float g, float b);

	void draw_spt(int32_t x, int32_t y, sptRGBA* spt);
	void draw_spt(int32_t x, int32_t y, int32_t w, int32_t h, sptRGBA* spt);

	virtual void dr_in_cont(HDC* dc, uint32_t scr_w, uint32_t scr_h) = 0;
	//~dr_buf();
};