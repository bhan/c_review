#include <math.h>
#include <stdio.h>

void
print_array(int arr[], int len) {
    printf("[");
    for (int i = 0; i < len; ++i) {
        printf("%d,", arr[i]);
    }
    printf("]");
}

int
utils_get_places(int num) {
    if (num == 0)
        return 1;
    int places = 0;
    if (num < 0) {
        ++places;
        num = -1*num;
    }
    return ceil(log10(num));
}

void
utils_swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

void
utils_print_array(void *arr[], int len, void (*print)(void*)) {
  printf("[");
  for (int i = 0; i < len; ++i) {
    print(arr[i]); printf(",");
  }
  printf("]");
}
