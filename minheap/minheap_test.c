#include "minheap.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int intptr_t_cmp(void *a, void *b) {
  if ((intptr_t)a > (intptr_t)b) return 1;
  else if ((intptr_t)a < (intptr_t)b) return -1;
  else return 0;
}

void
intptr_t_print(void *value) {
    printf("%"PRIdPTR, value);
}

int main() {
  intptr_t values[] = {10, 5, 1, 8, 2, 6, 20, 5, 100};
  int size = sizeof(values)/sizeof(values[0]);
  struct minheap* heap = minheap_init(&intptr_t_cmp);
  minheap_check(heap);
  for (int i = 0; i < size; ++i) {
    minheap_check(heap);
    minheap_add(heap, (void*)values[i]);
    minheap_print(heap, &intptr_t_print);
  }
  for (int i = 0; i < size; ++i) {
    minheap_check(heap);
    intptr_t_print(minheap_remove(heap));
    printf("\n");
    minheap_print(heap, &intptr_t_print);
  }
  minheap_destroy(heap);
}
