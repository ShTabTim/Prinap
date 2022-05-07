#pragma once
#include "scene.h"
#include "../game_objs/meta_planet.h"

class planet_sc : public scene {
private:
	vec2f pos;
public:
	void init();
	void loop_sc(float dt);
	void draw_sc(dr_buf* db);
};