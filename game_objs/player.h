#pragma once
#include "g_object.h"
#include "../FundLibs/ShRendCPU/ShWin.h"

class player : public g_object{
private:
	vec2f vel, dv, cam_dpos, old_cam_dpos;
	ShWinRendCPU* m_sh_r_c;
	float w_c = 1, h_c = 1;
	float friction = 0.5f;
	float max_speed = 120;
	float cam_speed = 10;
	double cam_move = 0.5f;
	float acceleration = 40;
public:
	vec2f delta_cam;
	float cam_scale = 1;
	void init(ShWinRendCPU* r);
	void loop(float dt);
	void draw(dr_buf* db);
	void finit();
	float get_pos_from_player_x(float o_x) const;
	float get_pos_from_player_y(float o_y) const;
	float get_w_c();
	float get_h_c();
	~player();
};