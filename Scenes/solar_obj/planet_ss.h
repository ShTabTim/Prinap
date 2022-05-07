#pragma once
#include <cstdint>
#include "../../game_objs/meta_planet.h"
#include "../../game_objs/g_object.h"
class solar_sys_sc;

class planet_ss : public g_object{
private:
	meta_planet* m_pl;
	solar_sys_sc* sc;
	float t = 0;
public:
	void init(meta_planet* m_pl, solar_sys_sc* sys);
	void loop(float dt);
	void draw(dr_buf* db);
	void finit();
};