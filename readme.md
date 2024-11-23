## hashmap.c

c实现的简单的hashmap. 采用线性探测法处理hash冲突。代码简单，性能强悍。


## example

```c
#include <stdio.h>
#include "hashmap.h"

struct test_element {
    int rand;
};

static int test_hashcode(const void* data) {
    const struct test_element* it = data;
    return it->rand;
}

static int test_equal(const void* a, const void* b) {
    const struct test_element* aa = a;
    const struct test_element* bb = b;
    if (aa->rand == bb->rand) {
        return 1;
    }
    return 0;
}

int test_forearch_(void* data) {
    struct test_element* it = data;
    printf("%d\n", it->rand);
    return 1;
}

int main(int argc, char const* argv[]) {
    struct hashmap* hmap = hashmap_create(100, test_hashcode, test_equal);
    hashmap_put(hmap, &(struct test_element){.rand = 1});
    hashmap_get(hmap, &(struct test_element){.rand = 1});
    hashmap_foreach(hmap, test_forearch_);
    hashmap_del(hmap, &(struct test_element){.rand = 1});
    hashmap_free(hmap);
    return 0;
}
```

## benchmarks

执行测试：
```sh
make
```

测试机器：`MacBook Air（M2，2022年）`
```txt
gcc -Wall -Werror -O3 *.c -o test

--- test 1 --- 
./test 5000000 1000 500000000
test_count=5000000, init_count=1000, rand_range=500000000
count: 4975302, put time pass: 393600 us, 12703252 op/s
count: 4975302, get time pass: 133267 us, 37518665 op/s
not_find: 0, error: 0
check: arr[891].rand=177771394 -> hget=177771394
count: 0, del time pass: 266096 us, 18790211 op/s
error: 0, size=0
foreach check:
480968755 483143300 306079745 
480968755 483143300 306079745 

--- test 2 --- initialize the capacity well
./test 5000000 5000000 500000000
test_count=5000000, init_count=5000000, rand_range=500000000
count: 4975002, put time pass: 168393 us, 29692445 op/s
count: 4975002, get time pass: 165994 us, 30121570 op/s
not_find: 0, error: 0
check: arr[891].rand=217067086 -> hget=217067086
count: 0, del time pass: 125840 us, 39732994 op/s
error: 0, size=0
foreach check:
158207695 83217392 370289917 
370289917 158207695 83217392 
```