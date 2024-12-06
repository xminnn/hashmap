#pragma once

struct hashmap;

struct hashmap* hashmap_create(int init_cap, int element_size, int (*func_hashcode)(const void*), int (*func_equal)(const void*, const void*)); // element_size=0表示不申请内存仅存储指针
void hashmap_free(struct hashmap* self);
int hashmap_count(struct hashmap* self);
void hashmap_resize(struct hashmap* self, int capacity);
void* hashmap_add(struct hashmap* self, void* data); // 添加元素，⚠ 必须保证不存在
void* hashmap_put(struct hashmap* self, void* data);
void* hashmap_get(struct hashmap* self, const void* key);
void hashmap_del(struct hashmap* self, const void* key);

struct hashmap_itor {
    int i;
    int j;
    int where;
};
struct hashmap_itor hashmap_itor_next(struct hashmap* self, struct hashmap_itor it);
void* hashmap_itor_val(struct hashmap* self, struct hashmap_itor it);
#define _concat_impl(a, b) a##b
#define _concat(a, b) _concat_impl(a, b)
#define hashmap_foreach(type, val, map)                     \
    struct hashmap_itor _concat(__hmap_it, __LINE__) = {0}; \
    for (type val = 0; (_concat(__hmap_it, __LINE__) = hashmap_itor_next(map, _concat(__hmap_it, __LINE__))).where != 0 && (val = hashmap_itor_val(map, _concat(__hmap_it, __LINE__)));)
