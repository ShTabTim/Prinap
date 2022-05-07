#include "star_ss.h"
#include "../../FundLibs/noises/Simplex.h"
#include "../solar_sys_sc.h"
#include "../../game_objs/player.h"

SimplexNoise nnn;

void star_ss::init(uint32_t seed, solar_sys_sc* sys) {
	srand(seed);
	this->sc = sys;
	this->z = 2;
	float r = (1 + rand() % 255)/256.0f;
	float g = (1 + rand() % 255)/256.0f;
	float b = (1 + rand() % 255)/256.0f;
	scale *= 16.0f / half_size;
	blocks = new sptRGB();
	blocks->init(half_size * 2, half_size * 2);
	uint32_t id;
	float nois_scale = 0.1f;
	float ghj = 0.45f;
	if (r * r + g * g + b * b < 0.5f) {
		float l = 1.0f/sqrt(r * r + g * g + b * b);
		r = r * l;
		g = g * l;
		b = b * l;
	}
	uint8_t fr = 1 + rand() % 4;
	fract = 0.4f*sqrt(fr*sqrt(fr));
	for (uint16_t i(blocks->get_w()); i--;)
		for (uint16_t j(blocks->get_h()); j--;) {
			id = (blocks->get_h() * j + i)*3;
			(blocks->get_buf())[id++] = 255 * r * ((1-ghj)+ghj*nnn.fractal(fr, i * nois_scale, j * nois_scale, 0.1f + seed%16));
			(blocks->get_buf())[id++] = 255 * g * ((1-ghj)+ghj*nnn.fractal(fr, i * nois_scale, j * nois_scale, 0.3f + seed%16));
			(blocks->get_buf())[id  ] = 255 * b * ((1-ghj)+ghj*nnn.fractal(fr, i * nois_scale, j * nois_scale, 0.5f + seed%16));
		}
	a = [this](uint16_t i, uint16_t j) {
		float x = (((float)i)/half_size - 1)*3;
		float y = (((float)j)/half_size - 1)*3;
		float l = x*x + y*y;
		if (l > 9) return false;
		if (l < 4) return true;
		return (nnn.noise(x*fract, y*fract, t * activity) * 0.5f + tanh(3.2f - 0.3f * l) * 1.5f > 1);
	};
}
void star_ss::loop(float dt) {
	t += dt * 10.0f;
}
void star_ss::draw(dr_buf* db) {
	float f = (1 - (1 + sin(t)) * activity);
	
	db->draw_spt_scaled(
		((player*)(sc->get_cam()))->get_pos_from_player_x(-half_size * scale), 
		((player*)(sc->get_cam()))->get_pos_from_player_y(-half_size * scale), 
		((player*)(sc->get_cam()))->cam_scale * scale, 
		blocks, a, f, f, f);
}
void star_ss::finit() {
	blocks->finit();
}