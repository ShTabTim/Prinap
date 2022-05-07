#include "scene.h"

void scene::init_sc(g_object* cam) {
	o_mgr.init();
	o_mgr.set_obj(cam, 0);
	this->cam = cam;
}
void scene::loop_sc(float dt) {
	o_mgr.loop(dt);
}
void scene::draw_sc(dr_buf* db) {
	o_mgr.draw(db);
}
void scene::finit_sc() {
	o_mgr.finit();
}
g_object* scene::get_cam() const { return cam; }