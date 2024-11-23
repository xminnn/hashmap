#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "./hashmap.h"

long long time_curruent_us() {
    long long now;
    struct timeval tv;
    gettimeofday(&tv, 0);
    now = tv.tv_sec;
    now = now * 1000000;
    now += tv.tv_usec;
    return now;
}

int rand_range(int min, int max) {
    static int sand_inited = 0;
    if (!sand_inited) {
        sand_inited = 1;
        srand(time(NULL));
    }
    return ((1.0L * rand() / RAND_MAX) * (max - min) + 0.5L) + min;
}

int util_rand(int min, int max) {
    static unsigned long long seed;
    static char seed_init = 0;
    static const unsigned long long a = 1103515245;
    static const unsigned long long c = 12345;
    static const unsigned long long m = 1 << 31;
    if (seed_init == 0) {
        seed_init = 1;
        seed = time_curruent_us();
    }
    seed = (a * seed + c) % m;
    if (max <= min) {
        return min;
    }
    return seed % (max - min + 1) + min;
}

struct test_element {
    int rand;
};

static int test_hashcode(void* data) {
    struct test_element* it = (struct test_element*)data;
    return it->rand;
}

static int test_equal(void* a, void* b) {
    struct test_element* aa = (struct test_element*)a;
    struct test_element* bb = (struct test_element*)b;
    if (aa->rand == bb->rand) {
        return 1;
    }
    return 0;
}

int main(int argc, char const* argv[]) {
    int test_count = argc > 1 ? atoi(argv[1]) : 5000000;
    int init_count = argc > 2 ? atoi(argv[2]) : test_count;
    int rand_range = argc > 3 ? atoi(argv[3]) : test_count * 100;

    long long start_time, end_time;
    struct test_element* arr = (struct test_element*)malloc(sizeof(struct test_element) * test_count);
    for (int i = 0; i < test_count; i++) {
        arr[i].rand = util_rand(1, rand_range);
    }
    printf("test_count=%d, init_count=%d, rand_range=%d\n", test_count, init_count, rand_range);

    struct hashmap* hmap = hashmap_create(init_count, test_hashcode, test_equal);
    start_time = time_curruent_us();
    for (int i = 0; i < test_count; i++) {
        hashmap_put(hmap, &arr[i]);
    }
    end_time = time_curruent_us();
    int total_count = hashmap_count(hmap);
    printf("count: %d, put time pass: %lld us, %lld op/s\n", hashmap_count(hmap), end_time - start_time, 1000000L * test_count / (end_time - start_time));

    int error = 0;
    int not_find = 0;
    start_time = time_curruent_us();
    for (int i = 0; i < test_count; i++) {
        struct test_element* it = (struct test_element*)hashmap_get(hmap, &arr[i]);
        if (it == 0) {
            not_find++;
            continue;
        }
        if (it->rand != arr[i].rand) {
            error++;
        }
    }
    end_time = time_curruent_us();
    printf("count: %d, get time pass: %lld us, %lld op/s\n", hashmap_count(hmap), end_time - start_time, 1000000L * test_count / (end_time - start_time));

    printf("not_find: %d, error: %d\n", not_find, error);
    struct test_element* find = (struct test_element*)hashmap_get(hmap, &arr[891]);
    if (find) {
        printf("check: arr[891].rand=%d -> hget=%d\n", arr[891].rand, ((struct test_element*)hashmap_get(hmap, &arr[891]))->rand);
    }

    start_time = time_curruent_us();
    for (int i = 0; i < test_count; i++) {
        hashmap_del(hmap, &arr[i]);
    }
    end_time = time_curruent_us();
    printf("count: %d, del time pass: %lld us, %lld op/s\n", hashmap_count(hmap), end_time - start_time, 1000000L * test_count / (end_time - start_time));

    error = 0;
    for (int i = 0; i < test_count; i++) {
        struct test_element* it = (struct test_element*)hashmap_get(hmap, &arr[i]);
        if (it != 0) {
            error++;
        }
    }
    printf("error: %d, size=%d\n", error, hashmap_count(hmap));
    hashmap_free(hmap);

    printf("foreach check:\n");
    hmap = hashmap_create(init_count, test_hashcode, test_equal);
    for (int i = 0; i < 3; i++) {
        printf("%d ", arr[i].rand);
        hashmap_put(hmap, &arr[i]);
    }
    printf("\n");
    int test_forearch_(void* data);
    hashmap_foreach(hmap, test_forearch_);
    printf("\n");
    return 0;
}

int test_forearch_(void* data) {
    struct test_element* it = data;
    printf("%d ", it->rand);
    return 1;
}