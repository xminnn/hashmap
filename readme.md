## hashmap.c



## benchmarks

```
make
```

```txt
gcc -O3 *.c -o test

--- test 1 --- 
./test 5000000 1000 500000000
test_count=5000000, init_count=1000, rand_range=500000000
count: 4975008, put time pass: 403065 us, 12404947 op/s
count: 4975008, get time pass: 131709 us, 37962477 op/s
not_find: 0, error: 0
check: arr[891].rand=329848858 -> hget=329848858
count: 0, del time pass: 266284 us, 18776944 op/s
error: 0, size=0

--- test 2 --- initialize the capacity well
./test 5000000 5000000 500000000
test_count=5000000, init_count=5000000, rand_range=500000000
count: 4975045, put time pass: 175767 us, 28446750 op/s
count: 4975045, get time pass: 147677 us, 33857675 op/s
not_find: 0, error: 0
check: arr[891].rand=472356125 -> hget=472356125
count: 0, del time pass: 120897 us, 41357519 op/s
error: 0, size=0
```