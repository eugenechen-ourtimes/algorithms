.PHONY: clean

queue_test: queue_test.o queue.o
	gcc -o queue_test queue_test.o queue.o

queue_test.o: queue_test.c
	gcc -c queue_test.c

queue.o: queue.c
	gcc -c queue.c

clean:
	rm *.o queue_test
