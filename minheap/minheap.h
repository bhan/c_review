struct minheap {
  int size;
  void **values;
  int capacity;
  // the function used to define orderings in the heap
  int (*cmp)(void*, void*);
  void (*print)(void*);
};

struct minheap*
minheap_init(int (*cmp)(void*, void*), void (*print)(void*));
void minheap_destroy(struct minheap *heap);
// 0 on success, else error
int minheap_add(struct minheap* heap, void *value);
void *minheap_remove(struct minheap* heap);

void minheap_check(struct minheap* heap);
void minheap_print(struct minheap* heap);
