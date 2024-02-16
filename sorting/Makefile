.PHONY: clean

all: bubble_sort_test selection_sort_test

bubble_sort_test: sorting_test.o bubble_sort.o
	gcc -o bubble_sort_test sorting_test.o bubble_sort.o

selection_sort_test: sorting_test.o selection_sort.o
	gcc -o selection_sort_test sorting_test.o selection_sort.o

sorting_test.o: sorting_test.c
	gcc -c sorting_test.c

bubble_sort.o: bubble_sort.c
	gcc -c bubble_sort.c

selection_sort.o: selection_sort.c
	gcc -c selection_sort.c

clean:
	rm *.o bubble_sort_test selection_sort_test
