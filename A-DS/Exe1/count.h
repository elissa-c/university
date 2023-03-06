#include <stdio.h>
#include <stdlib.h>

int arr1[1000000];
int count_arr[1000000];
void CountingSort(int arr[], int n) {

  int x = arr[0];
  for (int i = 1; i < n; i++) {
    if (arr[i] > x)
      x = arr[i];
  }

  for (int i = 0; i <= x; ++i) {
    count_arr[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    count_arr[arr[i]]++;
  }

  for (int i = 1; i <= x; i++) {
    count_arr[i] += count_arr[i - 1];
  }


  for (int i = n - 1; i >= 0; i--) {
    arr1[count_arr[arr[i]] - 1] = arr[i];
    count_arr[arr[i]]--;
  }

  for (int i = 0; i < n; i++) {
    arr[i] = arr1[i];
  }
}