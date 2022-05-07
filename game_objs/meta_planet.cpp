#include "meta_planet.h"

void meta_planet::init(sptRGB* blocks, uint32_t seed, float w, float teta, float alpha, float scale, uint32_t a, uint32_t c) {
	this->a = a;
	this->c = c;
	this->scale = scale;
	this->teta = teta;
	this->alpha = alpha;
	this->w = w;
	orb_r = 128 + rand()%128; 
	orb_g = 128 + rand()%128; 
	orb_b = 128 + rand()%128;
	if (!blocks)
		generate(seed);
	else
		this->blocks = blocks;
}

void meta_planet::generate(uint32_t seed) {
	blocks = new sptRGB();
	blocks->init(half_size * 2, half_size * 2);
	uint8_t* gh;
	for (uint16_t i((this->blocks)->get_w()); i--;)
		for (uint16_t j((this->blocks)->get_h()); j--;) {
			gh = blocks->get_buf() + (blocks->get_w() * j + i) * 3;
			*(gh++) = rand() % 256;
			*(gh++) = rand() % 256;
			*(gh  ) = rand() % 256;
		}
}

float meta_planet::get_r(float alp) {
	return (a * a - c * c) / (a - c*cos(alp));
}