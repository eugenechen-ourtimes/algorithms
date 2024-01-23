.PHONY: clean

kth_largest: kth_largest.o heap_2.o
	gcc -o kth_largest kth_largest.o heap_2.o

kth_largest.o: kth_largest.c
	gcc -c kth_largest.c

heap_2.o: heap_2.c
	gcc -c heap_2.c

clean:
	rm *.o kth_largest
