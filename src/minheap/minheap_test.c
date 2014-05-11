#include "minheap.h"
#include "../utils/utils.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int intptr_t_cmp_asc(void *a, void *b) {
  if ((intptr_t)a > (intptr_t)b) return 1;
  else if ((intptr_t)a < (intptr_t)b) return -1;
  else return 0;
}

int intptr_t_cmp_dsc(void *a, void *b) {
  if ((intptr_t)a < (intptr_t)b) return 1;
  else if ((intptr_t)a > (intptr_t)b) return -1;
  else return 0;
}

void
intptr_t_print(void *value) {
    printf("%"PRIdPTR, (intptr_t)value);
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("Please provide a list of integers\n");
    return 1;
  }
  int len = argc-1;
  intptr_t values[len];
  for (int i = 0; i < len; ++i)
    values[i] = (intptr_t)atoi(argv[i+1]);

  printf("input: ");
  utils_print_array((void**)values, len, &intptr_t_print);
  printf("\n");

  struct minheap* heap = minheap_init(&intptr_t_cmp_asc, &intptr_t_print);
  minheap_print(heap);
  printf("\n");
  minheap_check(heap);
  printf("passed minheap_check\n");
  for (int i = 0; i < len; ++i) {
    printf("adding "); intptr_t_print((void*)values[i]); printf(" ");
    minheap_add(heap, (void*)values[i]);
    minheap_print(heap); printf("\n");
    minheap_check(heap); printf("passed minheap_check\n");
  }
  for (int i = 0; i < len; ++i) {
    printf("removed ");
    intptr_t_print(minheap_remove(heap)); printf(" ");
    minheap_print(heap); printf("\n");
    minheap_check(heap); printf("passed minheap_check\n");
  }
  minheap_destroy(heap);
}
