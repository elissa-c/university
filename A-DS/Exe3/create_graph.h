#ifndef CREATE_GRAPH_H_INCLUDED
#define CREATE_GRAPH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 50
#define prob 0.6
#define iterations 10000


int mat[size][size];

void print_arr(int mat[size][size]){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            printf("%i ", mat[i][j]);
        }
        printf("\n");
    }
}

void create_undirected(int mat[size][size]){
    for (int i = 0; i < size; i++){
        time_t t;
        srand((unsigned) time(&t));
        for (int j = 0; j < size; j++){
            
            float random = (float)rand()/RAND_MAX;
            if (random < prob) {
                mat[i][j] = 1;
                mat[j][i] = 1;
            }
            else {
                mat[i][j] = 0;
                mat[j][i] = 0;
            }
        }
    }
}

int im_edge_existence(int mat[size][size]){
    int random_vertex1 = rand()%size, random_vertex2 = rand()%size;
    if (mat[random_vertex1][random_vertex2] == 1){
        return 1;
    }
    else {
        return 0;
    }
}

#endif // CREATE_GRAPH_H_INCLUDED
