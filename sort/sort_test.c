#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

int* get_array_copy(int arr[], int len) {
    int* new_array = (int*)malloc(sizeof(int)*len);
    for (int i = 0; i < len; ++i)
        new_array[i] = arr[i];
    return new_array;
}

void print_array(int arr[], int len) {
    printf("[");
    for (int i = 0; i < len; ++i) {
        printf("%d,", arr[i]);
    }
    printf("]");
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("List of integers must be provided\n");
        return 1;
    }
    int len = argc-1;
    int arr[len];
    for (int i = 0; i < len; ++i) {
        arr[i] = atoi(argv[i+1]);
    }
    printf("input: ");
    print_array(arr, len);
    printf("\n");

    int *copy;

    copy = get_array_copy(arr, len);
    printf("bubblesort: ");
    bubblesort(copy, len);
    print_array(copy, len);
    printf("\n");
    free(copy);

    copy = get_array_copy(arr, len);
    printf("insertionsort: ");
    insertionsort(copy, len);
    print_array(copy, len);
    printf("\n");
    free(copy);

    copy = get_array_copy(arr, len);
    printf("selectionsort: ");
    selectionsort(copy, len);
    print_array(copy, len);
    printf("\n");
    free(copy);

    copy = get_array_copy(arr, len);
    printf("mergesort: ");
    mergesort(copy, len);
    print_array(copy, len);
    printf("\n");
    free(copy);
}
