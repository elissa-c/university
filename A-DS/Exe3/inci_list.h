#ifndef INCI_LIST_H_INCLUDED
#define INCI_LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


struct Node{int base, length, incidences[1000];};

struct Node node_list[15000];

void create_inci_list(int mat[size][size]){
    int k = 0;
    for (int i = 0; i < size; i++){
        for (int j = i; j < size; j++){
            struct Node n;
            n.base = i;
            int m = 0;
            if (mat[i][j] == 1){
                n.length = m;
                n.incidences[m] = j;
                m++;
            }
        node_list[k++] = n;
        }
    }
    //printf("\n%d\n", k);
}

int il_edge_existence(struct Node node_list[], int num_of_vert){
    int random_vertex1 = rand()%size, random_vertex2 = rand()%size;
    for (int k=0; k<num_of_vert; k++){
        if ((node_list[random_vertex1].incidences[k]==random_vertex2 || node_list[random_vertex2].incidences[k]==random_vertex1)){
            return 1;
        }
    }
    return 0;
}

#endif