#pragma once
#include <cstdint>
#include "scene.h"
#include "solar_obj/star_ss.h"
#include "solar_obj/planet_ss.h"


class solar_sys_sc : public scene {
private:
	uint8_t count_of_stars;
	uint8_t count_of_planets;
	std::wstring m_file;
public:
	void init(uint32_t seed, std::wstring file_name);
	void draw_sc(dr_buf* db);
	std::wstring get_file_name();
};