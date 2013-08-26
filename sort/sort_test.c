#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

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
    print_array(arr, len);
    printf("\n");

    bubblesort(arr, len);
    print_array(arr, len);
    printf("\n");
}
