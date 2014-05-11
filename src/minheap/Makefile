CC=gcc
CFLAGS=-c -std=c99
LIB=-lm

all: minheap_test

minheap_test: utils.o minheap.o minheap_test.o
	$(CC) ../utils/utils.o minheap.o minheap_test.o -o minheap_test $(LIB)

minheap.o:
	$(CC) $(CFLAGS) minheap.c

minheap_test.o:
	$(CC) $(CFLAGS) minheap_test.c

utils.o:
	cd ../utils/; make

clean:
	rm -rf *o minheap_test; cd ../utils/; make clean
