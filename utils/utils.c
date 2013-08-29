#include <math.h>
#include <stdio.h>

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
swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void
print_array(int arr[], int len) {
    printf("[");
    for (int i = 0; i < len; ++i) {
        printf("%d,", arr[i]);
    }
    printf("]");
}
