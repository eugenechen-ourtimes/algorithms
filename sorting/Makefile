.PHONY: clean

all: bubble_sort_test selection_sort_test insertion_sort_test merge_sort_test heap_sort_test

bubble_sort_test: sorting_test.o bubble_sort.o
	gcc -o bubble_sort_test sorting_test.o bubble_sort.o

selection_sort_test: sorting_test.o selection_sort.o
	gcc -o selection_sort_test sorting_test.o selection_sort.o

insertion_sort_test: sorting_test.o insertion_sort.o
	gcc -o insertion_sort_test sorting_test.o insertion_sort.o

merge_sort_test: sorting_test.o merge_sort.o
	gcc -o merge_sort_test sorting_test.o merge_sort.o

heap_sort_test: sorting_test.o heap_sort.o
	gcc -o heap_sort_test sorting_test.o heap_sort.o

sorting_test.o: sorting_test.c
	gcc -c sorting_test.c

bubble_sort.o: bubble_sort.c
	gcc -c bubble_sort.c

selection_sort.o: selection_sort.c
	gcc -c selection_sort.c

insertion_sort.o: insertion_sort.c
	gcc -c insertion_sort.c

merge_sort.o: merge_sort.c
	gcc -c merge_sort.c

heap_sort.o: heap_sort.c
	gcc -c heap_sort.c

clean:
	rm *.o bubble_sort_test selection_sort_test insertion_sort_test merge_sort_test heap_sort_test
