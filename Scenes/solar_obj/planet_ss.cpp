#include "planet_ss.h"
#include "../../game_objs/player.h"
#include "../solar_sys_sc.h"
#include "../../FundLibs/Keys/Keys.h"

void planet_ss::init(meta_planet* m_pl, solar_sys_sc* sys) {
	this->m_pl = m_pl;
	this->sc = sys;
	this->z = 2;
	this->blocks = m_pl->blocks;
}
void planet_ss::loop(float dt) {
	t += 10*dt;
	float g = m_pl->a - m_pl->c * cos(m_pl->teta);
	m_pl->teta += dt * g * g * m_pl->w * 0.000005f;
	m_pl->r = m_pl->get_r(m_pl->teta);
	get_pos().x = sin(m_pl->teta + m_pl->alpha) * m_pl->r;
	pos.y = cos(m_pl->teta + m_pl->alpha) * m_pl->r;
}
void planet_ss::draw(dr_buf* db) {
	float tet = atan2(2 * m_pl->half_size*m_pl->scale, m_pl->r), t0 = m_pl->teta + tet;
	float r_c = m_pl->get_r(t0), r_x, r_y, 
		old_r_x = sin(m_pl->alpha+t0) * r_c, 
		old_r_y = cos(m_pl->alpha+t0) * r_c;
	for (float alp(0); alp < 6.2831f - 2 * tet; alp += 0.1f) {
		r_c = m_pl->get_r(t0 + alp);
		r_x = sin(alp + m_pl->alpha + t0) * r_c; r_y = cos(alp + m_pl->alpha + t0) * r_c;
		db->draw_line(
			((player*)(sc->get_cam()))->get_pos_from_player_x(r_x), 
			((player*)(sc->get_cam()))->get_pos_from_player_y(r_y), 
			((player*)(sc->get_cam()))->get_pos_from_player_x(old_r_x), 
			((player*)(sc->get_cam()))->get_pos_from_player_y(old_r_y), 
			m_pl->orb_r, m_pl->orb_g, m_pl->orb_b);
		old_r_x = r_x; old_r_y = r_y;
	}
	r_c = m_pl->get_r(t0-2*tet);
	r_x = sin(m_pl->alpha + t0 - 2 * tet) * r_c; r_y = cos(m_pl->alpha + t0 - 2 * tet) * r_c;
	db->draw_line(
		((player*)(sc->get_cam()))->get_pos_from_player_x(r_x),
		((player*)(sc->get_cam()))->get_pos_from_player_y(r_y),
		((player*)(sc->get_cam()))->get_pos_from_player_x(old_r_x),
		((player*)(sc->get_cam()))->get_pos_from_player_y(old_r_y),
		m_pl->orb_r, m_pl->orb_g, m_pl->orb_b);
	float c_x = ((player*)(sc->get_cam()))->get_pos_from_player_x(pos.x), c_y = ((player*)(sc->get_cam()))->get_pos_from_player_y(pos.y), r = 2 * m_pl->scale * m_pl->half_size * ((player*)(sc->get_cam()))->cam_scale;
	if ((c_x - get_x() * ((player*)(sc->get_cam()))->get_w_c()) * (c_x - get_x() * ((player*)(sc->get_cam()))->get_w_c()) + (c_y - get_y() * ((player*)(sc->get_cam()))->get_h_c()) * (c_y - get_y() * ((player*)(sc->get_cam()))->get_h_c()) < 1.2f * r * r) {
		float n_r = 2 * r *(1 + 0.1f*sin(t+1)), s_t = 1.2f + 0.2f * sin(t), c_t = 0.6f * (1 + 0.1f * cos(t));
		uint8_t _r = m_pl->orb_r * m_pl->orb_b, _g = m_pl->orb_g * m_pl->orb_r, _b = m_pl->orb_b * m_pl->orb_g;
		db->draw_line(c_x - n_r*s_t, c_y, c_x - n_r*c_t, c_y, _r, _g, _b);
		db->draw_line(c_x + n_r*s_t, c_y, c_x + n_r*c_t, c_y, _r, _g, _b);
		db->draw_line(c_x, c_y + n_r*s_t, c_x, c_y + n_r*c_t, _r, _g, _b);
		db->draw_line(c_x, c_y - n_r*s_t, c_x, c_y - n_r*c_t, _r, _g, _b);
		db->draw_circ(c_x, c_y, n_r, _r * _g, _g * _b, _b * _r);
	}
	db->draw_circ(c_x, c_y, r, m_pl->orb_r, m_pl->orb_g, m_pl->orb_b);
	db->draw_spt_scaled(
		((player*)(sc->get_cam()))->get_pos_from_player_x(-m_pl->half_size * m_pl->scale + pos.x), 
		((player*)(sc->get_cam()))->get_pos_from_player_y(-m_pl->half_size * m_pl->scale + pos.y), 
		((player*)(sc->get_cam()))->cam_scale * m_pl->scale,
		blocks);
}
void planet_ss::finit() {
	blocks->finit();
}