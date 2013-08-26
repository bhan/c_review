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

void
insertionsort(int arr[], int len) {
    for (int i = 0; i < len-1; ++i) {
        int cur = i+1;
        for (int j = i; j >= 0; --j) {
            if (arr[cur] < arr[j]) {
                swap(&arr[cur], &arr[j]);
                cur = j;
            } else {
                break;
            }
        }
    }
}

void
selectionsort(int arr[], int len) {
    for (int i = 0; i < len-1; ++i) {
        int *min = &arr[i];
        for (int j = i; j < len; ++j) {
            if (*min > arr[j])
                min = &arr[j];
        }
        swap(&arr[i], min);
    }
}
