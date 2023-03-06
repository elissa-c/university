#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "AdjecList.h"


void traverse(int u, bool visited[]) {
   visited[u] = true; //mark v as visited
   for(int v = 0; v<size; v++) {
      if(mat[u][v]) {
         if(!visited[v]) traverse(v, visited);
      }
   }
}
bool isConnected() {
   bool vis[size];
   //for all vertex u as start point, check whether all nodes are visible or not
   for(int u; u < size; u++) {
      for(int i = 0; i<size; i++)
         vis[i] = false; //initialize as no node is visited
         traverse(u, vis);
         for(int i = 0; i<size; i++) {
            if(!vis[i]) //if there is a node, not visited by traversal, mat is not connected
            return false;
         }
   }
   return true;
}
int hasEulerianCircuit() {
   if(isConnected() == false) return 0;   //when mat is not connected
   int degree[size];
   int oddDegree = 0;
   for(int i = 0; i<size; i++) {
      for(int j = 0; j<size; j++) {
         if(mat[i][j])
            degree[i]++; //increase degree, when connected edge found
      }
      if(degree[i] % 2 != 0) //when degree of vertices are odd
      oddDegree++; //count odd degree vertices
   }
   if(oddDegree == 0) { //when oddDegree is 0, it is Euler circuit
      return 1;
   }
   return 0;
}

void printEulerCycle()
{
    int i, start = 0;

    for (int i = 0; i < AdjacencyListCount; i++)
    {
        if (countEdges(i) % 2 == 1)
        {
            start = i;
            break;
        }
    }
    findEulerCycle(start);
}

void findEulerCycle(int start)
{
    ALI *current = AdjacencyList[start];

    while (current != NULL)
    {
        int target = current->j;

        if (target != -1 && isValidEdge(start, target))
        {
            removeUDEdge(start, target);
            findEulerCycle(target);
        }
        
        current = current->next;
    }
    
}

int isValidEdge(int start, int v)
{
    if (countEdges(start) == 1)
        return 1;

    int *visited = (int *)calloc(AdjacencyListCount, sizeof(int8_t));
    int c1 = dfsCount(start, visited);
    free(visited);

    removeUDEdge(start, v);
    visited = (int *)calloc(AdjacencyListCount, sizeof(int8_t));

    int c2 = dfsCount(start, visited);
    free(visited);

    if (c1 > c2)
        return 0;
    else
        return 1;
}

int dfsCount(int v, int8_t *visited)
{
    visited[v] = 1;
    int c = 1;

    ALI *current = AdjacencyList[v];

    while (current != NULL)
    {
        if (current->j != -1 && !visited[current->j])
            c = c + dfsCount(current->j, visited);

        current = current->next;
    }

    return c;
}







int main() {

    int itter = 0;
    int noReturns = 1;
    float t=0;

    while(itter<noReturns){
        create_undirected(mat);
        hasEulerianCircuit(); 

        initAList(size);
        for (int i =0; i<size; i++) {
            for (int j = i; j<size; j++) {
                    if (mat[i][j] == 1) {
                            addALEdge(i,j);
                            addALEdge(j, i);
                            //printf("%d  ", i);
                    }
            } 
        }

    clock_t start = clock();

    printEulerCycle();
    
    clock_t end = clock();
    t += (end-start)*1000/CLOCKS_PER_SEC;

    itter++;
    }
    printf("%d %f", size, t/noReturns);
}