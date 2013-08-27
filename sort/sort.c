#include "sort.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static void
swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void
print_array(int arr[], int len) {
    printf("[");
    for (int i = 0; i < len; ++i) {
        printf("%d,", arr[i]);
    }
    printf("]");
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
    assert(arr != NULL);
    assert(len > 0);
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
    assert(arr != NULL);
    assert(len > 0);
    for (int i = 0; i < len-1; ++i) {
        int *min = &arr[i];
        for (int j = i; j < len; ++j) {
            if (*min > arr[j])
                min = &arr[j];
        }
        swap(&arr[i], min);
    }
}

static void
merge(int arr[], int lstart, int llen, int rstart, int rlen, int aux[]) {
    int lidx = lstart; int ridx = rstart;
    for (int i = lstart; i < lstart+llen+rlen; ++i) {
        if (lidx >= lstart+llen || arr[lidx] >= arr[ridx]) {
            aux[i] = arr[ridx];
            ++ridx;
        } else if (ridx >= rstart+rlen || arr[lidx] < arr[ridx]) {
            aux[i] = arr[lidx];
            ++lidx;
        }
    }
    for (int i = lstart; i < lstart+llen+rlen; ++i)
        arr[i] = aux[i];
}

static void
mergesort_helper(int arr[], int start, int len, int aux[]) {
    if (len < 2)
        return;

    int llen = len/2; int rlen = len-llen;
    int lstart = start; int rstart = lstart+llen;
    mergesort_helper(arr, lstart, llen, aux);
    mergesort_helper(arr, rstart, rlen, aux);
    merge(arr, lstart, llen, rstart, rlen, aux);
}

void
mergesort(int arr[], int len) {
    assert(arr != NULL);
    assert(len > 0);

    int aux[len];
    mergesort_helper(arr, 0, len, aux);
}
