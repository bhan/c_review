#ifdef DEBUG
#define D
#else
#define D for (;0;)
#endif

// returns number of places (including negative sign) a number takes up
int
utils_get_places(int num);
void
print_array(int arr[], int len);
void
utils_swap(int *a, int *b);
