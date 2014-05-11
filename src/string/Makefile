CC=gcc
CFLAGS=-c -std=c99
LIB=-lm

all: string_test

string_test: utils.o string.o string_test.o
	$(CC) ../utils/utils.o string.o string_test.o -o string_test $(LIB)

string.o:
	$(CC) $(CFLAGS) string.c

string_test.o:
	$(CC) $(CFLAGS) string_test.c

utils.o:
	cd ../utils/; make

clean:
	rm -rf *o string_test; cd ../utils/; make clean
