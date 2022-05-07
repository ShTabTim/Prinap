#include "object_manager.h"
#include <cassert>
#include <algorithm>


void object_manager::set_null() {
	if (g_objects)
		std::memset(g_objects, NULL, this->amount_objects * sizeof(g_object*));
}
void object_manager::set_null(uint32_t amount){
	if (g_objects && this->amount_objects >= amount)
		std::memset(g_objects, NULL, amount * sizeof(g_object*));
}
void object_manager::set_null(uint32_t from, uint32_t amount) {
	if (g_objects && this->amount_objects >= amount+from)
		std::memset(g_objects + from, NULL, amount * sizeof(g_object*));
}
void object_manager::malloc_objs(uint32_t amount) {
	g_objects = (g_object**)malloc(amount * sizeof(g_object*));
}
void object_manager::realloc_objs(uint32_t amount) {
	g_objects = (g_object**)realloc(g_objects, amount * sizeof(g_object*));
}


void object_manager::init(uint32_t amount) {
	malloc_objs(amount_objects = amount);
	assert(g_objects);
	set_null();
}
void object_manager::reinit(uint32_t amount) {
	realloc_objs(amount);
	assert(g_objects);
	if (amount > amount_objects)
		set_null(amount_objects, amount - amount_objects);
	amount_objects = amount;
}
void object_manager::loop(float dt) {
	for (g_object** gh(g_objects + amount_objects); g_objects < gh--;)
		if (*gh)(*gh)->loop(dt);
}

void object_manager::draw(dr_buf* db) {
	for (g_object** gh(g_objects + amount_objects); g_objects < gh--;)
		if (*gh)(*gh)->draw(db);
}
int comp2(const void* a, const void* b) {
	return ((*(g_object**)a)->z - (*(g_object**)b)->z);
}
void object_manager::update_z() {
	qsort(g_objects, amount_objects, sizeof(g_object*), comp2);
}

void object_manager::finit() {
	for (uint32_t gh(amount_objects); gh--;)
		fin_obj(gh);
	free(g_objects);
	g_objects = NULL;
}
uint32_t object_manager::get_amount_objs() const {
	return amount_objects;
}
g_object* object_manager::get_obj(uint32_t ind) const {
	return *(g_objects+ind);
}
uint32_t object_manager::add_obj(g_object* obj) {
	realloc_objs(amount_objects + 1);
	*(g_objects + amount_objects) = obj;
	return amount_objects++;
}
void object_manager::set_obj(g_object* obj, uint32_t ind) {
	*(g_objects + ind) = obj;
}
uint32_t object_manager::set_obj(g_object* obj) {
	for (g_object** gh(g_objects + amount_objects); g_objects < gh--;)
		if (!(*gh))
			return ((*gh = obj), (gh - g_objects));
	return add_obj(obj);
}
g_object* object_manager::del_obj_from_mgr(uint32_t ind) {
	g_object* gh = g_objects[ind];
	g_objects[ind] = NULL;
	return gh;
}
void object_manager::fin_obj(uint32_t ind) {
	if (g_objects[ind]) {
		g_objects[ind]->finit();
		free(g_objects[ind]);
		g_objects[ind] = NULL;
	}
}