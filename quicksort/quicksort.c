#include <stdio.h>

void print_array(int array[], int length) {
  printf("{");
  for (int i = 0; i < length; ++i) {
    printf("%d,", array[i]);
  }
  printf("}\n");
}

static void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void quicksort(int array[], int begin, int end) {
  int len = end-begin+1;
  printf("begin:%d end:%d\n", begin, end);
  print_array(&array[begin], len);

  // array of length 0 or 1 is already sorted
  if (len <= 1)
    return;

  int left = begin;
  int right = end;
  int pivot_val = array[left+(right-left)/2];
  //printf("pivot_val:%d\n", pivot_val);
  while (left <= right) {
    // increment left until there's an element out of place (could hit pivot)
    if (array[left] < pivot_val) {
      ++left;
      continue;
    }
    // increment right until there's an element out of place (could hit pivot)
    if (array[right] > pivot_val) {
      --right;
      continue;
    }
    // swap those two elements
    swap(&array[left], &array[right]);
    ++left;
    --right;
  }

  printf("left:%d right:%d\n", left, right);
  print_array(&array[begin], len);
  quicksort(array, begin, right);
  quicksort(array, left, end);
}

int main(void) {
  int len = 10;
  int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  print_array(arr, len);
  quicksort(arr, 0, len-1);
  print_array(arr, len);

  len = 1;
  int arr2[] = {5};
  print_array(arr2, len);
  quicksort(arr2, 0, len-1);
  print_array(arr2, len);

  len = 6;
  int arr4[] = {10, 3, 6, 1, 2, 8};
  print_array(arr4, len);
  quicksort(arr4, 0, len-1);
  print_array(arr4, len);

  len = 3;
  int arr5[] = {3, 3, 1};
  print_array(arr5, len);
  quicksort(arr5, 0, len-1);
  print_array(arr5, len);

  len = 5;
  int arr3[] = {2, 3, 10, 1, 5};
  print_array(arr3, len);
  quicksort(arr3, 0, len-1);
  print_array(arr3, len);

  return 0;
}
