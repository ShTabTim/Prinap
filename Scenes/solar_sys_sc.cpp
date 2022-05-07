#include "solar_sys_sc.h"

void solar_sys_sc::init(uint32_t seed, std::wstring file_name) {
	srand(seed);

	count_of_planets = sqrt(1 + 3 * (rand() % 9));
	count_of_stars = 1;// +rand() % 6;

	((star_ss*)(o_mgr.get_obj(o_mgr.add_obj(new star_ss()))))->init(seed, this);

	float del_a = 4.5f +(rand() % 100) * 0.01f;
	float tg_k = 0.5f+(rand()%8)/7.0f;
	float ccc = 20 + rand() % 40;
	float l = 40.0f + rand() % 20;

	for (uint8_t k(count_of_planets); k--;) {
		float a = 1 + del_a*pow(2, k*tg_k);
		meta_planet* pl = new meta_planet();
		pl->init(NULL, seed + rand(), ccc / (a * a * a), rand() % 8, rand() % 8, 1 + k * 0.5f, l * a, a * (rand() % 12) * 0.3f);
		((planet_ss*)(o_mgr.get_obj(o_mgr.add_obj(new planet_ss()))))->init(pl, this);
	}
	o_mgr.update_z();
}
void solar_sys_sc::draw_sc(dr_buf* db) {
	o_mgr.draw(db);
	//db->fill_circ(128, 128, 100, 255, 255, 255);
}
std::wstring solar_sys_sc::get_file_name() { return m_file; }