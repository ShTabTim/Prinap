#pragma once
#include <vector>
#include "../FundLibs/sh_d_l/dr_buf.h"
#include "g_object.h"

class object_manager {
private:
	g_object** g_objects;
	uint32_t amount_objects;
	void set_null();
	void set_null(uint32_t amount);
	void set_null(uint32_t from, uint32_t amount);
	void malloc_objs(uint32_t amount);
	void realloc_objs(uint32_t amount);
public:
	void init(uint32_t amount_objects = 1);
	void reinit(uint32_t amount_objects = 1);
	void loop(float dt);
	void draw(dr_buf* db);
	void update_z();
	void finit();
	uint32_t get_amount_objs() const;
	g_object* get_obj(uint32_t ind) const;
	uint32_t add_obj(g_object* obj);
	void set_obj(g_object* obj, uint32_t ind);
	uint32_t set_obj(g_object* obj);
	g_object* del_obj_from_mgr(uint32_t ind);
	void fin_obj(uint32_t ind);
};