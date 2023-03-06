#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "quick.h"

int value[2000];
int weight[2000];

int max(int a, int b) { 
    return (a > b) ? a : b; 
}

int K[10000][10000];


int knapSackdynamic(int W, int weight[], int value[], int n) {
    int i, w;
    //printf("%d %d ", n, W);
    //int K[n + 1][W + 1];
 
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (weight[i - 1] <= w)
                K[i][w] = max(value[i - 1]
                          + K[i - 1][w - weight[i - 1]],
                          K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
 
    return K[n][W];

}

int knapSackbrute(int W, int weight[], int value[], int n) {
    if (n == 0 || W == 0)
        return 0;

    if (weight[n - 1] > W)
        return knapSackbrute(W, weight, value, n - 1);

    else
        return max(
            value[n - 1] + knapSackbrute(W - weight[n - 1], weight, value, n - 1),
            knapSackbrute(W, weight, value, n - 1));
}


int knapSackgreedy(int W, int weight[], int value[], int n) {
    float cost[n-1];
    int indexes[n-1];

    for (int i = 0; i<n; i++) {
            indexes[i] = i;
    }

    QuickSort(weight, indexes, 0, n-1);

    int res = 0;

    for (int i=n-1; i>0; i--) {
        if (weight[indexes[i]] > W) {
            return res;
        }
        else {
            res += value[indexes[i]];
            W -= weight[indexes[i]];
            //printf("%d\n", res);
        }
    }


    return res;
}





int weightsSum;
int RandomBag(int size) {
    int i;
    weightsSum = 0;
    srand(time(0));
    for (i=0; i<size; i++) {
        
        int a = rand()%100;
        value[i] = a;
        int b = rand()%100;
        weight[i] = b;
        weightsSum += b;

        //for counting quality

        // if (i == 0) {
        //     value[i] = 15; 
        //     weight [i] = 10;
        // }
        // else {
        //     value[i] = 10;
        //     weight[i] = 10;
        // }
        // weightsSum += 10;
    }
    return 0;
}


int main()
{
    int s = 2;
    int itter;
    for (itter = 0; itter<15; itter++){
        RandomBag(s);
        int W = weightsSum*0.7;
        //printf("++ %d\n** %d\n ", weightsSum, W);
        printf("%d ", s);


        clock_t start = clock();
        int a = knapSackdynamic(W, weight, value, s);
        //printf("%d ", a);
        clock_t end = clock();
        float t;
        t = (end-start);
        printf("%f ", t);
        

        clock_t start2 = clock();
        int b = knapSackbrute(W, weight, value, s);
        //printf("%d ", b);
        clock_t end2 = clock();
        float t2 = (end2-start2);
        printf("%f ", t2);


        clock_t start3 = clock();
        int c = knapSackgreedy(W, weight, value, s);
        //printf("%d \n", c);
        clock_t end3 = clock();
        float t3 = (end3-start3);
        printf("%f\n", t3);
        s+=2;
    }

    return 0;
}
