#include "minheap.h"
#include "../utils/utils.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct minheap* minheap_init() {
  struct minheap *heap = (struct minheap*)malloc(sizeof(struct minheap));
  if (heap == NULL)
    return NULL;
  heap->size = 0;
  heap->values = NULL;
  heap->capacity = 0;
  return heap;
}

void minheap_destroy(struct minheap *heap) {
  assert(heap != NULL);
  assert(heap->size == 0);
  assert(heap->values == NULL);
  assert(heap->capacity == 0);
  free(heap);
}

int minheap_add(struct minheap *heap, int value) {
  assert(heap != NULL);
  // empty heap
  if (heap->size == 0) {
    assert(heap->values == NULL);
    assert(heap->capacity == 0);

    int *values = (int*)malloc(sizeof(int));
    if (values == NULL)
      return -1;
    values[0] = value;
    heap->values = values;
    heap->size = 1;
    heap->capacity = 1;
    return 0;
  }

  // heap is at capacity, double capacity
  if (heap->size == heap->capacity) {
    int new_capacity = heap->capacity*2;
    int *new_values = (int*)realloc(heap->values, sizeof(int)*new_capacity);
    if (new_values == NULL)
      return -1;
    heap->values = new_values;
    heap->capacity = new_capacity;
  }

  heap->values[heap->size] = value;
  ++heap->size;

  int cur_pos = heap->size-1;
  int par_pos = (cur_pos-1)/2;
  while (heap->values[cur_pos] < heap->values[par_pos] && par_pos >= 0) {
    utils_swap(&heap->values[cur_pos], &heap->values[par_pos]);
    cur_pos = par_pos;
    par_pos = (par_pos-1)/2;
  }

  return 0;
}

int minheap_remove(struct minheap *heap) {
  assert(heap != NULL);
  assert(heap->size > 0);

  int min = heap->values[0];
  heap->values[0] = heap->values[heap->size-1];
  --heap->size;

  // reallocate when too much capacity
  if (heap->size <= heap->capacity/2) {
    int new_capacity = heap->capacity/2;
    int *new_values = (int*)realloc(heap->values, new_capacity);
    if (new_capacity == 0)
      heap->values = NULL;
    else heap->values = new_values;
    heap->capacity = new_capacity;
  }

  int cur_pos = 0;
  int child1_pos = cur_pos*2+1;
  int child2_pos = child1_pos+1;
  while ((child1_pos < heap->size &&
          heap->values[cur_pos] > heap->values[child1_pos]) ||
         (child2_pos < heap->size &&
          heap->values[cur_pos] > heap->values[child2_pos])
        ) {
    int swap_pos = ((child1_pos < heap->size && child2_pos >= heap->size) ||
                    (heap->values[child1_pos] < heap->values[child2_pos])) ?
                    child1_pos : child2_pos;
    utils_swap(&heap->values[cur_pos], &heap->values[swap_pos]);
    cur_pos = swap_pos;
    child1_pos = cur_pos*2+1;
    child2_pos = child1_pos+1;
  }

  return min;
}

void minheap_check(struct minheap *heap) {
  assert(heap != NULL);
  for (int cur_pos = heap->size-1; cur_pos > 0; --cur_pos) {
    int par_pos = (cur_pos-1)/2;
    assert(heap->values[cur_pos] >= heap->values[par_pos]);
  }
}

void minheap_print(struct minheap *heap) {
  assert(heap != NULL);
  printf("size:%d\n", heap->size);
  printf("capacity:%d\n", heap->capacity);
  printf("{");
  for (int i = 0; i < heap->size; ++i) {
    printf("%d,", heap->values[i]);
  }
  printf("}\n");
}
