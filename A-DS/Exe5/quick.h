#include <stdio.h>
#include <stdlib.h>

void swap(int a, int b, int x, int y) {
	int t = a;
	a = b;
	b = t;

    t = y;
    y = x;
    x = t;
}

int partition(int arr[],int indexes[], int start, int end)
{
    int pivot = arr[start];
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start], indexes[pivotIndex], indexes[start]);
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--], indexes[i++], indexes[j--]);
        }
    }

    return pivotIndex;
}

void QuickSort(int arr[], int indexes[], int start, int end)
{
    if (start >= end)
        return ;
    int p = partition(arr, indexes, start, end);
    QuickSort(arr, indexes, start, p - 1);
    QuickSort(arr,indexes, p + 1, end);
}