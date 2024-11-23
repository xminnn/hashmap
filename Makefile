test_: 
	gcc -O3 *.c -o test
	@echo
	@echo "--- test 1 --- "
	./test 5000000 1000 500000000
	@echo
	@echo "--- test 2 --- initialize the capacity well"
	./test 5000000 5000000 500000000

.PYTHON: test_