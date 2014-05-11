CC=gcc
CFLAGS=-c -std=c99
LIB=-lm
all: sort_test

sort_test: utils.o sort.o sort_test.o
	$(CC) ../utils/utils.o sort.o sort_test.o -o sort_test $(LIB)

utils.o:
	cd ../utils/; make

sort.o:
	$(CC) $(CFLAGS) sort.c

sort_test.o:
	$(CC) $(CFLAGS) sort_test.c

clean:
	rm -rf *o sort_test; cd ../utils/; make clean
