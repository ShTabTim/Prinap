#pragma once
#include "../FundLibs/sh_d_l/sprite.h"

class meta_planet {
public:
	uint8_t orb_r = 255, orb_g = 255, orb_b = 255;
	uint16_t half_size = 16;
	uint32_t a = 200, c = 50;
	float w = 1;
	float r;
	float scale = 1;
	float teta = 1, alpha = 1;
	sptRGB* blocks;
	void init(sptRGB* blocks = NULL, uint32_t seed = 0, float w = 1.0f, float teta = 0, float alpha = 0, float scale = 1, uint32_t a = 200, uint32_t c = 50);
	void generate(uint32_t seed = 0);
	float get_r(float alpha);
};