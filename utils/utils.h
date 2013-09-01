#ifdef DEBUG
#define D
#else
#define D for (;0;)
#endif

void
print_array(int arr[], int len);
// returns number of places (including negative sign) a number takes up
int
utils_get_places(int num);
void
utils_print_array(void *arr[], int len, void (*print)(void*));
void
utils_swap(void **a, void **b);
