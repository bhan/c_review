CC=gcc
CFLAGS=-c -std=c99
LIBS=-lm
all: sort_test

simpletree_test: simpletree.o common.o utils.o bst_test.o
	$(CC) simpletree.o common.o bst_test.o utils.o -o bst_test $(LIBS)

rbtree_test: rbtree.o common.o utils.o bst_test.o
	$(CC) rbtree.o common.o bst_test.o -o bst_test $(LIBS)

simpletree.o:
	$(CC) $(CFLAGS) simpletree.c

rbtree.o:
	$(CC) $(CFLAGS) rbtree.c

common.o:
	$(CC) $(CFLAGS) common.c

utils.o:
	$(CC) $(CFLAGS) ../utils/utils.c

bst_test.o:
	$(CC) $(CFLAGS) bst_test.c

clean:
	rm -rf *o bst_test
