#pragma once

struct hashmap;

struct hashmap* hashmap_create(int init_cap, int (*func_hashcode)(const void*), int (*func_equal)(const void*, const void*));
void hashmap_free(struct hashmap* self);
int hashmap_count(struct hashmap* self);
void hashmap_resize(struct hashmap* self, int capacity);
void hashmap_add(struct hashmap* self, void* data);    // the data key must not have been putted before.
void hashmap_put(struct hashmap* self, void* data);
void* hashmap_get(struct hashmap* self, void* key);
void hashmap_del(struct hashmap* self, void* key);
void hashmap_foreach(struct hashmap* self, int (*func)(void*));    // func: return 1 continue, return 0 break; can't do put or del in this func
