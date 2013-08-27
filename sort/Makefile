CC=gcc
CFLAGS=-c -std=c99
all: sort_test

sort_test: utils.o sort.o sort_test.o
	$(CC) ../utils/utils.o sort.o sort_test.o -o sort_test

utils.o:
	$(CC) $(CFLAGS) ../utils/utils.c -o ../utils/utils.o

sort.o:
	$(CC) $(CFLAGS) sort.c

sort_test.o:
	$(CC) $(CFLAGS) sort_test.c

clean:
	rm -rf *o sort_test
