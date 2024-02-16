.PHONY: clean

all: bubble_sort_test

bubble_sort_test: sorting_test.o bubble_sort.o
	gcc -o bubble_sort_test sorting_test.o bubble_sort.o

sorting_test.o: sorting_test.c
	gcc -c sorting_test.c

bubble_sort.o: bubble_sort.c
	gcc -c bubble_sort.c

clean:
	rm *.o bubble_sort_test
