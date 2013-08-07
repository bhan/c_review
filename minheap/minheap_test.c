#include "minheap.h"
#include <stdio.h>

int main() {
  int values[] = {10, 5, 1, 8, 2, 6, 20, 5};
  int size = sizeof(values)/sizeof(values[0]);
  struct minheap* heap = minheap_init();
  minheap_check(heap);
  for (int i = 0; i < size; ++i) {
    minheap_check(heap);
    minheap_add(heap, values[i]);
    minheap_print(heap);
  }
  for (int i = 0; i < size; ++i) {
    minheap_check(heap);
    int value = minheap_remove(heap);
    printf("value:%d\n", value);
    minheap_print(heap);
  }
  minheap_destroy(heap);
}
