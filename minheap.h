#define NUM_CHILDREN 2

struct minheap {
  int size;
  int *values;
  int capacity;
};

struct minheap* minheap_init();
void minheap_destroy(struct minheap *heap);
// 0 on success, else error
int minheap_add(struct minheap* heap, int value);
int minheap_remove(struct minheap* heap);

void minheap_check(struct minheap* heap);
void minheap_print(struct minheap* heap);
