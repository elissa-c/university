#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void BubbleSort(int arr[], int n) {
    int a;
        for (a=0; a<n-1; a++) {
            int b, one, two;
            for (b=0; b<n-a; b++) {
                one = arr[b];
                two = arr[b+1];
                if (one>two) {
                    arr[b]= two;
                    arr[b+1]=one;
                }
            }
        }
}