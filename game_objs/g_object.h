#pragma once
#include "../FundLibs/math/vec2.h"
#include "../FundLibs/sh_d_l/dr_buf.h"

class g_object {
protected:
	vec2f pos;
	sptRGB* blocks;
public:
	uint32_t z = 0;
	virtual void loop(float dt) = 0;
	virtual void draw(dr_buf* db) = 0;
	virtual void finit() = 0;
	vec2f& get_pos();
};