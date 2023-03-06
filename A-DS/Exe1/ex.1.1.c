#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "count.h"
#include "bubble.h"
#include "heap.h"
#include "shell.h"

int main() {
    int n;
    printf("Sorting : Bubble, Heap, Count, Shell\n\n");
    
    static int toSort1[100000000];
    static int toSort2[100000000];
    static int toSort3[100000000];
    static int toSort4[100000000];
    int i, num;
    n = 50000;
    int itter = 0;

    while (itter<15) {
        for (i = 0; i<n; i++) {
            num = rand() % 100;
            toSort1[i] = num;
            toSort2[i] = num;
            toSort3[i] = num;
            toSort4[i] = num;
            //printf(" %d", num);
        }
        printf("%d\n", n);

        // clock_t start = clock();
        // BubbleSort(toSort1, n);
        // clock_t end = clock();
        // double t;
        // t = (end-start)*1000/CLOCKS_PER_SEC;
        // printf("%f  ", t);

        clock_t start2 = clock();
        HeapSort(toSort2, n);
        clock_t end2 = clock();
        double t2;
        t2 = (end2-start2)*1000/CLOCKS_PER_SEC;
        printf("%f  ", t2);

        clock_t start3 = clock();
        CountingSort(toSort3, n);
        clock_t end3 = clock();
        double t3;
        t3 = (end3-start3)*1000/CLOCKS_PER_SEC;
        printf("%f  ", t3);

        clock_t start4 = clock();
        ShellSort(toSort4, n);
        clock_t end4 = clock();
        double t4;
        t4 = (end4-start4)*1000/CLOCKS_PER_SEC;
        printf("%f\n\n", t4);



        n += 50000;
        itter++;
    }

    return 0;
}