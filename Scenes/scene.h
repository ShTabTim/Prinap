#pragma once
#include "../FundLibs/sh_d_l/dr_buf.h"
#include "../game_objs/object_manager.h"
//0 object is a camera
class scene {
protected:
	g_object* cam;
	object_manager o_mgr;
public:
	void init_sc(g_object* cam);
	virtual void loop_sc(float dt);
	virtual void draw_sc(dr_buf* db);
	virtual void finit_sc();
	g_object* get_cam() const;
};