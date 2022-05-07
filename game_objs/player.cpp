#include "player.h"
#include "../FundLibs/Keys/Keys.h"

vec2f clamped(vec2f v, float max_abs) {
    if (v.abs2() > max_abs*max_abs) v.norm(max_abs);
    return v;
}

void player::init(ShWinRendCPU* r) {
    z = 1;
    pos.x = 0;
    pos.y = 0;
    m_sh_r_c = r;
    blocks = new sptRGB();
    blocks->init(16, 16);
    for (uint32_t fg(768); fg--; blocks->get_buf()[fg] = rand());
}

void player::loop(float dt) {
    dt *= 10;

    cam_scale += (GetKey(VK_SPACE).bHeld - GetKey(VK_SHIFT).bHeld) * cam_scale * cam_scale * dt;
    cam_scale = min(1, cam_scale);

    dv.x = GetKey('D').bHeld - GetKey('A').bHeld;
    dv.y = GetKey('W').bHeld - GetKey('S').bHeld;

    if (dv.abs2()) {
        vel += dv.get_norm(acceleration * dt*dt);
        vel = clamped(vel, max_speed*dt);
    } else {
        vel -= clamped(vel * friction * dt, vel.abs2());
    }
    vel = clamped(vel, max_speed*0.1f);
    old_cam_dpos = old_cam_dpos*0.2f + vel * (cam_move * 2.6f);
    cam_dpos = cam_dpos*(1-dt) - old_cam_dpos;
    pos += vel*pow(cam_scale, -0.5f);

}

void player::draw(dr_buf* db) {
    db->draw_spt (120- cam_dpos.x * cam_scale, 120- cam_dpos.y * cam_scale, blocks);
    w_c = ((float)db->get_w()) / ((float) m_sh_r_c->get_width());
    h_c = ((float)db->get_h()) / ((float)m_sh_r_c->get_height());
}

void player::finit() {
    blocks->finit();
}

float player::get_pos_from_player_x(float o_x) const { return 128 + (o_x - pos.x - cam_dpos.x) * cam_scale; }
float player::get_pos_from_player_y(float o_y) const { return 128 + (o_y - pos.y - cam_dpos.y) * cam_scale; }

float player::get_w_c(){return w_c;}
float player::get_h_c(){return h_c;}

player::~player() { finit(); }