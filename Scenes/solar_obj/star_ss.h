#pragma once
#include <cstdint>
#include <functional>
#include "../../game_objs/g_object.h"
class solar_sys_sc;

class star_ss : public g_object{
private:
	float activity = 0.2f;
	float scale = 10;
	uint16_t half_size = 16;
	std::function<bool(uint16_t, uint16_t)> a;
	float t = 0;
	float fract;
	solar_sys_sc* sc;
public:
	void init(uint32_t seed, solar_sys_sc* sys);
	void loop(float dt);
	void draw(dr_buf* db);
	void finit();
};