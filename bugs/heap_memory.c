#include <stdlib.h>
#include <stdio.h>

int* func1() {
  int* num = malloc(sizeof(int));
  *num = 5;
  return num;
}

int* func2() {
  int* num = malloc(sizeof(int));
  *num = 1000;
  return num;
}

int
main(void) {
  int *num = func1();
  func2();
  printf("%d\n", *num);
}
