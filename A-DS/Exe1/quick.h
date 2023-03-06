#include <stdio.h>
#include <stdlib.h>

void swapq(int arr[], int a, int b) {
	int t = arr[a];
	arr[a] = arr[b];
	arr[b] = t;
}

void QuickSort(int arr[], int low, int high)
{
    if(high <= low) return;
	int i = low - 1, j = high + 1, 
	pivot = arr[(low + high) / 2];
	
	while(i <= j){
		while (pivot > arr[++i]);
		while(pivot < arr[--j]);
		if(i < j)
			swapq(arr, i, j);

	}

	if(j > low)
	    QuickSort(arr, low, j);
	if(i < high)
	    QuickSort(arr, i, high);
}
