#ifndef EDGE_LIST_H_INCLUDED
#define EDGE_LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct Edge{int vertex1, vertex2;};

int count_vertices(int mat[size][size]){
    int v = 0;
    for (int i = 0; i < size; i++){
        for (int j = i; j < size; j++){
            if (mat[i][j] == 1){
                v++;
            }
        }
    }
    return v;
}

struct Edge edge_list[25000000];

void create_edge_list(int mat[size][size]){
    int k = 0;
    for (int i = 0; i < size; i++){
        for (int j = i; j < size; j++){
            if (mat[i][j] == 1){
                struct Edge e;
                e.vertex1 = i;
                e.vertex2 = j;
                edge_list[k++]=e;
            }
        }
    }
    //printf("\n%d\n", k);
}

int el_edge_existence(struct Edge edge_list[], int num_of_vert){
    int random_vertex1 = rand()%size, random_vertex2 = rand()%size;
    for (int k=0; k<num_of_vert; k++){
        if ((edge_list[k].vertex1==random_vertex1 && edge_list[k].vertex2==random_vertex2) || (edge_list[k].vertex2==random_vertex1 && edge_list[k].vertex1 == random_vertex2)){
            return 1;
        }
    }
    return 0;
}

int incidence_matrix[size][(size*size)];

void inci_mat_from_edge(struct Edge edge_list[], int count, int incidence_matrix[size][count]){
    for (int i = 0; i<count; i++){
        incidence_matrix[edge_list[i].vertex1][i] = 1;
        incidence_matrix[edge_list[i].vertex2][i] = 1;
    }
}

int incmat_existance(int count, int incidence_matrix[size][count]) {
    int random_vertex1 = rand()%size, random_vertex2 = rand()%size;
    for (int i=0; i<count; i++){
        if (incidence_matrix[random_vertex1][i] == 1 && incidence_matrix[random_vertex2][i] == 1) {
            return 1;
        }
    }
    return 0;
}

#endif