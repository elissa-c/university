#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <windows.h>


typedef struct AdjListNode
{
    int j;
    struct AdjListNode *next;
} AL;

AL **AdjacencyList;
int AdjacencyListCount;

void addALEdge(int i, int j);

void initAdjList(int n)
{
    int i, j;

    AdjacencyList = (AL **)calloc(n, sizeof(AL *));
    AdjacencyListCount = n;
    for (int z=0; z<n; z++) {
        AdjacencyList[z] = 0;
    }
}

void addALEdge(int i, int j)
{
    if (AdjacencyList == NULL)
        return;

    AL *newEdge = (AL *)calloc(1, sizeof(AL));

    newEdge->j = j;

    if (AdjacencyList[i] == 0)
    {
        AdjacencyList[i] = newEdge;
        return;
    }

    AL *current = AdjacencyList[i];

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newEdge;

    return;
}

void freeAdjList()
{
    if (AdjacencyList == NULL)
        return;

    int i;

    for (i = 0; i < AdjacencyListCount; i++)
    {
        AL *current = AdjacencyList[i], *prev;

        while (current != NULL)
        {
            prev = current;
            current = prev->next;
            free(prev);
        }
    }

    free(AdjacencyList);
}

uint8_t checkALEdge(int i, int j)
{
    AL *current;

    current = AdjacencyList[i];

    while (current != NULL)
    {
        if (current->j == j)
            return 1;

        current = current->next;
    }

    return 0;
}

void removeALEdge(int i, int j)
{
    if (AdjacencyList == NULL)
        return;

    if (AdjacencyList[i] == NULL)
        return;

    AL *current = AdjacencyList[i], *prev;

    if (current->j == j)
    {
        current->j = -1;
        return;
    }

    while (current != NULL && current->j != j)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return;
    
    current->j = -1;
    
    return;
}



clock_t algoStart;

int8_t hamiltonianCycle();
int8_t findHamiltonianCycle(int *path, int currentPos);
int8_t checkPathArray(int pos, int v, int *path);
void printPath(int *path);

int8_t hamiltonianCycle()
{
    int i, *path = (int *)malloc(sizeof(int) * AdjacencyListCount);

    for (i = 0; i < AdjacencyListCount; i++)
        path[i] = -1;

    path[0] = 0;

    algoStart = clock();

    if (findHamiltonianCycle(path, 1) == 0)
    {
        return 0;
    }

    //printPath(path);

    free(path);
    return 1;
}

int8_t findHamiltonianCycle(int *path, int currentPos)
{
    clock_t runtime = clock() - algoStart;

    if (currentPos == AdjacencyListCount)
    {
        if (checkALEdge(path[currentPos - 1], path[0]))
            return 1;
        else
            return 0;
    }

    AL *current = AdjacencyList[path[currentPos - 1]];

    while (current != NULL)
    {
        if (checkPathArray(currentPos, current->j, path))
        {
            path[currentPos] = current->j;

            if(findHamiltonianCycle(path, currentPos + 1) == 1)
                return 1;

            path[currentPos] = -1;
        }
        
        current = current->next;
    }
    

    return 0;
}

int8_t checkPathArray(int pos, int v, int *path)
{
    int i;

    for(i = 0; i < pos; i++)
        if(path[i] == v)
            return 0;

    return 1;
}

void printPath(int *path)
{
    int i;

    printf("%d ", path[0]);

    for (i = 1; i < AdjacencyListCount; i++)
        printf("-> %d ", path[i]);

    printf("\n");
}





void randomGraph(int n, float prob, int turn)
{
    initAdjList(n);

    char buffer[255];

    sprintf(buffer, "./data_%0.1f_%d_%d.txt", prob, n, turn);
    FILE *outputFile = fopen(buffer, "r");

    if (outputFile == NULL)
    {
        printf("no file");
        exit(1);
    }

    int i, j;

    while (1)
    {
        fgets(buffer, 255, outputFile);

        sscanf(buffer, "%d -> %d", &i, &j);

        if (i == -1 || j == -1)
            break;

        addALEdge(i, j);
        addALEdge(j, i);
    }

    
}



int main()
{

    
    int noReturns = 3, z =3;
    float prob[] = {0.2, 0.3, 0.4, 0.6, 0.8, 0.95};
    
    while (z<=5)
    {
        printf("\nHC for p=%f\n", prob[z]);
        int n = 20, itter = 0;
        while (itter<10)
        {
            double time = 0;
            int i = 0;
            while (i < noReturns)
            {
                int a;

                randomGraph(n, prob[z], i);


                clock_t start = clock();
                a = hamiltonianCycle();
                clock_t end = clock();


                time += (end - start)*1000 / CLOCKS_PER_SEC;
                i++;

                freeAdjList();
            }
            

            printf("%f\n", time/noReturns);

            n +=20;
            itter++;
        }
        z++;
        itter = 0;
    }

}