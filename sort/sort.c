#include "sort.h"
#include <assert.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void
bubblesort(int arr[], int len) {
    assert(arr != NULL);
    assert(len > 0);
    for (int i = 0; i < len-1; ++i) {
        int in_order = 1;
        for (int j = 0; j < len-1; j++) {
            if (arr[j+1] < arr[j]) {
                swap(&arr[j+1], &arr[j]);
                in_order = 0;
            }
        }
        if (in_order)
            return;
    }
}
