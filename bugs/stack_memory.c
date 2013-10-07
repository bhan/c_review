#include <stdio.h>

int* func1() {
  int num = 5;
  return &num;
}

int* func2() {
  int num = 1000;
}

int
main(void) {
  int *num = func1();
  func2();
  printf("%d\n", *num);
}
