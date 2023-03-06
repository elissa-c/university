#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "create_graph.h"
#include "edge_list.h"
#include "inci_list.h"


int main(){

    int noRetries = 10, z;
    float t = 0, t2 = 0, t3 = 0, t4 = 0;

    for (z=0; z<noRetries; z++) {

        create_undirected(mat);

        
        clock_t start = clock();

        for (int i=0; i<iterations; i++){
            im_edge_existence(mat);
        }

        clock_t end = clock();
        t += (end-start)*1000/CLOCKS_PER_SEC;

        //

        int num_of_vert=count_vertices(mat);
        create_edge_list(mat);

        clock_t start2 = clock();

        for (int i=0; i<iterations; i++){
            el_edge_existence(edge_list, num_of_vert);
        }

        clock_t end2 = clock();
        t2 += (end2-start2)*1000/CLOCKS_PER_SEC;

        //
        

        inci_mat_from_edge(edge_list, num_of_vert, incidence_matrix);

        clock_t start3 = clock();

        for (int i=0; i<iterations; i++){
            incmat_existance(num_of_vert, incidence_matrix);
        }

        clock_t end3 = clock();
        t3 += (end3-start3)*1000/CLOCKS_PER_SEC;

        //

        create_inci_list(mat);

        clock_t start4 = clock();

        for (int i=0; i<iterations; i++){
        il_edge_existence(node_list, num_of_vert);
        }

        clock_t end4 = clock();
        t4 += (end4-start4)*1000/CLOCKS_PER_SEC;
    }

    printf("Finding %d connections in matrixes size %d with prob %f\n", iterations, size, prob);
    printf("Vertex matrix, Edge list, Edge matrix, Incidence list:\n");
    printf("%f ", t/noRetries);
    printf("%f ", t2/noRetries);
    printf("%f ", t3/noRetries);
    printf("%f ", t4/noRetries);
    printf("\n");

    return 0;
}
