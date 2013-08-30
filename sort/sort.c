#include "sort.h"
#include "../utils/utils.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void
bubblesort(int arr[], int len) {
    assert(arr != NULL);
    assert(len > 0);
    for (int i = 0; i < len-1; ++i) {
        int in_order = 1;
        for (int j = 0; j < len-1; j++) {
            if (arr[j+1] < arr[j]) {
                utils_swap(&arr[j+1], &arr[j]);
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
                utils_swap(&arr[cur], &arr[j]);
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
        utils_swap(&arr[i], min);
    }
}

static void
merge(int arr[], int lstart, int llen, int rstart, int rlen, int aux[]) {
    D printf("merge:");
    D printf("larr:");
    D print_array(&arr[lstart], llen);
    D printf(",rarr:");
    D print_array(&arr[rstart], rlen);
    D printf(",lstart:%d,llen:%d,rstart:%d,rlen:%d\n",
            lstart, llen, rstart, rlen);
    int lidx = lstart; int ridx = rstart;
    for (int i = lstart; i < lstart+llen+rlen; ++i) {
        if (lidx < lstart+llen && ridx < rstart+rlen) {
            // both array indices are valid, so compare values from both arrays
            if (arr[lidx] >= arr[ridx]) {
                aux[i] = arr[ridx];
                ++ridx;
            } else {
                aux[i] = arr[lidx];
                ++lidx;
            }
        } else if (ridx >= rstart+rlen) {
            // right array index out of range, so take from the left array
            aux[i] = arr[lidx];
            ++lidx;
        } else if (lidx >= lstart+llen) {
            // left array index out of range, so take from the right array
            aux[i] = arr[ridx];
            ++ridx;
        }
    }
    for (int i = lstart; i < lstart+llen+rlen; ++i)
        arr[i] = aux[i];

    D printf("merge:result:");
    D print_array(&arr[lstart], llen+rlen);
    D printf("\n");
}

static void
mergesort_helper(int arr[], int start, int len, int aux[]) {
    D printf("mergesort_helper:");
    D printf("arr:");
    D print_array(&arr[start], len);
    D printf(",start:%d,len:%d\n", start, len);

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
    D printf("mergesort:");
    D print_array(arr, len);
    D printf(",%d\n", len);

    int aux[len];
    mergesort_helper(arr, 0, len, aux);
}

int
quicksort_partition(int arr[], int len) {
    int pidx = len/2;
    int pivot = arr[pidx];
    utils_swap(&arr[pidx], &arr[len-1]);
    int swapidx = 0;
    // rearrange all elements less than pivot to be below an index: swapidx
    for (int i = 0; i < len-1; ++i) {
        if (arr[i] < pivot) {
            utils_swap(&arr[i], &arr[swapidx]);
            ++swapidx;
        }
    }
    // at this point, all elements < pivot are at slots 0...swapidx-1
    utils_swap(&arr[swapidx], &arr[len-1]);
    return swapidx;
}

void
quicksort(int arr[], int len) {
    if (len < 2)
        return;
    int pivotIndex = quicksort_partition(arr, len);
    quicksort(arr, pivotIndex);
    quicksort(&arr[pivotIndex+1], len-pivotIndex-1);
}
