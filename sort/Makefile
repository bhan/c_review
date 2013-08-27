all: sort_test

sort_test: utils.o sort.o sort_test.o
	gcc ../utils/utils.o sort.o sort_test.o -o sort_test

utils.o:
	gcc -std=c99 -c ../utils/utils.c -o ../utils/utils.o

sort.o:
	gcc -std=c99 -c sort.c

sort_test.o:
	gcc -std=c99 -c sort_test.c

clean:
	rm -rf *o sort_test
