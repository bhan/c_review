//#define DEBUG
#ifdef DEBUG
#define D
#else
#define D for (;0;)
#endif

void bubblesort(int arr[], int len);
void insertionsort(int arr[], int len);
void selectionsort(int arr[], int len);
void mergesort(int arr[], int len);
void quicksort(int arr[], int len);
