#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }
  
  void tree(int arr[],int  n,int i) {
    int top = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[top]) {
      top = left;
    }

    if (right < n && arr[right] > arr[top]){
      top = right;
    }

    if (top != i) {
      swap(&arr[i], &arr[top]);
      tree(arr, n, top);
    }
  }

  void HeapSort(int arr[],int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
      tree(arr, n, i);

    for (i = n - 1; i >= 0; i--) {
      swap(&arr[0], &arr[i]);

      tree(arr, i, 0);
    }
  }
