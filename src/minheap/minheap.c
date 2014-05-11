#include "minheap.h"
#include "../utils/utils.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct minheap* minheap_init(int (*cmp)(void*, void*),
                             void (*print)(void*)) {
  assert(cmp != NULL);
  struct minheap *heap = (struct minheap*)malloc(sizeof(struct minheap));
  if (heap == NULL)
    return NULL;
  heap->size = 0;
  heap->values = NULL;
  heap->capacity = 0;
  heap->cmp = cmp;
  heap->print = print;
  return heap;
}

void minheap_destroy(struct minheap *heap) {
  assert(heap != NULL);
  assert(heap->size == 0);
  assert(heap->values == NULL);
  assert(heap->capacity == 0);
  free(heap);
}

int minheap_add(struct minheap *heap, void *value) {
  assert(heap != NULL);
  // empty heap
  if (heap->size == 0) {
    assert(heap->values == NULL);
    assert(heap->capacity == 0);

    void **values = (void**)malloc(sizeof(void*));
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
    void **new_values = (void**)realloc(heap->values,
                                        sizeof(void*)*new_capacity);
    if (new_values == NULL)
      return -1;
    heap->values = new_values;
    heap->capacity = new_capacity;
  }

  heap->values[heap->size] = value;
  ++heap->size;

  int cur_pos = heap->size-1;
  int par_pos = (cur_pos-1)/2;
  while (heap->cmp(heap->values[cur_pos], heap->values[par_pos]) == -1 &&
         par_pos >= 0) {
    utils_swap(&heap->values[cur_pos], &heap->values[par_pos]);
    cur_pos = par_pos;
    par_pos = (par_pos-1)/2;
  }

  return 0;
}

static inline int
minheap_get_swap_idx(struct minheap *heap, int cur_idx) {
  assert(heap != NULL);
  assert(cur_idx >= 0);

  int l_idx = cur_idx*2+1; // index of left child
  int r_idx = l_idx+1; // index of right child
  // swap with the min(left child, right child) if left or right child smaller
  int swap_idx = -1;
  if (r_idx < heap->size) {
    // two children exist
    if (heap->cmp(heap->values[cur_idx], heap->values[l_idx]) > 0) {
      // parent is greater than left child, right child possibly smaller still
      if (heap->cmp(heap->values[l_idx], heap->values[r_idx]) > 0) {
        // left child is greater than right child, so swap right child
          swap_idx = r_idx;
      } else {
        // left child is not greater than right child, so swap left child
        swap_idx = l_idx;
      }
    } else if (heap->cmp(heap->values[cur_idx], heap->values[r_idx]) > 0) {
      // parent is greater than right child but not left, so swap right child
      swap_idx = r_idx;
    }
  } else if (l_idx < heap->size) {
    // only left child exists
    if (heap->cmp(heap->values[cur_idx], heap->values[l_idx]) > 0) {
      // parent is greater than left child, so swap left child
      swap_idx = l_idx;
    }
  }
  return swap_idx;
}

void *minheap_remove(struct minheap *heap) {
  assert(heap != NULL);
  assert(heap->size > 0);

  void *min = heap->values[0];
  heap->values[0] = heap->values[heap->size-1];
  --heap->size;

  // reallocate when too much capacity
  if (heap->size <= heap->capacity/2) {
    int new_capacity = heap->capacity/2;
    void **new_values = (void**)realloc(heap->values,
                                        new_capacity*sizeof(void*));
    if (new_capacity == 0)
      heap->values = NULL;
    else heap->values = new_values;
    heap->capacity = new_capacity;
  }

  int cur_idx = 0;
  int swap_idx = minheap_get_swap_idx(heap, cur_idx);
  while (swap_idx > 0) {
    utils_swap(&heap->values[cur_idx], &heap->values[swap_idx]);
    cur_idx = swap_idx;
    swap_idx = minheap_get_swap_idx(heap, cur_idx);
  }

  return min;
}

// start from bottom of heap, make sure each child is "greater" than parent
void minheap_check(struct minheap *heap) {
  assert(heap != NULL);
  for (int cur_pos = heap->size-1; cur_pos > 0; --cur_pos) {
    int par_pos = (cur_pos-1)/2;
    assert(heap->cmp(heap->values[cur_pos], heap->values[par_pos]) >= 0);
  }
}

void minheap_print(struct minheap *heap) {
  assert(heap != NULL);
  printf("{");
  for (int i = 0; i < heap->size; ++i) {
    heap->print(heap->values[i]);
    printf(",");
  }
  printf("} size:%d capacity:%d", heap->size, heap->capacity);
}
